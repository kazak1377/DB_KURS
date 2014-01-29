#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QDate>
#include "dbworker.h"
#include "tablewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    dbworker *db;
    tableWidget *resultTable;
    QString actorsList;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectToDb();
private:
    Ui::MainWindow *ui;
private slots:
    void emitAddActor();
    void emitAddMovie();
    void emitAddGener();
    void emitAddDirector();
    void emitSelectFromActors();
    void emitSelectFromMovies();
    void emitSelectFromGeners();
    void emitSelectFromDirectors();
    void loadDb(QString dbFile);
    void openFileDialog();
    void addActorToList(QModelIndex);
    void addActorToListFrom(QModelIndex index);
    void showOwnQueryResult();
public slots:
    void refreshUi();
signals:
    void addActor(QString name, QDate bDate);
    void addMovie(int director, QString name, QDate releaseDate,
                  QString actors, QTime duration, int gener);
    void addGener(QString name);
    void addDirector(QString name, QDate bDate);
    void showResult(QString query);
    void selectFromActors(QString name, QDate bDate1, QDate bDate2);
    void selectFromMovies(int director, QString name, QDate releaseDate1, QDate releaseDate2,
                  QString actors, int gener, bool isDirector, bool isActors, bool isName, bool isGener);
    void selectFromGeners(QString name);
    void selectFromDirectors(QString name, QDate bDate1, QDate bDate2);
};

#endif // MAINWINDOW_H
