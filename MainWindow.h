
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QDateEdit>
#include <QListWidget>

#include "Tracker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Tracker& tracker, QWidget *parent = nullptr);

private:
    Tracker& tracker;

    QLineEdit *hoursInput;
    QLineEdit *wageInput;
    QLineEdit *tipsInput;
    QLineEdit *salesInput;
    QLineEdit *tipValueInput;

    QComboBox *tipTypeBox;

    QPushButton *addShiftButton;
    QPushButton *editShiftButton;
    QPushButton *deleteShiftButton;

    QLabel *resultLabel;
    QLabel *totalEarningsLabel;

    QDateEdit *shiftDateInput;
    QDateEdit *viewDateInput;

    QCheckBox *allShiftsBox;
    QListWidget *shiftList;

    int editingShiftIndex = -1;

    void updateShiftList();
    void updateTotalEarnings();

    void addShiftFromInputs();
    void calculateTipOutFromInputs();

    void editSelectedShift();
    void deleteSelectedShift();
};

#endif // MAINWINDOW_H
