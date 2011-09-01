#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_wyczyscButton_clicked();
    void on_actionOprogramie_triggered();
    void on_actionZako_triggered();
    void obliczCene();

};

#endif // MAINWINDOW_H
