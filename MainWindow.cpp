
#include "MainWindow.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include <QMessageBox>
#include <QListWidgetItem>

#include "PercentTipOut.h"
#include "FixedTipOut.h"

#include <exception>
#include <cmath>

// Builds main TipTally window
MainWindow::MainWindow(Tracker& tracker, QWidget *parent)
    : QMainWindow(parent),
      tracker(tracker)
{
    setWindowTitle("TipTally");
    setFixedSize(700, 500);

    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    QFormLayout *formLayout = new QFormLayout();

    shiftDateInput = new QDateEdit(QDate::currentDate());
    shiftDateInput->setCalendarPopup(true);

    hoursInput = new QLineEdit();
    wageInput = new QLineEdit();
    tipsInput = new QLineEdit();
    salesInput = new QLineEdit();

    tipTypeBox = new QComboBox();
    tipTypeBox->addItems({"Percent", "Fixed"});

    tipValueInput = new QLineEdit();

    formLayout->addRow("Shift Date:", shiftDateInput);
    formLayout->addRow("Hours Worked:", hoursInput);
    formLayout->addRow("Hourly Wage:", wageInput);
    formLayout->addRow("Tips Earned:", tipsInput);
    formLayout->addRow("Sales:", salesInput);
    formLayout->addRow("Tip-Out Type:", tipTypeBox);
    formLayout->addRow("Tip-Out Value:", tipValueInput);

    mainLayout->addLayout(formLayout);

    addShiftButton = new QPushButton("Add Shift");
    QPushButton *calculateButton = new QPushButton("Calculate Tip-Out");

    mainLayout->addWidget(addShiftButton);
    mainLayout->addWidget(calculateButton);

    resultLabel = new QLabel("Enter shift information.");
    totalEarningsLabel = new QLabel();

    mainLayout->addWidget(resultLabel);
    mainLayout->addWidget(totalEarningsLabel);

    allShiftsBox = new QCheckBox("Show All Shifts");
    allShiftsBox->setChecked(true);

    viewDateInput = new QDateEdit(QDate::currentDate());
    viewDateInput->setCalendarPopup(true);

    shiftList = new QListWidget();

    mainLayout->addWidget(allShiftsBox);
    mainLayout->addWidget(viewDateInput);
    mainLayout->addWidget(shiftList);

    QLabel* tipOutLabel = new QLabel("Select a shift to see its tip-out.");
    mainLayout->addWidget(tipOutLabel);

    connect(shiftList, &QListWidget::currentItemChanged, this,
            [this, tipOutLabel](QListWidgetItem* row) {
        if (!row) {
            tipOutLabel->clear();
            return;
        }

        // Read saved shift using index
        int index = row->data(Qt::UserRole).toInt();
        const ShiftData& shift = this->tracker.getShift(index);
        QString value = QString::number(shift.getTipOutValue(), 'f', 2);

        //formatting for % vs fixed
        if (shift.getTipOutType() == "Percent") {
            value += "%";
        } else {
            value = "$" + value;
        }

        tipOutLabel->setText("Saved tip-out: " + value);
    });

    editShiftButton = new QPushButton("Edit Shift");
    deleteShiftButton = new QPushButton("Delete Shift");

    mainLayout->addWidget(editShiftButton);
    mainLayout->addWidget(deleteShiftButton);

    connect(addShiftButton, &QPushButton::clicked,
            this, &MainWindow::addShiftFromInputs);

    connect(calculateButton, &QPushButton::clicked,
            this, &MainWindow::calculateTipOutFromInputs);

    connect(viewDateInput, &QDateEdit::dateChanged,
            this, &MainWindow::updateShiftList);

    connect(allShiftsBox, &QCheckBox::toggled,
            this, &MainWindow::updateShiftList);

    connect(editShiftButton, &QPushButton::clicked,
            this, &MainWindow::editSelectedShift);

    connect(deleteShiftButton, &QPushButton::clicked,
            this, &MainWindow::deleteSelectedShift);

    updateShiftList();

    setCentralWidget(mainWidget);
}

// Adds a new shift or saves changes to an existing shift
void MainWindow::addShiftFromInputs()
{
    bool hoursOk, wageOk, tipsOk, salesOk;

    double hours = hoursInput->text().toDouble(&hoursOk);
    double wage = wageInput->text().toDouble(&wageOk);
    double tips = tipsInput->text().toDouble(&tipsOk);
    double sales = salesInput->text().toDouble(&salesOk);

    if (!hoursOk || !wageOk || !tipsOk || !salesOk) {
        resultLabel->setText("Please enter valid numbers.");
        return;
    }

    if (!std::isfinite(hours) || !std::isfinite(wage) ||
        !std::isfinite(tips) || !std::isfinite(sales) ||
        hours < 0 || wage < 0 || tips < 0 || sales < 0) {
        resultLabel->setText("Values must be positive numbers.");
        return;
    }

    std::shared_ptr<TipOut> tipOutType;

    try {

        //Qt sets to false if you enter something thats not a number
        bool tipGood = false;
        double tipValue = tipValueInput->text().toDouble(&tipGood);

        //stops before adding an incorrect tip out
        if (!tipGood || !std::isfinite(tipValue) || tipValue < 0) {
            resultLabel->setText ("Enter a valid tip out");
            return;
        }

        if (tipTypeBox->currentText() == "Percent") {
            tipOutType = std::make_shared<PercentTipOut>(tipValue);
        }
        else {
            tipOutType = std::make_shared<FixedTipOut>(tipValue);
        }

        QString date = shiftDateInput->date().toString(Qt::ISODate);

        if (editingShiftIndex == -1) {
            tracker.addShift(hours, wage, tips, sales, tipOutType, date.toStdString());
            resultLabel->setText("Shift added successfully.");
        }
        else {
            ShiftData updatedShift(
                hours, wage, tips, sales, tipOutType, date.toStdString()
            );

            tracker.editShift(editingShiftIndex, updatedShift);

            editingShiftIndex = -1;
            addShiftButton->setText("Add Shift");

            resultLabel->setText("Shift updated successfully.");
        }

        updateShiftList();

    }
    catch (const std::exception& e) {
        resultLabel->setText(QString("Error: %1").arg(e.what()));
    }
}

// Calculates tip-out without adding a shift
void MainWindow::calculateTipOutFromInputs()
{
    bool valueOk;
    double tipValue = tipValueInput->text().toDouble(&valueOk);

    if (!valueOk || !std::isfinite(tipValue) || tipValue < 0) {
        resultLabel->setText("Enter a valid tip-out value.");
        return;
    }

    try {
        std::shared_ptr<TipOut> tipOutType;

        if (tipTypeBox->currentText() == "Percent") {
            tipOutType = std::make_shared<PercentTipOut>(tipValue);
        }
        else {
            tipOutType = std::make_shared<FixedTipOut>(tipValue);
        }

        double sales = 0;

        if (tipTypeBox->currentText() == "Percent") {
            bool salesOk;
            sales = salesInput->text().toDouble(&salesOk);

            if (!salesOk || !std::isfinite(sales) || sales < 0) {
                resultLabel->setText("Enter valid sales for percentage tip-out.");
                return;
            }
        }

        double tipOut = tipOutType->calculateTipOut(sales);

        resultLabel->setText(
            "Tip-Out: $" + QString::number(tipOut, 'f', 2)
        );
    }
    catch (const std::exception& e) {
        resultLabel->setText(QString("Error: %1").arg(e.what()));
    }
}

// Updates the total earnings display
void MainWindow::updateTotalEarnings()
{
    double total = 0;
    QString label = "Total Earnings: $";

    //show earnings from all shifts
    if (allShiftsBox->isChecked()) {
        total = tracker.getTotalEarnings();
    }
    else {
        //add only selected shifts
        std::string selectedDate =
            viewDateInput->date().toString(Qt::ISODate).toStdString();

        // for loop that adds up earnings for date you picked
        for (int i = 0; i < tracker.getShiftCount(); i++) {
            const ShiftData& shift = tracker.getShift(i);

            if (shift.getShiftDate() == selectedDate) {
                total += shift.calculateEarnings();
            }

            label = "Earnings for Date Selected: $";
        }
    }

    totalEarningsLabel->setText(label + QString::number(total, 'f', 2));
}

// Updates the shift history list
void MainWindow::updateShiftList()
{
    shiftList->clear();

    QString selectedDate = viewDateInput->date().toString(Qt::ISODate);

    for (int index = 0; index < tracker.getShiftCount(); index++) {
        const ShiftData& shift = tracker.getShift(index);

        if (!allShiftsBox->isChecked() &&
            shift.getShiftDate() != selectedDate.toStdString()) {
            continue;
        }

        QString rowText =
            QString::fromStdString(shift.getShiftDate()) +
            " | " + QString::number(shift.getHours()) +
            " hrs | $" + QString::number(shift.getTips(), 'f', 2);

        QListWidgetItem *item = new QListWidgetItem(rowText);

        // Store the actual Tracker index, even when the list is filtered
        item->setData(Qt::UserRole, index);

        shiftList->addItem(item);
    }

    updateTotalEarnings();
}

// Loads a selected shift into the input fields
void MainWindow::editSelectedShift()
{
    if (!shiftList->currentItem()) {
        resultLabel->setText("Select a shift first.");
        return;
    }

    int index = shiftList->currentItem()->data(Qt::UserRole).toInt();

    const ShiftData& shift = tracker.getShift(index);

    hoursInput->setText(QString::number(shift.getHours()));
    wageInput->setText(QString::number(shift.getHourlyWage()));
    tipsInput->setText(QString::number(shift.getTips()));
    salesInput->setText(QString::number(shift.getSales()));

    tipValueInput->setText(QString::number(shift.getTipOutValue()));

    tipTypeBox->setCurrentText(
        QString::fromStdString(shift.getTipOutType())
    );

    shiftDateInput->setDate(
        QDate::fromString(
            QString::fromStdString(shift.getShiftDate()),
            Qt::ISODate
        )
    );

    editingShiftIndex = index;
    addShiftButton->setText("Save Changes");

    resultLabel->setText("Edit the fields and save your changes.");
}

// Deletes a selected shift
void MainWindow::deleteSelectedShift()
{
    if (!shiftList->currentItem()) {
        resultLabel->setText("Select a shift first.");
        return;
    }

    int index = shiftList->currentItem()->data(Qt::UserRole).toInt();

    QMessageBox::StandardButton answer = QMessageBox::question(
        this,
        "Delete Shift",
        "Are you sure you want to delete this shift?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (answer != QMessageBox::Yes) {
        return;
    }

    tracker.deleteShift(index);

    editingShiftIndex = -1;
    addShiftButton->setText("Add Shift");

    updateShiftList();

    resultLabel->setText("Shift deleted.");
}
