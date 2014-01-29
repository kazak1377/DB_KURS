#include "dbworker.h"

dbworker::dbworker(QObject *parent) : QObject(parent)
{
}

dbworker::dbworker(QString name)
{
    qDebug()<<"Constructor with params";
    db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db->setDatabaseName(name);
    if (!db->open())
    {
        qDebug() << db->lastError().text();
    }
    //add check for table content
    query = new QSqlQuery();
    query->exec( "CREATE TABLE IF NOT EXISTS `movies` ( "
                 " `movie_id`       INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                 " `duration`       TIME,"
                 " `date`           DATE,"
                 " `name`           TEXT,"
                 " `director_id`    INTEGER NOT NULL,"
                 " `gener`          INTEGER NOT NULL,"
                 " `actors_list`      TEXT"
                 "  )");
    qDebug()<<query->lastError().text();
    query->exec("CREATE TABLE IF NOT EXISTS `actors` ("
                 " `actor_id`       INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                 " `name`           TEXT,"
                 " `birthdate`       DATE)");
    query->exec("CREATE TABLE IF NOT EXISTS `geners` ("
                 " `gener_id`       INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                 " `name`           TEXT)");
    query->exec("CREATE TABLE IF NOT EXISTS `directors` ("
                 " `director_id`    INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
                 " `name`           TEXT,"
                 " `birthdate`      DATE)");
    qDebug()<<query->lastError().text();
}

void dbworker::addActor(QString name, QDate bDate)
{
    qDebug()<<"addActor:   "<<name<<"    "<<bDate.toString("dd/MM/yyyy");
    query->prepare("INSERT INTO `actors` (name,birthdate) VALUES (:name,:birthdate)");
    query->bindValue(":name",name);
    query->bindValue(":birthdate",bDate);
    query->exec();
    query->clear();
    qDebug()<<query->lastError();
}

void dbworker::addMovie(int director, QString name, QDate releaseDate,
                        QString actors, QTime duration, int gener)
{
    query->prepare("INSERT INTO `movies` (duration,date,name,director_id,gener,actors_list) VALUES"
                   "(:duration,:releaseDate,:name,:director,:gener,:actorsList)");
    query->bindValue(":duration",duration.toString("hh:mm:ss"));
    query->bindValue(":releaseDate",releaseDate);
    query->bindValue(":name",name);
    query->bindValue(":director",director);
    query->bindValue(":gener",gener);
    query->bindValue(":actorsList",actors);
    query->exec();
    query->clear();
    qDebug()<<query->lastError();

}

void dbworker::addGener(QString name)
{
    qDebug()<<"addGener:   "<<name;
    query->prepare("INSERT INTO `geners` (name) VALUES (:name)");
    query->bindValue(":name",name);
    query->exec();
    query->clear();
    qDebug()<<query->lastError();
}

void dbworker::addDirector(QString name, QDate bDate)
{
    qDebug()<<"addDeirector:   "<<name<<"    "<<bDate.toString("dd/MM/yyyy");
    query->prepare("INSERT INTO `directors` (name,birthdate) VALUES (:name,:birthdate)");
    query->bindValue(":name",name);
    query->bindValue(":birthdate",bDate);
    query->exec();
    query->clear();
    qDebug()<<query->lastError();
}

