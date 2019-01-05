#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include <QTextCodec>
#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QMessageBox>


class TopWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopWidget(QWidget *parent = 0,QString sqlSentence = "show tables");
    ~TopWidget();

    void setSqlSentence(const QString &sqlSentence);

    void setSqlServerParameter(const QString &DatabaseName,
                                       const QString &UserName,
                                       const QString &Password,
                                       const QString &HostName = "localhost",
                                       const int & port = 3306);


    void sqlShow();

private:
    void sqlConnect();

    QString m_sqlSentence;//要执行的sql语句

    QString m_DatabaseName;
    QString m_UserName;
    QString m_Password;
    QString m_HostName;
    int m_port;

    QSqlDatabase m_db;
    QSqlQuery * m_query;
    QSqlQueryModel m_model;
    QTableView m_view;
};

#endif // TOPWIDGET_H
