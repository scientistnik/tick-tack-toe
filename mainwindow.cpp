#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qsrand(static_cast<quint64>(QTime::currentTime().msecsSinceStartOfDay()));

    for (int i=0; i< 3*3; i++)
        pole[i] = i + 1 + '0';

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(CompRun()));
    timer->setSingleShot(true);

    have_empty = true;
    game_over = false;
    isHumanRun = false;

}

void MainWindow::paintEvent(QPaintEvent * /*ev*/)
{
   QPainter painter(this);
   QPen pen;

   pen.setWidth(10);
   pen.setColor(Qt::black);
   painter.setPen(pen);

   // game pole
   painter.drawLine(100, 0, 100, 300);
   painter.drawLine(200, 0, 200, 300);
   painter.drawLine(0, 100, 300, 100);
   painter.drawLine(0, 200, 300, 200);

   const int SHORT = 20;

   for (int i=0; i < 3*3; i++) {
       if (pole[i] == 'X') {
            int deltaX = 100*(i%3);
            int deltaY = 100*(i/3);

            pen.setWidth(5);
            pen.setColor(Qt::blue);
            painter.setPen(pen);

            painter.drawLine(0 + SHORT + deltaX, 0 + SHORT + deltaY,100 - SHORT + deltaX,100 - SHORT+ deltaY);
            painter.drawLine(0 + SHORT + deltaX,100 - SHORT + deltaY,100 - SHORT + deltaX,0 + SHORT + deltaY);
       }
       else if (pole[i] == 'O') {
            pen.setWidth(5);
            pen.setColor(Qt::red);
            painter.setPen(pen);

            int deltaX = 100*(i%3);
            int deltaY = 100*(i/3);

            painter.drawEllipse(0 + SHORT + deltaX, 0 + SHORT + deltaY, 100 - SHORT*2, 100 - SHORT*2);
       }
   }

   findEmpty();
   isGameOver();


   if (!have_empty || game_over) {
       pen.setColor(Qt::black);
       painter.setPen(pen);

       QFont font("Ubuntu",35,QFont::Bold);
       painter.setFont(font);

       painter.drawText(10+2,150+35/2 +2, "GAME OVER");

       pen.setColor(Qt::green);
       painter.setPen(pen);
       painter.setFont(font);

       painter.drawText(10,150+35/2, "GAME OVER");

   }
   else if (isHumanRun)
       isHumanRun = false;
   else
       isHumanRun = true;
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if (!have_empty || game_over) {
        clearPole();
        if (!isHumanRun)
            timer->start(1000);
        return;
    }

    if (!isHumanRun)
        return;

    int x = event->x();
    int y = event->y();

    int index = 0;
    /*    index
     *  1 | 2 | 3
     * ---|---|---
     *  4 | 5 | 6
     * ---|---|---
     *  7 | 8 | 9
     */

    if (x <= 100) index = 1;
    else if (x <= 200) index = 2;
    else index = 3;

    if (y <= 100) index += 0;
    else if (y <= 200) index += 3;
    else index += 6;

    index--;

    if (pole[index] != 'X' && pole[index] != 'O') {
        pole[index] = 'X';
    }

    repaint();

    if (have_empty && !game_over)
        timer->start(1000);

}
void MainWindow::CompRun()
{
    if (!have_empty || game_over || isHumanRun)
        return;

    int i;

    do {
        i = qrand()%9;
    } while (pole[i] == 'X' || pole[i] == 'O');

    pole[i] = 'O';

    repaint();
}

void MainWindow::findEmpty()
{
    for (int i=0; i< 3*3; i++)
        if (pole[i] != 'X' && pole[i] != 'O') {
            have_empty = true;
            return;
        }

    have_empty = false;
}

void MainWindow::isGameOver()
{
    for (int i=0; i< 3; i++)
        if ( (pole[i*3] == pole[i*3+1] && pole[i*3+1] == pole[i*3+2]) ||
             (pole[i] == pole[i+3] && pole[i+3] == pole[i+6])) {
            game_over = true;
            return;
        }

    if ( (pole[0] == pole[4] && pole[4] == pole[8]) ||
         (pole[2] == pole[4] && pole[4] == pole[6])) {
        game_over = true;
        return;
    }
}

void MainWindow::clearPole()
{
    for (int i=0;i < 3*3; i++)
        pole[i] = i + 1 + '0';

    game_over = false;
    have_empty = true;

    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}
