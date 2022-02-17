#include "appmange.h"


#include"Utilities.h"

AppMange::AppMange(int argc, char *argv[])


{



    ///https://doc.qt.io/qt-6/qtcharts-changes-qt6.html  use opengl
    qDebug()<<"USE OPENGL"<<  qputenv("QSG_RHI_BACKEND","opengl");
    QApp=qApp;



    //  init app
     InitLOG(argv[0]);//
    InitSpdlog();
    //exceptionHander();//google breakpad in process catch
    InitApp();//
    registerQmlTypes();
    initializeQmlInterface();



    connect(QApp,&QApplication::lastWindowClosed,this,&AppMange::Appclose);
    connect(QApp,&QApplication::aboutToQuit,this,&AppMange::Appquit);
    connect(QApp,&QApplication::destroyed,this,&AppMange::Appdestroy);


    connect(&qmlengine,&QQmlApplicationEngine::exit,this,&AppMange::QMLexit);
    connect(&qmlengine,&QQmlApplicationEngine::quit,this,&AppMange::QMLquit);
    connect(&qmlengine,&QQmlApplicationEngine::destroyed,this,&AppMange::QMLdestroy);





    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for(auto &s:uiLanguages){
        LOG(INFO)<<s.toStdString();
    }

    for (const QString &locale : uiLanguages) {
        const QString baseName = "CusSuperV_" + QLocale(locale).name();

        if (translator.load("./" + baseName)) {//translator/

          QApp->installTranslator(&translator);
            break;
        }
    }


        const QUrl url(QStringLiteral("qrc:/assets/main.qml") );//u"qrc:/CusSuperV/main.qml"_qs

    qmlengine.load(url);




}

AppMange::~AppMange()
{
  delete mdplc;
}
void YourFailureFunction() {
    // Reports something...
    LOG(ERROR)<<"YourFailureFunction";

}
void YourFailureWriter(const char* data, int size) {
    // Reports something...
    std::string src(data,size) ;


    LOG(ERROR)<<"YourFailureWriter"<<src;

}
void AppMange::InitLOG(const char * argv)
{
    auto checkpath=[](const std::string path){
        //std::fstream  fstrm(path.c_str(),std::ios::out) ;
        //if(!fstrm.is_open()){

        //    LOG(ERROR)<<path +" 打开失败！";
        //}
        //fstrm.close();
        QDir dir(QString::fromStdString( path));
        if(!dir.exists()){

            dir.mkpath(QString::fromStdString( path));
        }

    };

    std::string log_dir="./LOG/";

    std::string log_INFO_dir=QDir::currentPath().toStdString()+ "/LOG/INFO/";      checkpath(log_INFO_dir);
    std::string log_ERROR_dir=QDir::currentPath().toStdString()+"/LOG/ERROR/";    checkpath(log_ERROR_dir);
    std::string log_WARNNG_dir=QDir::currentPath().toStdString()+"/LOG/WARNING/"; checkpath(log_WARNNG_dir);
    std::string log_FATAL_dir=QDir::currentPath().toStdString()+"/LOG/FATAL/";    checkpath(log_FATAL_dir);


    // FLAGS_colorlogtostderr=true;
   // FLAGS_logtostderr=true;

    google::InstallFailureSignalHandler();
    google::InstallFailureWriter(&YourFailureWriter);
    google::InstallFailureFunction(&YourFailureFunction);





}

void AppMange::InitSpdlog()
{
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);
    console_sink->set_pattern("[LOG] [%^%l%$] %v");


    QString Year=QDateTime::currentDateTime().toString("yyyy");
    QString Month=QDateTime::currentDateTime().toString("MM");
    QString day=QDateTime::currentDateTime().toString("dd");
    QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh-mm-ss");
    QString LOGFILE="LOG/"+Year+"/"+Month+"/"+day+"/"+time+".txt";
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(LOGFILE.toStdString(), true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::logger spdlg("GSPDLOG", {console_sink, file_sink});
    auto t=std::make_shared<spdlog::logger>(spdlg);
    t->set_level(spdlog::level::info);



    spdlog::set_default_logger(t);
    spdlog::flush_on(spdlog::level::info);///刷新
    spdlog::set_error_handler([](const std::string &msg){

      spdlog::error("*** LOGGER ERROR ***: {}", msg);
    });

  }  catch (
      spdlog::spdlog_ex &e
      ) {
    qDebug() << "Log init failed: " << e.what() ;
  }
}


//static bool MinidumpCallback(const wchar_t* dump_path,
//                             const wchar_t* id,
//                             void* context, EXCEPTION_POINTERS* exinfo,
//                             MDRawAssertionInfo* assertion,
//                             bool succeeded)
//{
//    if (succeeded)
//    {
//        printf("dump guid is %ws\n", id);


//    }
//    fflush(stdout);

//    return succeeded;
//}
//void AppMange::exceptionHander()
//{
//    eh=new google_breakpad::ExceptionHandler(
//                L"./dump", nullptr, MinidumpCallback, nullptr,
//                google_breakpad::ExceptionHandler::HANDLER_ALL);
//}

void AppMange::InitApp()
{    // Init. application

    QApp->setApplicationName(APP_NAME);
    QApp->setApplicationVersion(APP_VERSION);
    QApp->setOrganizationName(APP_DEVELOPER);
    QApp->setOrganizationDomain(APP_SUPPORT_URL);

    // Set application style
    QApp->setStyle(QStyleFactory::create("Fusion"));
    QQuickStyle::setStyle("Fusion");
    // Load Roboto fonts from resources
    QFontDatabase::addApplicationFont(":/assets/fonts/Roboto-Bold.ttf");
    QFontDatabase::addApplicationFont(":/assets/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/assets/fonts/RobotoMono-Bold.ttf");
    QFontDatabase::addApplicationFont(":/assets/fonts/RobotoMono-Regular.ttf");

    QFontDatabase::addApplicationFont(":/assets/fonts/Hack-Bold.ttf");
    QFontDatabase::addApplicationFont(":/assets/fonts/Hack-BoldItalic.ttf");
    QFontDatabase::addApplicationFont(":/assets/fonts/Hack-Italic.ttf");
    QFontDatabase::addApplicationFont(":/assets/fonts/Hack-Regular.ttf");

    // Set Roboto as default app font
    QFont font("Hack");
#if defined(Q_OS_WIN)
    font.setPointSize(9);
#elif defined(Q_OS_MAC)
    font.setPointSize(13);
#elif defined(Q_OS_LINUX)
    font.setPointSize(10);
#endif
    qApp->setFont(font);


}

void AppMange::registerQmlTypes()
{

}

void AppMange::initializeQmlInterface()
{// Initialize modules
    auto miscThemeManager = &Misc::ThemeManager::instance();

    auto miscUtilities = &Misc::Utilities::instance();

    mdplc=new MD_PLC();
     mdplc->asyncGetdata();
   // Operating system flags
    bool isWin = false;
    bool isMac = false;
    bool isNix = false;
#if defined(Q_OS_MAC)
    isMac = true;
#elif defined(Q_OS_WIN)
    isWin = true;
#else
    isNix = true;
#endif

    // Qt version QML flag
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    const bool qt6 = false;
#else
    const bool qt6 = true;
#endif

    // Register C++ modules with QML
     auto c   = qmlengine.rootContext();
    c->setContextProperty("Cpp_Qt6", qt6);
    c->setContextProperty("Cpp_IsWin", isWin);
    c->setContextProperty("Cpp_IsMac", isMac);
    c->setContextProperty("Cpp_IsNix", isNix);
    c->setContextProperty("Cpp_ThemeManager", miscThemeManager);

    // Register app info with QML
    c->setContextProperty("Cpp_AppName", qApp->applicationName());
    c->setContextProperty("Cpp_AppUpdaterUrl", APP_UPDATER_URL);
    c->setContextProperty("Cpp_AppVersion", qApp->applicationVersion());
    c->setContextProperty("Cpp_AppOrganization", qApp->organizationName());
    c->setContextProperty("Cpp_AppOrganizationDomain", qApp->organizationDomain());
    c->setContextProperty("Cpp_Misc_Utilities", miscUtilities);
    c->setContextProperty("Cpp_MDPLC", mdplc);
    for(const QString &s:qmlengine.importPathList()){
      qDebug()<<s;
    }
}
void AppMange::Appdestroy()
{
    LOG(INFO)<<"Appdestroy";
}
void AppMange::Appquit()
{
    LOG(INFO)<<"Appquit";
}
void AppMange::Appclose()
{
    LOG(INFO)<<"Appclose";
}
void AppMange::QMLexit()
{
    LOG(INFO)<<"QMLexit";
}
void AppMange::QMLdestroy()
{
    LOG(INFO)<<"QMLdestroy";
}
void AppMange::QMLquit()
{
    LOG(INFO)<<"QMLquit";
}



