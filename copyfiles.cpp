#include "copyfiles.h"
#include "ui_copyfiles.h"
#include "dialog.h"

#include <QString>
#include <QIODevice>
#include <QDebug>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>


#include <QTimer>
#include <QStandardPaths>


//#include <QTCore/QCoreApplication>

//for demonstration
void demostr(){

}
//end demo
copyfiles::copyfiles(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::copyfiles)
{
    ui->setupUi(this);
//    this->setFixedSize(572, 473);//536 * 252
    this->setFixedSize(536, 252);


    emit setToolTips();


    flag_for_icon_definition=false;


    emit set_settings();


    defaull_path_from="";
    defaull_path_to="";
    delta_month_from_user=ui->spinBox->value();
    emit load_settings();

    QFile *file=new QFile ("readme.txt", this);

    if (ui->checkBox_autorun->isChecked()&&file->exists()){

        emit start_work();
    }
}

copyfiles::~copyfiles()
{
    delete ui;
}

bool removing_equals_month(const uint& toDayDate, const uint& RemoveDate, const int &delta_month);

void copyfiles::setRemoveDate(const int& delta_month){
    date_to_remove= date_current-((delta_month+1)*30);
}
void copyfiles::setCurentDate(){
    date_current =  QDate::currentDate().toString("d").toUInt()+
                    QDate::currentDate().toString("M").toUInt()*30+
                    QDate::currentDate().toString("yyyy").toUInt()*365;
}
uint copyfiles::getCurrentDate() const{
    return date_current;
}
uint copyfiles::getRemoveDate() const{
    return date_to_remove;
}


void copyfiles::actiontimer()
{
    emit analization_directories();

    if( (getCurrentDate() - settings->value("last_remove", 0).toUInt()) < (delta_month_from_user*30)
            /* !removing_equals_month(getCurrentDate(),
                              getRemoveDate(),
                              delta_month_from_user)*/
      )
    {
        emit analization_old_files(defaull_path_to);

        //задать дату удаления в settings и отталкиваться от нее,
        //чтобы не нагружать бедные серваки с памятью в 1 гб...
        settings->setValue("last_remove",getCurrentDate());
    }

    if(ui->checkBox_remove_after_copy->isChecked()){
         //надо грамотно втыкнуть условие мнгновенного удаления.//КУДА?
         emit remove_old_files(defaull_path_from,date_current);
    }
}

uint copyfiles::timer_for_start_copy()
{
    int hour = QTime::currentTime().toString("h").toInt();
    int min  = QTime::currentTime().toString("m").toInt();

    int def_hour, def_min;
    def_hour = ui->timeEdit->time().toString("h").toInt();
    def_min  = ui->timeEdit->time().toString("m").toInt();

    int delta_hours, delta_min;

    if(hour>def_hour)
        delta_hours = def_hour+24-hour;
    if(min>def_min){
        --delta_hours;
        delta_min = def_min+60-min;
    } else {
        delta_min = def_min-min;
    }
    return delta_hours*60*60+delta_min*60;
}

void copyfiles::setToolTips(){
    ui->ButSetPathFrom->setToolTip("set 'start' directory");
    ui->ButSetPathTo->setToolTip("set 'final' directory, \nfiles will be copying into \n'\\final directory\\username(who exec copying)\\date of copy in format MM.DD.YYYY'");

    ui->ButtonSaveSettingsIntoFle->setToolTip("save settings into file");
    ui->ButtonSettingsFile->setToolTip("open settings from file, after loading settings, you needed to Apply they.");

    ui->checkBox_remove_after_copy->setToolTip("removing files imideatly in 'from' directory");
    ui->checkBox_systemtray->setToolTip("this is server_mode, copy will be start on timer");
    ui->checkBox_autorun->setToolTip("if system tray not checked, \nfiles will be copying with start System, \nhide from user");

    ui->pushButton->setToolTip("Settings must be installing or programm not will be working");

    ui->label->setToolTip("for server_mode, files removing from repository \n('final' directory)");
}
/*

*/


void get_current_Date(QString &mydate){
    mydate = QDate::currentDate().toString("dd.MM.yy");
}
void get_current_Time(QString &mytime){
    mytime = QTime::currentTime().toString();
}


#include <vector>
#include <set>
#include <QByteArray>


void copyfiles::start_work(){

    QDir* not_exist = new QDir(defaull_path_from);
    if(! not_exist->exists()){ delete not_exist; exit(0);}
    delete not_exist;

    correction_path_to();//createPath need
    if(!ui->checkBox_systemtray->isChecked()){//не серверный вариант, => делать копии после запуска шиндовс
        if(settings->value("last_copy_date",0).toUInt()==getCurrentDate()){
            //клиентский вариант
            exit(0);     //сегодня было копирование, выходим
        }   else    {
            //имеет смысл паузу поставить минуты на 2
            emit actiontimer();

            settings->setValue("last_copy_date", getCurrentDate());
            //записали сегодняшнюю дату последнего копирования

            exit(0);
        }
    }   else {  //серверный вариант работы, по таймеру
        QTimer *tim = new QTimer(this);
        connect(tim,SIGNAL(timeout()),this,SLOT(actiontimer()));
        tim->start(timer_for_start_copy()*1000);//!!!
    }
}

//      copiyng block   START
void copyfiles::correction_path_to(){
    //    QString str="\\\\192.168.0.102\\debian";
    #if defined(Q_OS_WIN)
        #define qUsername QString::fromLocal8Bit (qgetenv ("USERNAME").constData ()).toUtf8 ()
    #elif defined(Q_OS_UNIX)
        #define qUsername qgetenv("USER").constData ()
    #endif

        directoryPathTo = defaull_path_to;
        QDir directory(directoryPathTo);
        QString nowDate= QDate::currentDate().toString("MM-dd-yyyy");

//        directory.mkdir(qUsername);
//        directory.cd(qUsername);
//        directory.mkdir(nowDate);
//        directory.cd(nowDate);

        directoryPathTo+= "\\"+qUsername+"\\"+nowDate;

        if(!directory.mkpath(directoryPathTo+"\\")) exit(0);
        //создали дирректории в конечной папке, куда будет происходить копирование.
        //  в формате \\заданный путь\\имя пользователя\\текущая дата

//        qDebug()<< directoryPathTo;
//        directoryPathTo.left( directoryPathTo.length()-1);  //kill last two slashes '//'
}

bool copyfiles::create_subdirectory(const QString& path_to, const QString &baseName){

    QDir directory(path_to+"\\"+baseName);
    return directory.mkpath(path_to+"\\"+baseName);
}
unsigned int earlier_file_info(const QFileInfo &file){  //chiken or egg?
    unsigned int date_created = file.created().toString("d").toInt() +
                                file.created().toString("M").toInt()*30 +
                                file.created().toString("yyyy").toInt()*365;
    unsigned int date_modify = file.lastModified().toString("d").toInt() +
                               file.lastModified().toString("M").toInt()*30 +
                               file.lastModified().toString("yyyy").toInt()*365;

    if(date_created>date_modify){
        return date_created;
    }
    return date_modify;
}

bool copyfiles::current_files(const QFileInfo &file){

    return (earlier_file_info(file) > date_last_copy);
}


unsigned int copyfiles::find_fresh_date(){

    unsigned int search_date = QDate::currentDate().toString("d").toInt()     +
                               QDate::currentDate().toString("M").toInt()*30  +
                               QDate::currentDate().toString("yyyy").toInt()*365;

    QDir FromDir(directoryPathFrom);    //получили дирректорию, прогоняем ее:

    //прогоняем дирректорию для поиска свежей даты
    for (const auto& iter : FromDir.entryInfoList()){
        if(current_files(iter))
        {
            return search_date;
        }
    }
    return 0;
}

//блочное копирование файла
void execute_copying(const QString &path_from, const QString &path_to, const QString &file_name){

    QFile file_from(path_from);             file_from.open(QIODevice::ReadOnly);

    QFile file_to(path_to+"\\"+file_name);  file_to.open(QIODevice::WriteOnly);

    if(!file_from.isOpen()){
        qDebug()<< "file_from not open"<< path_from;
    }
    if(!file_to.isOpen()){
        qDebug()<< "file_to not open"<< "path-to: "<<path_to<<"  name: "<<file_name;
    }

    char buffer[1024];
    while(!file_from.atEnd()){
        int block_size = file_from.read(buffer, sizeof(buffer));
        file_to.write(buffer, block_size);
    }

    file_from.close();
    file_to.close();
}
void copyfiles::recursion(const QString &path,
                              QString path_to,
                             std::set<QString> *directory)
{

    void execute_copying(const QString &path_from, const QString &path_to, const QString &file_name);


    QDir dir(path);
    int i =2;
    for( const QFileInfo& temp: dir.entryInfoList() )
    {
        if(i){ --i; continue;}

        if (!current_files(temp))
            continue;

        if(temp.isSymLink()){
            QFileInfo check(temp.symLinkTarget());
//            qDebug()<< "**************LNK**********************";
//            qDebug() << "temp name:  " <<temp.baseName() << "\ncheck.name: "<< check.baseName();
//            qDebug() << "temp.LinkTarget: "<< temp.symLinkTarget()
//                     << "\n check.filepath:  "<< check.filePath()<<"\ncheck.filename:  "<< check.fileName();
            if(check.isDir()){
                //add to set
                if(directory->insert(check.filePath()).second==false)
                    continue;


//                qDebug() << "create subdir in"<< path_to << "  on baseName: "<< check.baseName() << "\nfilename: "<< check.fileName();
                if(!create_subdirectory(path_to, check.fileName())){
//                    qDebug()<< "\n SUBDIR NOT CREATED\n";
                    break;
                }

                //call recursion
//                qDebug() << "call rec for lnk:"<< temp.absoluteFilePath()<<endl;
                recursion(check.filePath(),path_to+"\\"+check.fileName(), directory);
//                continue;
//                qDebug()<< "****************END LNK**********************";

            }

            continue;
        }

        if(temp.isDir() &&!temp.isSymLink())
        {
            if(directory->insert(temp.absoluteFilePath()).second==false) continue;//add dir in set
            //добавляем элемент в множество и проверяем на успешное добавление,
            //если не успешно - уже есть в множестве, идем на следующую операцию

//            qDebug() << "create subdir in"<< path_to << "  on baseName: "<< temp.baseName() << "\nfilename: "<< temp.fileName();
            if(!create_subdirectory(path_to, temp.fileName())){
                qDebug()<< "\n SUBDIR NOT CREATED\n";
                break;
            }

            //здесь создаем новый подкаталог по basename() или что то такое
            //и меняем путь куда копировать с учетом этого каталога

//            qDebug() << "call rec for dir: "<< temp.absoluteFilePath()<< " path_to: "<< path_to;

            recursion(temp.absoluteFilePath(),path_to+"\\"+temp.fileName(), directory); //call recursion
            continue;//return;
        }


//        qDebug() << "---------------------------------------";
////        qDebug() << "call exec copy for absoluteFilePath: "<< temp.absoluteFilePath()<<endl;
//        qDebug() << "call exec copy for filePath: "<< temp.filePath()<<endl;
//        qDebug() << "call exec copy for fileName: "<< temp.fileName()<<endl;
//        qDebug() << "path_to: "<< path_to;
//        qDebug() << "---------------------------------------";
        if(!temp.isSymLink())
        execute_copying(temp.filePath(),path_to, temp.fileName());
        //до суда этого фрагмента кода дойдет только файл и его можно пихать в переливать по текущему пути..
    }

}
void copyfiles::analization_directories(){

    if( date_current==settings->value("last_copy_date",0).toUInt())
            return; //not found  or nothing to copy

    //здесь могла быть ваша рекурсия
    std::set<QString> *directoriyes = new std::set<QString> ();
    recursion(defaull_path_from, directoryPathTo,directoriyes);

//    qDebug()<<"set directoryes:";
//    for (const auto &i: *directoriyes){
//        qDebug()<< i;
//    }
    directoriyes->clear();
    delete directoriyes;

    settings->setValue("last_copy_date",date_current);
}
//      copiyng block   END




//  REMOVING BLOCK  start

void copyfiles::analization_old_files(QString & remove_path)
{

    emit remove_old_files(remove_path, getRemoveDate());
}



bool removing_equals_month(const uint& toDayDate,
                           const uint& removeDate,
                           const int &delta_month)
{
    //сравниваем с дельтой, полученной от пользователя
//    int delta_month=3;

    return ((int)(toDayDate-removeDate) > (delta_month+1)*30);
}

//removing recursion                                            //getcurrentdate("MM");
void copyfiles::remove_old_files(const QString &path_from, const uint &remove_date)
{
        QDir dir(path_from);
        int i =2;
        for(const QFileInfo& temp: dir.entryInfoList() )
        {
            if(i){--i;continue;}

            //здесь надо наверное преобразование к инт приводить и сравнивать по месяцам,
            //если разница больше --заданной пользователем-- то удалять
            if( !removing_equals_month(remove_date,
                                      earlier_file_info(temp),
                                      delta_month_from_user)
              ){
                qDebug() << "remove_date: "<<remove_date <<"\nfile_info: "<<earlier_file_info(temp)
                         <<"\n delta from user: "<< delta_month_from_user;
                continue;
            }

            if(temp.isDir()) // true - is directory
            {
                remove_old_files(temp.absoluteFilePath(), remove_date);
                temp.dir().rmdir(temp.fileName());
            }
            if(temp.isFile()){
                //remove(temp.absoluteFilePath().toStdString());
                if(!QFile::remove(temp.absoluteFilePath()))
                    qDebug()<< "can't remove: "<< temp.absoluteFilePath();
            }
        }
}
//  REMOVING BLOCK  end

// SETTINGS BLOCK    start
void copyfiles::on_radioButton_freshDate_clicked()
{
    ui->radioButton_allFiles->setChecked(false);
}
void copyfiles::on_radioButton_allFiles_clicked()
{
    ui->radioButton_freshDate->setChecked(false);
}

void copyfiles::set_settings(){
#if defined(Q_OS_WIN)
      settings = new QSettings("help_for_sysadmins", "backupper",this);
#elif defined(Q_OS_UNIX)
      settings = new QSettings("settings.conf", QSettings::NativeFormat,this);
#endif
}
void copyfiles::save_settings()
{

//    QSettings *settings = new QSettings("settings.conf",QSettings::NativeFormat);

    if(ui->checkBox_systemtray->isChecked())
        settings->setValue("systemtray",1);
    else
        settings->setValue("systemtray",0);

    if(ui->checkBox_autorun->isChecked())
        settings->setValue("autorun",1);
    else
        settings->setValue("autorun",0);

    if(ui->radioButton_freshDate->isChecked()){
        settings->setValue("radioBtn",1);
        settings->setValue("last_copy_date",date_current);
    } else {
        settings->setValue("radioBtn",0);
        settings->setValue("last_copy_date",0);
    }

    settings->setValue("defPathFrom", defaull_path_from);
    settings->setValue("defPathTo", defaull_path_to);

    settings->setValue("delta_month",  delta_month_from_user);
    settings->setValue("time_to_copy", ui->timeEdit->time());



    settings->sync(); //записываем настройки

}
void copyfiles::load_settings()
{
    /* открываем файл с настройками для считывания */
    if(settings->value("systemtray").toInt()==1)
        ui->checkBox_systemtray->setChecked(true);
    else
        ui->checkBox_systemtray->setChecked(false);

    if(settings->value("autorun").toInt()==0)
        ui->checkBox_autorun->setChecked(false);
    else
        ui->checkBox_autorun->setChecked(true);
    if(settings->value("radioBtn").toInt()==1)
        ui->radioButton_freshDate->setChecked(true);
    else
        ui->radioButton_allFiles->setChecked(true);

    defaull_path_from = settings->value("defPathFrom").toString();
    ui->label_FROM->setText(defaull_path_from);

    defaull_path_to=settings->value("defPathTo").toString();
    ui->label_TO->setText(defaull_path_to);

    delta_month_from_user=settings->value("delta_month",2).toInt();
    ui->timeEdit->setTime(settings->value("time_to_copy").toTime());

    date_last_copy = settings->value("last_copy_date",0).toUInt();
    //date_last_removing = settings->value("last_remove_date", 2000*365).toUInt();
    emit setCurentDate();
    emit setRemoveDate(delta_month_from_user);

}

//проверить дирректории на существование,
//проверить путь на КУДА созданием файла и удалением.
#include <QTextStream>
bool copyfiles::check_settings(){
    if(defaull_path_from==defaull_path_to){
        QMessageBox::information(this, "Wrong path", "Dirrectories 'start' and 'final' is equal");
        return false;
    }
    if((defaull_path_from=="" && defaull_path_to==""))
    {
        QMessageBox::information(this,"Wrong path", "you must set right path");
        return false;
    } else {
        //проверка путей, создание дирректорий, файлов
        QDir directory(defaull_path_to);

        int i =0; //critical errors count

        if(!directory.mkdir("test")){

            //not ok            
            QMessageBox::critical(this,"Wrong", "i can't create subdirectory in final path");
            ++i;
        }

        if(!directory.rmdir("test")){    //удаляем дирректорию


            QMessageBox::warning(this,"Wrong", "i can't remove subdirectory in final path");
//            ++i;
        }


        QString read_str="", test_str = "963258741";

        QFile file_from(defaull_path_from+"\\test.txt"); //создаем файл в начальной дирректории,
                                            //записываем в него тестовую строку если удалось - хорошо

        if(!file_from.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,"Wrong", "i can't open to write file in start path");
//            ++i;
        }   else {

            QTextStream testing_files (&file_from);
            testing_files << test_str; //<< endl;
            file_from.close();
        }
        if(!file_from.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,"Wrong", "i can't read file in start path");
            ++i;
        }   else {
            QTextStream testing_files (&file_from);
            testing_files >> read_str; //<< endl;
            file_from.close();
        }
        if(test_str!=read_str){
             QMessageBox::warning(this,"Wrong", "error read/write files in start path");
        }


        file_from.remove();

        test_str = "654789123";     read_str="";

        QFile file_to(defaull_path_to+"\\test.txt");//создаем файл в конечной дирректории,
                                              //записываем в него тестовую строку если удалось - хорошо

        if(!file_to.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,"Wrong", "i can't open to write file in final path");
            ++i;
        }   else {
            QTextStream testing_files_to (&file_to);
            testing_files_to << test_str; //<< endl;
            file_to.close();
        }
        if(!file_to.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this,"Wrong", "i can't open to read file in final path");
//            ++i;
        }   else {
            QTextStream testing_files_to (&file_to);
            testing_files_to >> read_str; //<< endl;
            file_to.close();
        }

        file_to.remove();

        if(test_str!=read_str){
             QMessageBox::critical(this,"Wrong", "error read/write files in final path");
             ++i;
        }
        if(i!=0){
            QMessageBox::information(this, "Possibly resolve",
                                     "Perhaps, you don't have necessary access "
                                     "rights for read/write in that directories");
            return false;
        }
    }
    return true;
}

// SETTINGS BLOCK    end





                            //  GUI

void copyfiles::on_ButSetPathFrom_clicked()
{
    Dialog *wnd = new Dialog(this);
    wnd->show();
    connect(wnd,SIGNAL(path(QString)), this, SLOT(printdir(QString)));
}
void copyfiles::printdir(const QString & path){
        ui->label_FROM->setText("From: "+ path);
        defaull_path_from=path;
}

void copyfiles::on_ButSetPathTo_clicked()
{
    Dialog *wnd = new Dialog(this);
    wnd->show();
    connect(wnd,SIGNAL(path(QString)), this, SLOT(printdir2(QString)));
}
void copyfiles::printdir2(const QString &path){
    ui->label_TO->setText("TO: "+path);
    defaull_path_to=path;
}


void copyfiles::copy_myself_to_autorun(){
    QSettings *settings1;
#ifdef Q_OS_WIN32
    settings1 = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings1->setValue("backupper", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
                  //    ^^^APPLICATION_NAME
    settings1->sync();
#endif
    delete settings1;
}
void copyfiles::remove_myself_from_autorun(){
    QSettings *settings1;
#ifdef Q_OS_WIN32
    settings1 = new QSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings1->remove( "backupper");//APPLICATION_NAME
#endif
    delete settings1;
}

//APPLY_SETTINGS
void copyfiles::on_pushButton_clicked()
{
    //checked_dir
    if(!check_settings()){
        return;
    }

    emit save_settings();

#if defined(Q_OS_WIN)
    if(ui->checkBox_autorun->isChecked())
        emit copy_myself_to_autorun();
    else
        emit remove_myself_from_autorun();

#elif defined(Q_OS_UNIX)
    emit copy_myself_to_autorun_UNIX();
#endif
    if(!ui->checkBox_systemtray->isChecked()){
        QFile *file = new QFile("readme.txt", this);
        file->open(QIODevice::WriteOnly);
        file->write(" kill me to execute");
    }


    QMessageBox::information(this, "All ok", "Settings is applied!");
}

void copyfiles::on_spinBox_valueChanged(int arg1)
{
    if(arg1==1) ui->label_2->setText("месяца");
    else ui->label_2->setText("месяцев");
    delta_month_from_user=ui->spinBox->value();
}


void copyfiles::icon_tray_definition(){
    /* Инициализируем иконку трея, устанавливаем иконку из набора системных иконок,
         * а также задаем всплывающую подсказку
         * */

        trayIcon = new QSystemTrayIcon(this);
        //trayIcon->setIcon(this->style()->standardIcon(QStyle::SP_ComputerIcon));
        trayIcon->setIcon(QIcon(":/img/glass.png"));

        trayIcon->setToolTip("Backupper");
        /* После чего создаем контекстное меню из двух пунктов*/
        QMenu * menu = new QMenu(this);
        QAction * viewWindow = new QAction(trUtf8("Open window"), this);
        QAction * quitAction = new QAction(trUtf8("Exit"), this);

        /* подключаем сигналы нажатий на пункты меню к соответсвующим слотам.
         * Первый пункт меню разворачивает приложение из трея,
         * а второй пункт меню завершает приложение
         * */
        connect(viewWindow, SIGNAL(triggered()), this, SLOT(show()));
        connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

        menu->addAction(viewWindow);
        menu->addAction(quitAction);

        /* Устанавливаем контекстное меню на иконку
         * и показываем иконку приложения в трее
         * */
        trayIcon->setContextMenu(menu);
        trayIcon->show();

        /* Также подключаем сигнал нажатия на иконку к обработчику
         * данного нажатия
         * */
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
        connect(trayIcon,SIGNAL(quitAction),this, SLOT(close()));
}
void copyfiles::closeEvent(QCloseEvent * event){
    /* Если окно видимо и чекбокс отмечен, то завершение приложения
     * игнорируется, а окно просто скрывается, что сопровождается
     * соответствующим всплывающим сообщением
     */
    if(this->isVisible() && ui->checkBox_systemtray->isChecked()){
        event->ignore();
        this->hide();

//        QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);
//        trayIcon->showMessage("Tray Program",
//                              trUtf8("Приложение свернуто в трей. Для того чтобы, "
//                                     "развернуть окно приложения, щелкните по иконке приложения в трее"),
//                              icon,
//                              2000);
    }
}
void copyfiles::iconActivated(QSystemTrayIcon::ActivationReason reason){
    switch (reason){
    case QSystemTrayIcon::Trigger:
        /* Событие игнорируется в том случае, если чекбокс не отмечен
         * */
        if(ui->checkBox_systemtray->isChecked()){
            /* иначе, если окно видимо, то оно скрывается,
             * и наоборот, если скрыто, то разворачивается на экран
             * */
            if(!this->isVisible()){
                this->show();
            } else {
                this->hide();
            }
        }
        break;
    default:
        break;
    }
}


void copyfiles::copy_myself_to_autorun_UNIX(){
    // Путь к папке автозапуска
    QString autostartPath = QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0) + QLatin1String("/autostart");
    /* Проверяем, существует ли директория, в которой будет храниться файл автозапуска.
     * А то мало ли... пользователь удалил...
     * */
    QDir autorunDir(autostartPath);
    if(!autorunDir.exists()){
        // Если не существует, то создаём
        autorunDir.mkpath(autostartPath);
    }
    QFile autorunFile(autostartPath + QLatin1String("/AutorunLinux.desktop"));
    /* Проверяем состояние чекбокса, если отмечен, то добавляем приложения в автозапуск.
     * В противном случае удаляем
     * */
    if(ui->checkBox_autorun->isChecked()) {
        // Далее проверяем наличие самого файла автозапуска
        if(!autorunFile.exists()){

            /* Далее открываем файл и записываем в него необходимые данные
             * с указанием пути к исполняемому файлу, с помощью QCoreApplication::applicationFilePath()
             * */
            if(autorunFile.open(QFile::WriteOnly)){

                QString autorunContent("[Desktop Entry]\n"
                                       "Type=Application\n"
                                       "Exec=" + QCoreApplication::applicationFilePath() + "\n"
                                       "Hidden=false\n"
                                       "NoDisplay=false\n"
                                       "X-GNOME-Autostart-enabled=true\n"
                                       "Name[en_GB]=AutorunLinux\n"
                                       "Name=AutorunLinux\n"
                                       "Comment[en_GB]=AutorunLinux\n"
                                       "Comment=AutorunLinux\n");
                QTextStream outStream(&autorunFile);
                outStream << autorunContent;
                // Устанавливаем права доступа, в том числе и на исполнение файла, иначе автозапуск не сработает
                autorunFile.setPermissions(QFileDevice::ExeUser|QFileDevice::ExeOwner|QFileDevice::ExeOther|QFileDevice::ExeGroup|
                                       QFileDevice::WriteUser|QFileDevice::ReadUser);
                autorunFile.close();
            }
        }
    } else {
        // Удаляем файл автозапуска
        if(autorunFile.exists()) autorunFile.remove();
    }
}



void copyfiles::on_ButtonSettingsFile_clicked()
{
    QString name = QFileDialog::getOpenFileName(this,
                                                "Open settings",
                                                QCoreApplication::applicationDirPath(),
                                                "Settings file (*.setconf)");

    if (!name.isNull()){

    QFile portable_settings_open (name);
    if(portable_settings_open.open(QIODevice::ReadOnly)){
        QTextStream file(&portable_settings_open);

        defaull_path_from   = file.readLine();
        defaull_path_to     = file.readLine();
        ui->label_FROM->setText(defaull_path_from);
        ui->label_TO->setText(defaull_path_to);
        ui->timeEdit->setTime(QTime::fromString(file.readLine(), "hhmm"));
        ui->spinBox->setValue(file.readLine().toInt());

        if(file.readLine()=="true"){
            ui->checkBox_autorun->setChecked(true);
        }else {
            ui->checkBox_autorun->setChecked(false);
        }

        if(file.readLine()=="true"){
            ui->checkBox_systemtray->setChecked(true);
        }else {
            ui->checkBox_systemtray->setChecked(false);
        }
        portable_settings_open.close();
    }

    emit on_pushButton_clicked();//APPLY SETTINGS
    }
}

void copyfiles::on_ButtonSaveSettingsIntoFle_clicked()
{
    if(check_settings())
    {
    QString name = QFileDialog::getSaveFileName(this,
                                                "Save settings",
                                                QCoreApplication::applicationDirPath(),
                                                "Settings file (*.setconf)");

    QFile portable_settings_save (name);//portable_settings_save

    if(portable_settings_save.open(QIODevice::WriteOnly)){
        QTextStream file(&portable_settings_save);
        file << defaull_path_from <<endl;
        file << defaull_path_to<<endl;
        file << ui->timeEdit->time().toString("hhmm")<<endl;
        file << ui->spinBox->value()<<endl;

        if(ui->checkBox_autorun->isChecked()){
            file<< "true"<<endl;
        }else {
            file<< "false"<<endl;
        }

        if(ui->checkBox_systemtray->isChecked()){
            file<< "true"<<endl;
        }else {
            file<< "false"<<endl;
        }
        portable_settings_save.close();

    }


    }//end if

}


//  status bar


void copyfiles::on_checkBox_systemtray_stateChanged(int arg1)
{
    if(!flag_for_icon_definition){

        flag_for_icon_definition= true;
        emit icon_tray_definition();
    }
}



void copyfiles::on_Button_Test_clicked()    //  TESTING     <<-----------------------------
{
    if ( ui->radioButton_allFiles->isChecked() ){
    date_last_copy =0;
    settings->setValue("last_copy_date",date_last_copy);
    emit start_work();

//    emit analization_directories();


    int     day   = QDate::currentDate().toString("d").toInt(),      //текущий день
            year  = QDate::currentDate().toString("yyyy").toInt(),
            month = QDate::currentDate().toString("M").toInt();

    int summary_days = day+ month*30+ year*365;
    ui->textBrowser->append(QString::number(summary_days));
    }
    int io = delta_month_from_user;
    if ( ui->radioButton_freshDate->isChecked() ){
        delta_month_from_user = -1;
        emit remove_old_files(directoryPathTo,date_current);
    }
    delta_month_from_user = io;



    /*
     *
    QRegExp reg("[a-zA-Z]{1,5}[1-9]{1}[0-9]{0,3}");//регулярные выражения форматируют пользовательский ввод
      //данная запись в [] означает диапазон допустимых вводимых значений
      //запись {} означает минимальное/максимальное количество символов

    ui->lineEdit->setValidator(new QRegExpValidator(reg,this));//в данном случае, при задании проверщика(валидатора)
    //выделяется память под объект ^ этого класса, который принимает значение expression(регулярного выражения)
    //и принимает родителя. и потому необходимо указать родителя, т.к. выделяемая память не привязана к указателю,
    //и соответственно, деструктор формы эту память не затронет
     *
     *
     *
     *
    QFile file_from(path_from);
    QFile file_to(path_to+"\\"+file_name);
    if(!file_from.isOpen()){
        qDebug()<< "file_from not open"<< path_from;
    }
    if(!file_to.isOpen()){
        qDebug()<< "file_to not open"<< path_to+"\\"+file_name;
    }

    char buffer[1024];
    while(!file_from.atEnd()){
        int block_size = file_from.read(buffer, sizeof(buffer));
        file_to.write(buffer, block_size);
    }

    file_from.close();
    file_to.close();

     *
    */
}


QString recursion1(QString path,QString &result)
{
//    qDebug() << "вошли в рекурсию"<<endl;
    QDir dir(path);


    int i =2;
    for( QFileInfo temp: dir.entryInfoList() )
    {

        if(i){ --i;continue;}

        result+=" "+temp.absoluteFilePath();


        if(temp.isDir()) // true - is directory
        {

            result+="   --dir-- \n";
            recursion1(temp.absoluteFilePath(),result);
        }
        else result+='\n';
    }
    return result;
}

