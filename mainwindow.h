#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void on_command_browse_clicked();

    void on_icon_browse_clicked();

    void on_path_browse_clicked();

    void on_save_clicked();

    void on_iconEdit_textChanged(const QString &arg1);

    void on_open_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
