#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actorsList = "";
    ui->movieGenerFrom->setEnabled(false);
    ui->movieDirectorFrom->setEnabled(false);
    ui->actorDateEdit->setMaximumDate(QDate::currentDate());
    ui->actorDateEditFrom->setMaximumDate(QDate::currentDate());
    ui->actorDateEditFrom->setDate(QDate::fromString("1900-01-01","yyyy-MM-dd"));
    ui->actorDateEditTo->setMaximumDate(QDate::currentDate());
    ui->actorDateEditTo->setDate(QDate::currentDate());
    ui->directorDateEdit->setMaximumDate(QDate::currentDate());
    ui->directorDateEditFrom->setMaximumDate(QDate::currentDate());
    ui->directorDateEditFrom->setDate(QDate::fromString("1900-01-01","yyyy-MM-dd"));
    ui->directorDateEditTo->setMaximumDate(QDate::currentDate());
    ui->directorDateEditTo->setDate(QDate::currentDate());
    ui->movieDateEdit->setMaximumDate(QDate::currentDate());
    ui->movieDateEditFrom->setMaximumDate(QDate::currentDate());
    ui->movieDateEditFrom->setDate(QDate::fromString("1900-01-01","yyyy-MM-dd"));
    ui->movieDateEditTo->setMaximumDate(QDate::currentDate());
    ui->movieDateEditTo->setDate(QDate::currentDate());
    //ui->movieActorsFrom->setSelectionBehavior();
    connect(ui->openFileAction,SIGNAL(triggered()),this,SLOT(openFileDialog()));
    connect(ui->addActorButton,SIGNAL(clicked()),this,SLOT(emitAddActor()));
    connect(ui->addMovieButton,SIGNAL(clicked()),this,SLOT(emitAddMovie()));
    connect(ui->addGenerButton,SIGNAL(clicked()),this,SLOT(emitAddGener()));
    connect(ui->addDirectorButton,SIGNAL(clicked()),this,SLOT(emitAddDirector()));
    connect(ui->selectActorButton,SIGNAL(clicked()),this,SLOT(emitSelectFromActors()));
    connect(ui->movieAddActorsList,SIGNAL(clicked(QModelIndex)),this,SLOT(addActorToList(QModelIndex)));
    connect(ui->movieActorsFrom,SIGNAL(clicked(QModelIndex)),this,SLOT(addActorToListFrom(QModelIndex)));
    connect(ui->selectDirectorButton,SIGNAL(clicked()),this,SLOT(emitSelectFromDirectors()));
    connect(ui->selectGenerButton,SIGNAL(clicked()),this,SLOT(emitSelectFromGeners()));
    connect(ui->execOwnPushButton,SIGNAL(clicked()),this,SLOT(showOwnQueryResult()));
    connect(ui->selectMoviesButton,SIGNAL(clicked()),this,SLOT(emitSelectFromMovies()));
    ui->tabWidget->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::emitAddActor()
{
    connect(this,SIGNAL(addActor(QString,QDate)),db,SLOT(addActor(QString,QDate)));
    emit addActor(ui->actorNameLineEdit->text(),ui->actorDateEdit->date());
    disconnect(this,SIGNAL(addActor(QString,QDate)),db,SLOT(addActor(QString,QDate)));
    ui->statusBar->showMessage("Actor added",3000);
    refreshUi();
}

void MainWindow::emitAddMovie()
{
    QStringList test;
    test << "1"<<"2"<<"23"<<"32";
    connect(this,SIGNAL(addMovie(int,QString,QDate,QString,QTime,int)),db,
            SLOT(addMovie(int,QString,QDate,QString,QTime,int)));
    emit addMovie(ui->movieDirectorSelector->currentIndex()+1,ui->movieNameLineEdit->text(),
                  ui->movieDateEdit->date(),
                  ui->movieAddedActors->text().remove(ui->movieAddedActors->text().length()-1,1),
                  ui->movieTimeEdit->time(),ui->movieGenerSelector->currentIndex()+1);
    disconnect(this,SIGNAL(addMovie(int,QString,QDate,QString,QTime,int)),db,
               SLOT(addMovie(int,QString,QDate,QString,QTime,int)));
    ui->statusBar->showMessage("Movie added",3000);
    refreshUi();
}

void MainWindow::emitAddGener()
{
    connect(this,SIGNAL(addGener(QString)),db,SLOT(addGener(QString)));
    emit addGener(ui->generNameLineEdit->text());
    disconnect(this,SIGNAL(addGener(QString)),db,SLOT(addGener(QString)));
    ui->statusBar->showMessage("Gener added",3000);
    refreshUi();
}

void MainWindow::emitAddDirector()
{
    connect(this,SIGNAL(addDirector(QString,QDate)),db,SLOT(addDirector(QString,QDate)));
    emit addDirector(ui->directorNameLineEdit->text(),ui->directorDateEdit->date());
    disconnect(this,SIGNAL(addDirector(QString,QDate)),db,SLOT(addDirector(QString,QDate)));
    ui->statusBar->showMessage("Director added",3000);
    refreshUi();
}

void MainWindow::emitSelectFromActors()
{
    connect(this,SIGNAL(selectFromActors(QString,QDate,QDate)),resultTable,SLOT(selectActor(QString,QDate,QDate)));
    emit selectFromActors(ui->actorNameLineEditFrom->text(),ui->actorDateEditFrom->date(),ui->actorDateEditTo->date());
    disconnect(this,SIGNAL(selectFromActors(QString,QDate,QDate)),resultTable,SLOT(selectActor(QString,QDate,QDate)));
}

void MainWindow::emitSelectFromMovies()
{
    bool isDirector = ui->checkBox->isChecked();
    bool isGener = ui->checkBox_2->isChecked();
    bool isActor;
    bool isName;
    if (ui->movieNameLineEditFrom->text() == "" || ui->movieNameLineEditFrom->text() == " ")
        isName = false;
    else
        isName = true;
    if (ui->addedActorsFrom->text() == "" || ui->addedActorsFrom->text() == " ")
        isActor = false;
    else
        isActor = true;
    connect(this,SIGNAL(selectFromMovies(int,QString,QDate,QDate,QString,int,bool,bool,bool,bool)),
            resultTable,SLOT(selectMovie(int,QString,QDate,QDate,QString,int,bool,bool,bool,bool)));
    emit selectFromMovies(ui->movieDirectorFrom->currentIndex() + 1,ui->movieNameLineEditFrom->text(),
                          ui->movieDateEditFrom->date(),ui->movieDateEditTo->date(),
                          ui->addedActorsFrom->text(),ui->movieGenerFrom->currentIndex()+1,isDirector,
                          isActor,isName,isGener);
    disconnect(this,SIGNAL(selectFromMovies(int,QString,QDate,QDate,QString,int,bool,bool,bool,bool)),
            resultTable,SLOT(selectMovie(int,QString,QDate,QDate,QString,int,bool,bool,bool,bool)));
}

void MainWindow::emitSelectFromGeners()
{
    connect(this,SIGNAL(selectFromGeners(QString)),resultTable,SLOT(selectGener(QString)));
    emit selectFromGeners(ui->generNameLineEditFrom->text());
    disconnect(this,SIGNAL(selectFromGeners(QString)),resultTable,SLOT(selectGener(QString)));
}

void MainWindow::emitSelectFromDirectors()
{
    connect(this,SIGNAL(selectFromDirectors(QString,QDate,QDate)),resultTable,SLOT(selectDirector(QString,QDate,QDate)));
    emit selectFromDirectors(ui->directorNameLineEditFrom->text(),ui->directorDateEditFrom->date(),ui->directorDateEditTo->date());
    disconnect(this,SIGNAL(selectFromDirectors(QString,QDate,QDate)),resultTable,SLOT(selectDirector(QString,QDate,QDate)));
}

void MainWindow::loadDb(QString dbFile)
{
    db = new dbworker(dbFile);
    resultTable = new tableWidget();
    connect(this,SIGNAL(showResult(QString)),resultTable,SLOT(showExecutedQuery(QString)));
    connect(ui->editMoviesTable,SIGNAL(triggered()),resultTable,SLOT(editMoviesTable()));
    connect(ui->editGenersTable,SIGNAL(triggered()),resultTable,SLOT(editGenersTable()));
    connect(ui->editActorsTable,SIGNAL(triggered()),resultTable,SLOT(editActorsTable()));
    connect(ui->editDirectTable,SIGNAL(triggered()),resultTable,SLOT(editDirectTable()));
    ui->tabWidget->setDisabled(false);
    refreshUi();
}

void MainWindow::openFileDialog()
{
    QString toOpen = QFileDialog::getOpenFileName(this,tr("Открыть базу"),
                                                  "C:",
                                                  tr("SQLite db files (*.sqlite)"));
    loadDb(toOpen);
}

void MainWindow::addActorToList(QModelIndex index)
{
    ui->movieAddedActors->insert(index.data().toString() + ",");
}

void MainWindow::addActorToListFrom(QModelIndex index)
{
    ui->addedActorsFrom->setText(index.data().toString());
}

void MainWindow::showOwnQueryResult()
{
    emit showResult(ui->queryEdit->toPlainText());
}

void MainWindow::refreshUi()
{
    qDebug()<<"REFRESHING";
    QSqlQueryModel *directors = new QSqlQueryModel;
    QSqlQuery *directorsQuery = new QSqlQuery();
    directorsQuery->exec("SELECT name FROM directors");
    directors->setQuery(*directorsQuery);
    ui->movieDirectorSelector->setModel(directors);
    ui->movieDirectorFrom->setModel(directors);
    QSqlQueryModel *actors = new QSqlQueryModel;
    QSqlQuery *actorsQuery = new QSqlQuery();
    actorsQuery->exec("SELECT name FROM actors");
    actors->setQuery(*actorsQuery);
    ui->movieAddActorsList->setModel(actors);
    ui->movieActorsFrom->setModel(actors);
    QSqlQueryModel *geners = new QSqlQueryModel;
    QSqlQuery *genersQuery = new QSqlQuery();
    genersQuery->exec("SELECT name FROM geners");
    geners->setQuery(*genersQuery);
    ui->movieGenerFrom->setModel(geners);
    ui->movieGenerSelector->setModel(geners);
}

