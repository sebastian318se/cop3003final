
#include <iostream>
#include <stdexcept>
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

    try {
        tracker.loadFromFile("shifts.txt");
    }
    //catch exception call it error tell me why
    catch (const std::exception&error) {
        std:: cout << "Loading error: " << error.what() << "\n";
    }

    MainWindow window(tracker);

    window.show();


    return app.exec();
}