#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
signals:
    void path(const QString &str);
    void testing(const QString &str, bool &flag);
private slots:
    void Ok_clicked();
    void on_folder_clicked();
};

#endif // DIALOG_H
