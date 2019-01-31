#ifndef COPYFILES_H
#define COPYFILES_H

#include <QMainWindow>
#include <QVector>
#include <set>
#include <QSettings>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QFile>
#include <QDir>

namespace Ui {
    class copyfiles;
}




class copyfiles : public QMainWindow
{
    Q_OBJECT
//    QVector <QString> vector_files;
//    QVector <QString> vector_directories;
//    QVector <QString> vector_links;//****

    QString defaull_path_to,        //дефолтный путь КУДА копировать, на всякий случай/  указывается пользователем
            defaull_path_from,      //дефолтный путь ОТКУДА копировать                /  указывается пользователем
            directoryPathTo,        //КУДА      копируем
            directoryPathFrom,      //ОТКУДА    копируем
            full_path_file;         //                                     имя файла приемника

    short int delta_month_from_user;



    uint    date_for_equal,
            date_last_copy,
            date_to_remove,
            date_current;

    //предусмотреть еще checkbox для выключения компа после сотворения бэкапа
    QSettings *settings;
    QSystemTrayIcon* trayIcon;
    bool flag_for_icon_definition;

public:

    explicit copyfiles(QWidget *parent = 0);
    ~copyfiles();

private slots:
    void start_work();
    void setToolTips();

    //services function
    unsigned int find_fresh_date();
    bool create_subdirectory(const QString & path_to, const QString & baseName);

    void setRemoveDate(const int & delta_month);
    void setCurentDate();
    uint getCurrentDate() const;
    uint getRemoveDate()const;

    void analization_directories();

    void recursion(const QString &path, QString date, std::set<QString> * directory);
    void correction_path_to();


    uint timer_for_start_copy();

    void set_settings();
    void save_settings();
    void load_settings();


    void analization_old_files(QString& remove_path);
    void remove_old_files(const QString & path_from, const uint & remove_dateMM);



    bool check_settings();

    //анализ папок, какая изменилась последней, передача в вектор имен последних измененных файлов.

    //запись файлов в лог, может еще и сравнение с логом? хотя нафиг этот лог переданных файлов?

    /*
    //получение текущей даты, - копирование вчерашних файлов. если сегодня понедельник - скопировать файлы,
    //наверное лучше просто простоанализировать все файлы и выбрать с самой последней датой что ли? а смсл..
    //можно тупо копировать вчерашние файлы, а если сегодня == пятница, то скопировать файлы в 15:30
    //а в понедельник можно и сразу вызывать exit(0);
    */

    //реализовать таймер для запуска процесса в определенное время. лучше всего это
    //делать в промежутке 14:00 -- 15:00
    //надо учесть что во время работы комп может перезапускаться, то есть нужно все таки вести лог о том, были ли
    //сегодня скопированы файлы или нет.(отчет)

    //прога должна сохарнять свой файл настроек в каких-нибудь "моих документах" ну и там же как вариант отчет

    //прога должна проверить, где она находится, и если это не путь автозапуска - то в него себя копировать.

    //создание дирректории от username и поддиректории с датой копирования в формате дд-мм-гггг



    //для серверного варианта нужно предусмотреть только время, когда будет осуществляться копирование
    //дирректорий, в какое время.
    //для сервака - удаление файлов старше одного месяца.

    //ну и самопрописка в автозапуск.


    //сохранить настройки программы.
    //считать настройки проги

    void on_Button_Test_clicked();

    void on_ButSetPathFrom_clicked();

    void on_ButSetPathTo_clicked();

    void printdir(const QString &);
    void printdir2(const QString &);

    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void closeEvent(QCloseEvent * event);
    void icon_tray_definition();

    void copy_myself_to_autorun();
    void remove_myself_from_autorun();
    void copy_myself_to_autorun_UNIX();



    void on_ButtonSettingsFile_clicked();

    void on_ButtonSaveSettingsIntoFle_clicked();

    void actiontimer();


    void on_checkBox_systemtray_stateChanged(int arg1);

    bool current_files(const QFileInfo &file);




    void on_radioButton_freshDate_clicked();

    void on_radioButton_allFiles_clicked();

private:
    Ui::copyfiles *ui;
    //vector для имен файлов.

};

#endif // COPYFILES_H

/*
 * программа для автоматического копирования файлов из пункта А в пункт В незаметно от пользователя
 *
 * программа должна выполняться скрытно от пользователя
 *
 * анализировать копируемые файлы и выбирать только свежие
 * записывать дату, когда было произведено последнее копирование и делать копирование если даты разнятся
 *
 * так же, должен быть реализован серверный вариант работы.
 *
 * реализовать "сохранение настроек программы"
 *
 *
 * со стороны сервера, программа должна копировать файлы, затем удалять их из пункта А.
 * т.к. от каждого пользователя со временем накопятся файлы за несколько месяцев, нужно
 * забацать отдельную процедуру, которая будет удалять файлы, старше 1го месяца - это сможет разгрузить
 * систему от лишнего мусора
 *
 *
*/
