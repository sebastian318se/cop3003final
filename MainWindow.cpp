//
// Created by Destiny Acuna on 11/12/26.
//

#include "MainWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QWidget>
#include "PercentTipOut.h"
#include<FixedTipOut.h>

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

    mainLayout->addWidget(resultLabel);

    //layout to widget
    mainWidget->setLayout(mainLayout);

    //attach widget to main
    setCentralWidget(mainWidget);



}

void MainWindow::addShiftFromInputs()
{
    double hours = hoursInput->text().toDouble();
    double wage = wageInput->text().toDouble();
    double tips = tipsInput->text().toDouble();
    double sales = salesInput->text().toDouble();
    double tipValue = tipValueInput->text().toDouble();

    std::shared_ptr<TipOut> tipOutType;

    if (tipTypeBox->currentText() == "Percent") {
        tipOutType = std::make_shared<PercentTipOut>(tipValue);
    }

    else {
        tipOutType = std::make_shared<FixedTipOut>(tipValue);

    }
    tracker.addShift(hours, wage, tips, sales, tipOutType);

    // get the shift added
    const ShiftData& shift =
        tracker.getShift(tracker.getShiftCount() - 1);

    // show the result
    resultLabel->setText(
        "Earnings: $" +
        QString::number(shift.calculateEarnings(), 'f', 2)
    );

}
