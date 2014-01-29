#include "tablewidget.h"
#include "ui_tablewidget.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QFileDialog>

tableWidget::tableWidget(QWidget *parent) : QMainWindow(parent), ui(new Ui::tableWidget)
{
    ui->setupUi(this);
    model = new QSqlTableModel;
    ui->resultTableWidget->setModel(model);
    connect(ui->action,SIGNAL(triggered()),this,SLOT(exportTable()));
}

tableWidget::~tableWidget()
{
    delete ui;
}

void tableWidget::showExecutedQuery(QString request)
{
    QSqlQueryModel *myModel = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery;
    query->exec(request);
    myModel->setQuery(*query);
    ui->resultTableWidget->setModel(myModel);
    this->show();
}

void tableWidget::selectActor(QString name, QDate bDate1, QDate bDate2)
{
    QSqlQueryModel *myModel = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery;
    if(name == "" || name == " ")
    {
        query->prepare("SELECT * FROM actors WHERE birthdate BETWEEN :date1 AND :date2");
        query->bindValue(":date1",bDate1);
        query->bindValue(":date2",bDate2);
        query->exec();
        qDebug()<<query->lastError();
    }
    else
    {
        query->prepare("SELECT * FROM actors WHERE LOWER(name) LIKE LOWER('%"+name+
                       "%') AND  birthdate BETWEEN :date1 AND :date2");
        query->bindValue(":date1",bDate1);
        query->bindValue(":date2",bDate2);
        //query->bindValue(":name2",name);
        query->exec();
        qDebug()<<query->executedQuery();
        qDebug()<<query->lastError();
    }
    myModel->setQuery(*query);
    ui->resultTableWidget->setModel(myModel);
    this->show();
}

void tableWidget::selectMovie(int director, QString name, QDate releaseDate1, QDate releaseDate2,
                              QString actors, int gener, bool isDirector, bool isActors,
                              bool isName, bool isGener)
{
    QString request = "SELECT movies.duration, movies.date, movies.name,movies.actors_list,"
            " geners.name AS gener, directors.name AS director FROM movies"
            " LEFT OUTER JOIN geners ON geners.gener_id = movies.gener"
            " LEFT OUTER JOIN directors ON movies.director_id = directors.director_id WHERE";
    qDebug()<<releaseDate1<<" "<<releaseDate2;
    if (isDirector)
        request += " movies.director_id = :directorid";
    if (isActors && isDirector)
        request += " AND movies.actors_list LIKE '%"+actors+"%'";
    else if (isActors)
        request += " movies.actors_list  LIKE '%"+actors+"%'";
    if (isName && (isActors || isDirector))
        request += " AND movies.name LIKE '%"+name+"%'";
    else if(isName)
        request += " movies.name LIKE '%"+name+"%'";
    if (isGener && (isActors || isDirector || isName))
        request += " AND movies.gener = :generid";
    else if(isGener)
        request += " movies.gener = :generid";
    if (isGener || isName || isActors || isDirector)
        request += " AND movies.date BETWEEN :date1 AND :date2";
    else
        request += " movies.date BETWEEN :date1 AND :date2";
    QSqlQueryModel *myModel = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery;
    query->prepare(request);
    query->bindValue(":date1",releaseDate1);
    query->bindValue(":date2",releaseDate2);
    query->bindValue(":directorid",director);
    query->bindValue(":generid",gener);
    query->exec();
    qDebug()<<query->executedQuery();
    qDebug()<<query->lastError();
    myModel->setQuery(*query);
    ui->resultTableWidget->setModel(myModel);
    this->show();
}

void tableWidget::selectGener(QString name)
{
    QString request = "SELECT * FROM geners WHERE LOWER(name) LIKE LOWER('%"+name+"%')";
    QSqlQueryModel *myModel = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery;
    query->exec(request);
    myModel->setQuery(*query);
    ui->resultTableWidget->setModel(myModel);
    this->show();
}

void tableWidget::selectDirector(QString name, QDate bDate1, QDate bDate2)
{
    QSqlQueryModel *myModel = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery;
    if(name == "" || name == " ")
    {
        query->prepare("SELECT * FROM directors WHERE birthdate BETWEEN :date1 AND :date2");
        query->bindValue(":date1",bDate1);
        query->bindValue(":date2",bDate2);
        query->exec();
        qDebug()<<query->lastError();
    }
    else
    {
        query->prepare("SELECT * FROM directors WHERE LOWER(name) LIKE LOWER('%"+name+"%') AND"
                       " birthdate BETWEEN :date1 AND :date2");
        query->bindValue(":date1",bDate1);
        query->bindValue(":date2",bDate2);
        query->exec();
        qDebug()<<query->executedQuery();
        qDebug()<<query->lastError();
    }
    myModel->setQuery(*query);
    ui->resultTableWidget->setModel(myModel);
    this->show();
}

void tableWidget::editMoviesTable()
{
    model->setTable("movies");
    model->select();
    ui->resultTableWidget->setModel(model);
    this->show();
}

void tableWidget::editGenersTable()
{
    model->setTable("geners");
    model->select();
    ui->resultTableWidget->setModel(model);
    this->show();
}

void tableWidget::editActorsTable()
{
    model->setTable("actors");
    model->select();
    ui->resultTableWidget->setModel(model);
    this->show();
}

void tableWidget::editDirectTable()
{
    model->setTable("directors");
    model->select();
    ui->resultTableWidget->setModel(model);
    this->show();
}


void tableWidget::exportTable()
{
    QString toOpen = QFileDialog::getSaveFileName(this,tr("сохранить в файл"),
                                                  "C:",
                                                  tr("Coma-separeted values (*.csv)"));
    QFile file(toOpen);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    QString exportStr = "";
    for (int col = 0; col < ui->resultTableWidget->model()->columnCount(); col++)
        exportStr += ui->resultTableWidget->model()->headerData(col,Qt::Horizontal,Qt::DisplayRole).toString()+";";
    exportStr+="\n";
    for (int i = 0; i < ui->resultTableWidget->model()->rowCount(); i++)
    {
        for (int j = 0; j<ui->resultTableWidget->model()->columnCount(); j++)
        {
            exportStr +=ui->resultTableWidget->model()->data(ui->resultTableWidget->model()->index(i,j)).toString()+
                    ";";
        }
        exportStr +="\n";
    }
    qDebug()<<exportStr;
    out << exportStr;
    file.close();
    qDebug()<<"closed";
}



