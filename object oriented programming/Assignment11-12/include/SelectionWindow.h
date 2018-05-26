#ifndef SELECTIONWINDOW_H
#define SELECTIONWINDOW_H
#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QLayout>
#include <QDialog>

class SelectionWindow : public QDialog {
    private:
        QPushButton select{"Select", this};

    public:
        SelectionWindow();
};

#endif // SELECTIONWINDOW_H
