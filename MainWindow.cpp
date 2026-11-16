//
// Created by Destiny Acuna on 11/12/26.
//

#include "MainWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include "PercentTipOut.h"
#include "FixedTipOut.h"

#include <exception>
#include <cmath>

//builds main TipTally window
MainWindow::MainWindow(Tracker& tracker, QWidget *parent)
    :QMainWindow(parent),
    tracker(tracker)
{
    //set title
    setWindowTitle("TipTally");

    //starting size
    setFixedSize(700,500);

    //creates QT widget acts like main (container)
    QWidget *mainWidget = new QWidget(this);

    //labels and inputs in rows (organizes inside container)
    QFormLayout *shiftInputForm = new QFormLayout();

    //starts with current date and opens calendar
    shiftDateInput = new QDateEdit(QDate::currentDate());
    shiftDateInput->setCalendarPopup(true);
    shiftInputForm->addRow("Shift Date", shiftDateInput);

    //user enters hours
    hoursInput = new QLineEdit();

    //formatting
    shiftInputForm->addRow("Hours: ", hoursInput);

    //user enters wage
    wageInput = new QLineEdit();

    shiftInputForm->addRow("Hourly Wage:", wageInput);

    //user enters tips
    tipsInput = new QLineEdit();

    shiftInputForm->addRow("Tips:", tipsInput);

    //user enters total sales
    salesInput = new QLineEdit();
    shiftInputForm->addRow("Sales:", salesInput);

    //dropdowm
    tipTypeBox = new QComboBox();

    //two tip out choices
    tipTypeBox->addItem("Percent");
    tipTypeBox->addItem("Fixed");

    shiftInputForm->addRow("Tip Out Type", tipTypeBox);

    //user enters percent or fixed
    tipValueInput = new QLineEdit();
    shiftInputForm->addRow("Tip Out Value: ", tipValueInput);

    //create add button
    addShiftButton = new QPushButton("Add Shift");

    connect(addShiftButton, &QPushButton::clicked,
        this, &MainWindow::addShiftFromInputs);

    resultLabel = new QLabel ("Results");

    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addLayout(shiftInputForm);

    mainLayout->addWidget(addShiftButton);

    //calculate tip out button
    QPushButton *calculateTipOutButton = new QPushButton("Calculate Tip-Out");
    mainLayout->addWidget(calculateTipOutButton);

    //run calculations when button pressed
    connect(calculateTipOutButton, &QPushButton::clicked,
        this, &MainWindow::calculateTipOutFromInputs);

    mainLayout->addWidget(resultLabel);

    //creates a new label below the last results
    totalEarningsLabel = new QLabel();
    mainLayout->addWidget(totalEarningsLabel);
    updateTotalEarnings();

    //show every shift
    allShiftsBox = new QCheckBox("Show every shift");
    allShiftsBox->setChecked(true);

    viewDateInput = new QDateEdit(QDate::currentDate());
    viewDateInput->setCalendarPopup(true);

    QFormLayout *historyForm = new QFormLayout();
    historyForm->addRow(allShiftsBox);
    historyForm->addRow("View Date", viewDateInput);

    shiftList = new QListWidget();
    mainLayout->addLayout(historyForm);
    mainLayout->addWidget(shiftList);

    //refresh if date is changed
    connect(viewDateInput, &QDateEdit::dateChanged,
        this, &MainWindow::updateShiftList);
    connect(allShiftsBox, &QCheckBox::toggled,
            this, &MainWindow::updateShiftList);
    updateShiftList();

    //layout to widget
    mainWidget->setLayout(mainLayout);

    //attach widget to main
    setCentralWidget(mainWidget);



}

void MainWindow::addShiftFromInputs()
{
    //Qt sets a flag when it reads each
    bool hoursGood = false;
    bool wageGood = false;
    bool tipsGood = false;
    bool salesGood = false;
    bool tipValueGood = false;

    double hours = hoursInput->text().toDouble(&hoursGood);
    double wage = wageInput->text().toDouble(&wageGood);
    double tips = tipsInput->text().toDouble(&tipsGood);
    double sales = salesInput->text().toDouble(&salesGood);
    double tipValue = tipValueInput->text().toDouble(&tipValueGood);

    //stop before adding a shift if inavlid
    if (!hoursGood || !wageGood || !tipsGood || !salesGood || !tipValueGood) {
        resultLabel->setText("Enter a valid number in every field.");
        return;
    }

    try {
        //tip out method selected
        std::shared_ptr<TipOut> tipOutType;

        if (tipTypeBox->currentText() == "Percent") {
            tipOutType = std::make_shared<PercentTipOut>(tipValue);
        }

        else {
            tipOutType = std::make_shared<FixedTipOut>(tipValue);
        }

        //records in year, month, date
        std::string date = shiftDateInput->date(). toString(Qt::ISODate).toStdString();
        tracker.addShift(hours, wage, tips, sales, tipOutType, date);
        updateShiftList(); //update after shift is added

        // get the shift added
        const ShiftData& shift =
            tracker.getShift(tracker.getShiftCount() - 1);

        // show the result
        resultLabel->setText(
            "Earnings: $" +
            QString::number(shift.calculateEarnings(), 'f', 2)
        );
    } catch (const std::exception& error) {
        resultLabel->setText(QString::fromUtf8(error.what()));
    }

}

void MainWindow::updateTotalEarnings()
{
    //Add up all shifts and show total to 2 decimals
    double total = tracker.getTotalEarnings();
    totalEarningsLabel->setText(
        "Total Earnings: S" + QString::number(total, 'f', 2)
        );
}

void MainWindow::updateShiftList()
{
    //remove visible rows
    shiftList->clear();

    //grabs date you picked formats it correctly
    std::string selectedDate =
            viewDateInput->date().toString(Qt::ISODate).toStdString();

    //goes through shifts one by one
    for (int index = 0; index < tracker.getShiftCount(); ++index) {
        const ShiftData& shift = tracker.getShift(index);

        //skip if the date is different than what we selected
        if (!allShiftsBox->isChecked() && shift.getShiftDate() != selectedDate) {
            continue;
        }

        QString dateText = shift.getShiftDate().empty()
            ? QString("No date")
            : QString::fromStdString(shift.getShiftDate());

        //hours and earning formatted as text
        QString hoursText = QString::number(shift.getHours());
        QString earningsText = QString::number(shift.calculateEarnings(), 'f', 2);

        //formatting
        QString rowText = dateText + " | " + hoursText + "hrs | $" + earningsText;
        shiftList->addItem(rowText);

    }
}

//read box if wrong input send error
static double readTipOutNumber(QLineEdit *box, const char *errorMessage)
{
    bool readGood = false;
    double number = box->text().toDouble(&readGood);

    if (!readGood || !std::isfinite(number)) {
        throw std::invalid_argument(errorMessage);
    }

    return number;
}

void MainWindow::calculateTipOutFromInputs()
{
    try {
        double tip = readTipOutNumber(tipValueInput, "Enter a valid amount");
        double amount;

        if (tipTypeBox->currentText() == "Percent") {
            double sales = readTipOutNumber(salesInput, "Enter sales amount.");
            PercentTipOut tipOut(tip);
            amount = tipOut.calculateTipOut(sales);
        }

        else {
            //doesnt need sales
            FixedTipOut tipOut(tip);
            amount = tipOut.calculateTipOut(0);
        }

        //dollars formatting
        resultLabel->setText("Tip Out: S" + QString::number(amount, 'f', 2));
    } catch (const std::exception& error) {
        resultLabel->setText(QString::fromUtf8(error.what()));
    }
}
