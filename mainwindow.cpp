#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QTextFrame>
#include <QPainter>

// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionGuardar_triggered()
{
    QString nombreArch = QFileDialog::getSaveFileName(this, "Guardar", "", "Documentos RTF (*.rtf);;Documentos PDF (*.pdf)");

    if (!nombreArch.isEmpty()) {
        QFile arch(nombreArch);

        if (arch.open(QIODevice::WriteOnly)) {
            QTextDocument *textDocument = ui->textEdit->document();

            if (nombreArch.endsWith(".rtf", Qt::CaseInsensitive)) {
                // Guardar el contenido en formato RTF
                arch.write(textDocument->toHtml().toUtf8());
            } else if (nombreArch.endsWith(".pdf", Qt::CaseInsensitive)) {
                // Guardar el contenido en formato PDF
                QPrinter printer;
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setOutputFileName(nombreArch);

                QPainter painter(&printer);
                textDocument->drawContents(&painter);
            }

            arch.close();
        } else {
            // Manejar el error al abrir el archivo
            QMessageBox::warning(this, "Error", "No se pudo abrir el archivo para escribir.");
        }
    }
}



void MainWindow::on_actionEliminar_triggered()
{
    ui->textEdit->clear();
}



void MainWindow::on_actionAbrir_triggered()
{
    QFile arch;
    QTextStream io;
    QString nombreArch;
    nombreArch=QFileDialog::getOpenFileName(this,"Abrir");
    arch.setFileName(nombreArch);
    arch.open(QIODevice::ReadOnly | QIODevice::Text);
    io.setDevice(&arch);
    ui->textEdit->setPlainText(io.readAll());
    arch.flush();
    arch.close();

}


void MainWindow::on_actionImprimir_triggered()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    if (printDialog.exec() == QDialog::Accepted) {
        QTextDocument document;
        document.setPlainText(ui->textEdit->toPlainText());
        document.print(&printer);
    }
}


void MainWindow::on_actionEstilo_triggered()
{
    bool ok;
 QFont font = QFontDialog::getFont(&ok, ui->textEdit->textCursor().charFormat().font(), this);


    if (ok) {
        QTextCursor cursor = ui->textEdit->textCursor();

        if (cursor.hasSelection()) {
            QTextCharFormat format;
            format.setFont(font);
            cursor.setCharFormat(format);
            QTextCharFormat defaultFormat;
            defaultFormat.setFont(QFont());
            QTextCursor defaultCursor = ui->textEdit->textCursor();
            defaultCursor.setCharFormat(defaultFormat);
            ui->textEdit->setCurrentCharFormat(format);
        } else {

            QTextCharFormat format;
            format.setFont(font);
            QTextCharFormat defaultFormat;
            defaultFormat.setFont(QFont());

            QTextCursor defaultCursor = ui->textEdit->textCursor();
            defaultCursor.setCharFormat(defaultFormat);
            ui->textEdit->setCurrentCharFormat(format);
        }
    }
}

void MainWindow::on_actionAlinear_Izquierda_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat format;
        format.setAlignment(Qt::AlignLeft);
        cursor.mergeBlockFormat(format);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::on_actionAlinear_Derecha_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat format;
        format.setAlignment(Qt::AlignRight);
        cursor.mergeBlockFormat(format);
    ui->textEdit->setTextCursor(cursor);
}



void MainWindow::on_actionCentrado_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
        QTextBlockFormat format;
        format.setAlignment(Qt::AlignCenter);
        cursor.mergeBlockFormat(format);

    ui->textEdit->setTextCursor(cursor);
}

