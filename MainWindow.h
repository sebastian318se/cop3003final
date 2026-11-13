//
// Created by Destiny Acuna on 11/12/26.
//

#ifndef COP3003FINAL_MAINWINDOW_H
#define COP3003FINAL_MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "Tracker.h"

//main GUI window for TipTally
class MainWindow : public QMainWindow
{
private:

    //reference to tracker
    Tracker& tracker;

    //inputs
    QLineEdit *hoursInput;
    QLineEdit *wageInput;
    QLineEdit *tipsInput;
    QLineEdit *salesInput;

    //percent or fixed tips dropdown menu
    QComboBox * tipTypeBox;

    // input for % or fixed
    QLineEdit *tipValueInput;

    //button to add shift
    QPushButton *addShiftButton;

    //results displayed after a shift is added
    QLabel *resultLabel;

    //runs when add shift button clicked
    void addShiftFromInputs();

public:
    //create main application
    MainWindow(Tracker& tracker, QWidget *parent = nullptr);
};


#endif //COP3003FINAL_MAINWINDOW_H