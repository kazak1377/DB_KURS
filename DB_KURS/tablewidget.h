#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDate>

namespace Ui {
class tableWidget;
}

class tableWidget : public QMainWindow
{
    Q_OBJECT
    QSqlTableModel *model;
public:
    explicit tableWidget(QWidget *parent = 0);
    ~tableWidget();

private:
    Ui::tableWidget *ui;
public slots:
    void showExecutedQuery(QString request);
    void selectActor(QString name, QDate bDate1, QDate bDate2);
    void selectMovie(int director, QString name, QDate releaseDate1, QDate releaseDate2,
                  QString actors, int gener, bool isDirector, bool isActors, bool isName, bool isGener);
    void selectGener(QString name);
    void selectDirector(QString name, QDate bDate1, QDate bDate2);
    void editMoviesTable();
    void editGenersTable();
    void editActorsTable();
    void editDirectTable();
    void exportTable();
};

#endif // TABLEWIDGET_H
