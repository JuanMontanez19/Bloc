#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionGuardar_triggered();

    void on_actionEliminar_triggered();

    void on_actionAbrir_triggered();

    void on_actionImprimir_triggered();

    void on_actionEstilo_triggered();

    void on_actionTama_po_triggered();

    void on_actionSubrayado_triggered();

    void on_actionNegrita_triggered();

    void on_actionAlinear_Izquierda_triggered();

    void on_actionAlinear_Derecha_triggered();

    void on_actionCentrado_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
