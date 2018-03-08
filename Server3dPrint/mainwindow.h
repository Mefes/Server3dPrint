#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include "server.h"
#include "gcodeeditor.h"
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
    Server *server;
    GcodeEditor editor;
//       editor.setWindowTitle(QObject::tr("Code Editor Example"));
//       editor.show();
public slots:
    void openFile();

};

#endif // MAINWINDOW_H
