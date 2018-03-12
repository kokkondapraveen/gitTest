#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTimer>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void my_tfunction();
    void updateProgressBar();

    void loadvalues();
    void addloadvalues();
    void secvalue();
    void minvalue();
    void insertvalues();

private slots:


    void on_Door_clicked();



    void on_start_clicked();

    void on_plus_clicked();

    void on_minus_clicked();

    void on_Door_toggled(bool checked);

    void on_Door_clicked(bool checked);

    void on_Door_close_clicked();

    void on_Door_pressed();

    void on_pushButton_skip_clicked();

    void on_plus_pressed();

    void on_push_reset_clicked();

    void on_push_skip_clicked();

    void on_push_preload_clicked();

    void on_pushButton_sensor_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *objTimer;
    QTimer *progress;



};

#endif // MAINWINDOW_H
