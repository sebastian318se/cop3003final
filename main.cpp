
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <QMessageBox>
#include <QApplication>

#include "ShiftData.h"
#include "Tracker.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{

    //creates Qt app
    QApplication app(argc, argv);

    //main tracker
    Tracker tracker;

    bool canSave = false;

    try {
        // no file might be there
        if (std::filesystem::exists("shifts.txt")) {
            tracker.loadFromFile("shifts.txt");
        }

        canSave = true;
    }
    catch (const std::exception& error) {
        QMessageBox::warning(
            nullptr,
            "Could not load shifts",
            QString("Original file saved. "
                    "Changes made will not be saved.\n\n%1")
                .arg(QString::fromUtf8(error.what()))
        );
    }


    MainWindow window(tracker);

    window.show();

    
    int exitCode = app.exec();

    if (!canSave) {
        return exitCode;
    };

    try {
        tracker.saveInFile("shifts.txt");
    }
    catch (const std::exception& error) {
        std::cout << "Saving Error: " << error.what() << "\n";
    }

    return exitCode;
}