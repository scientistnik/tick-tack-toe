#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event);

    void findEmpty();
    void isGameOver();
    void clearPole();

public slots:
    void CompRun();

private:
    Ui::MainWindow *ui;
    char pole[3*3];
    bool have_empty;
    bool game_over;
    bool isHumanRun;
    QTimer *timer;
};

#endif // MAINWINDOW_H
