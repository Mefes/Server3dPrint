#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new Server(6000,this);
    connect(ui->actionOpen_G_File,SIGNAL(triggered()),this,SLOT(openFile()));
//    ui->gcodeeditor->setWindowTitle(QObject::tr("Code Editor Example"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QFile file;
    if (file.isOpen())
            file.close();
    QString fileName_DATA;
    fileName_DATA = QFileDialog::getOpenFileName(this, tr("Open File"),"/home",tr("GCODE (*.gcode)"));
    file.setFileName(fileName_DATA);// создаем объект класса QFile
    if (file.open(QIODevice::ReadOnly)){
    QTextStream   in(&file);
//    int i=0;
//       while (!in.atEnd())
       {
           ui->gCodeEditor->insertPlainText(in.readAll());
//           ui->tableWidget->insertRow( i );

//           ui->listWidget_GFile->addItem(in.readLine());
//          QTableWidgetItem *num = new QTableWidgetItem(QString(i));
//           ui->tableWidget->setItem(i,0,num);
//           QTableWidgetItem *gcode = new QTableWidgetItem(in.readLine());
//           ui->tableWidget->setItem(i++,0,gcode);
//           if(line.startsWith("G")||line.startsWith("M"))
//           {
//               //SearchError
//               gcode.append(line);
//               if (gcode.last().indexOf(";") >= 0)
//                   gcode.last().truncate(gcode.last().indexOf(";"));
//           }
       }
    }
}
