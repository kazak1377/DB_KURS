#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QDate>

class dbworker : public QObject
{
    Q_OBJECT
    QSqlDatabase *db;
    QSqlQuery *query;
public:
    explicit dbworker(QObject *parent = 0);
    dbworker(QString name);
signals:

public slots:
    void addActor(QString name, QDate bDate);
    void addMovie(int director, QString name, QDate releaseDate,
                  QString actors, QTime duration, int gener);
    void addGener(QString name);
    void addDirector(QString name,QDate bDate);
};

#endif // DBWORKER_H
