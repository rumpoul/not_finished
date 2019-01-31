#include "dialog.h"
#include "ui_dialog.h"
#include <QPushButton>
#include <QFileDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), SLOT(Ok_clicked()));
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), SLOT(close()));
    ui->folder->setStyleSheet("none");
}

void Dialog::Ok_clicked()
{

    emit path(ui->lineEdit->text());
    close();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_folder_clicked()
{

    QString name = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                "/home",
                                                QFileDialog::ShowDirsOnly
                                                | QFileDialog::DontResolveSymlinks);
    if (!name.isNull()){
        ui->lineEdit->setText(name);
    }
}
