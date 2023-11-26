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
#include <QTextDocumentWriter>
#include <QFileInfo>
// Constructor de la clase MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Destructor de la clase MainWindow
MainWindow::~MainWindow()
{
    delete ui;
}

// Funcion de boton que guarda el archivo
void MainWindow::on_actionGuardar_triggered()
{
    // Cuadro de diálogo para definir el nombre y tipo de archivo a guardar
    QString nombreArch = QFileDialog::getSaveFileName(this, "Guardar", "", "Documentos RTF (*.rtf);;Documentos HTML (*.html);;Documentos PDF (*.pdf)");

    if (!nombreArch.isEmpty()) {
        QFile arch(nombreArch);
        if (arch.open(QIODevice::WriteOnly)) {
            QTextDocument *textDocument = ui->textEdit->document();

            if (textDocument) {
                if (nombreArch.toLower().endsWith(".html")) {
                    // Guardar el contenido en formato HTML
                    QTextDocumentWriter writer(nombreArch);  // Agregar la extensión .html
                    writer.write(textDocument);
                }
                 if (nombreArch.toLower().endsWith(".pdf")) {
                    // Guardar el contenido en formato PDF
                    QPrinter printer;
                    printer.setOutputFormat(QPrinter::PdfFormat);
                    printer.setOutputFileName(nombreArch);

                    QPainter painter(&printer);
                    textDocument->drawContents(&painter);
                } 
            }

            arch.close();
        } 
    }
}







// Funcion de boton que elimina todo el texto del bloc
void MainWindow::on_actionEliminar_triggered()
{
    ui->textEdit->clear();
}


// Funcion de boton que abre un archivo en el bloc
void MainWindow::on_actionAbrir_triggered()
{
    // Cuadro de diálogo para seleccionar el archivo a abrir
    QString nombreArch = QFileDialog::getOpenFileName(this, "Abrir archivo", "", "Documentos RTF (*.rtf);;Documentos HTML (*.html);;TXT (*.txt)");
    // Verifica si el nombre del archivo esta vacio
    if (!nombreArch.isEmpty()) {
        QFile arch(nombreArch);
    // Verifica si el archivo puede abrir en modo lectura
        if (arch.open(QIODevice::ReadOnly)) {
            QTextStream in(&arch);
            QString contenido = in.readAll();
            arch.close();
    // Verifica si el archivo está en formato HTML
            if (nombreArch.toLower().endsWith(".html")) {
                // Establecer el contenido en el QTextEdit para archivos HTML
                ui->textEdit->setHtml(contenido);
            }
    // Verifica si el archivo está en formato RTF
             if (nombreArch.toLower().endsWith(".rtf")) {
                // Establecer el contenido en el QTextEdit para archivos RTF
                ui->textEdit->setPlainText(contenido);

             }
            // Verifica si el archivo está en formato TXT
             if (nombreArch.toLower().endsWith(".txt")) {
                // Establecer el contenido en el QTextEdit para archivos TXT
                ui->textEdit->setPlainText(contenido);

             }

    }
}
}



void MainWindow::on_actionImprimir_triggered()
{
    // Declaración de un objeto QPrinter
QPrinter printer;

// Crea un cuadro de diálogo de impresión, asociándolo con el objeto QPrinter y el widget actual (this)
QPrintDialog printDialog(&printer, this);

// Si el usuario hace clic en "Aceptar" en el cuadro de diálogo de impresión
if (printDialog.exec() == QDialog::Accepted) {
    // Crea un objeto QTextDocument
    QTextDocument document;

    // Establece el texto del QTextDocument con el contenido del QTextEdit llamado "textEdit"
    document.setPlainText(ui->textEdit->toPlainText());

    // Imprime el documento en la impresora configurada a través del cuadro de diálogo de impresión
    document.print(&printer);
}

}


void MainWindow::on_actionEstilo_triggered()
{
    // Declaración de una variable booleana "ok"
bool ok;

// Abre un cuadro de diálogo para seleccionar la fuente y guarda la fuente seleccionada en la variable "font"
QFont font = QFontDialog::getFont(&ok, ui->textEdit->textCursor().charFormat().font(), this);

// Verifica si el usuario ha seleccionado una fuente en el cuadro de diálogo
if (ok) {
    // Obtiene el cursor de texto actual del widget QTextEdit
    QTextCursor cursor = ui->textEdit->textCursor();

    // Verifica si hay texto seleccionado
    if (cursor.hasSelection()) {
        // Crea un formato de caracteres y establece la fuente seleccionada
        QTextCharFormat format;
        format.setFont(font);

        // Aplica el formato al texto seleccionado
        cursor.setCharFormat(format);

        // Crea un formato de caracteres predeterminado y establece una fuente nula
        QTextCharFormat defaultFormat;
        defaultFormat.setFont(QFont());

        // Obtiene un cursor predeterminado y establece el formato predeterminado
        QTextCursor defaultCursor = ui->textEdit->textCursor();
        defaultCursor.setCharFormat(defaultFormat);

        // Establece el formato actual del widget al formato seleccionado
        ui->textEdit->setCurrentCharFormat(format);
    } else {
        // Si no hay texto seleccionado, simplemente establece la fuente en el formato actual
        QTextCharFormat format;
        format.setFont(font);

        // Crea un formato de caracteres predeterminado y establece una fuente nula
        QTextCharFormat defaultFormat;
        defaultFormat.setFont(QFont());

        // Obtiene un cursor predeterminado y establece el formato predeterminado
        QTextCursor defaultCursor = ui->textEdit->textCursor();
        defaultCursor.setCharFormat(defaultFormat);

        // Establece el formato actual del widget al formato seleccionado
        ui->textEdit->setCurrentCharFormat(format);
    }
}

}

void MainWindow::on_actionAlinear_Izquierda_triggered()
{
    // Obtiene el cursor de texto actual del widget QTextEdit
QTextCursor cursor = ui->textEdit->textCursor();

// Crea un formato de bloque de texto y establece la alineación a la izquierda
QTextBlockFormat format;
format.setAlignment(Qt::AlignLeft);

// Combina el formato del bloque en el cursor de texto actual
cursor.mergeBlockFormat(format);

// Establece el cursor de texto del widget QTextEdit con el nuevo formato de bloque
ui->textEdit->setTextCursor(cursor);

}

void MainWindow::on_actionAlinear_Derecha_triggered()
{
    // Obtiene el cursor de texto actual del widget QTextEdit
    QTextCursor cursor = ui->textEdit->textCursor();

    // Crea un formato de bloque de texto y establece la alineación a la derecha
        QTextBlockFormat format;
        format.setAlignment(Qt::AlignRight);

    // Combina el formato del bloque en el cursor de texto actual
        cursor.mergeBlockFormat(format);

    // Establece el cursor de texto del widget QTextEdit con el nuevo formato de bloque
    ui->textEdit->setTextCursor(cursor);
}



void MainWindow::on_actionCentrado_triggered()
{
    // Obtiene el cursor de texto actual del widget QTextEdit
    QTextCursor cursor = ui->textEdit->textCursor();

    // Crea un formato de bloque de texto y establece la alineación al centro
        QTextBlockFormat format;
        format.setAlignment(Qt::AlignCenter);

    // Combina el formato del bloque en el cursor de texto actual
        cursor.mergeBlockFormat(format);

    // Establece el cursor de texto del widget QTextEdit con el nuevo formato de bloque
    ui->textEdit->setTextCursor(cursor);
}

