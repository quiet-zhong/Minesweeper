#include "MySql.h"

TopWidget::TopWidget(QWidget *parent,QString sqlSentence)
    : QWidget(parent),m_sqlSentence(sqlSentence)
{
    setSqlServerParameter("mine","root","nsznsz","localhost",3306);

    this->sqlConnect();

    //执行sql语句
    m_query->exec(m_sqlSentence);
    this->resize(420,400);
    this->sqlShow();

}

TopWidget::~TopWidget()
{
    m_db.close();
    qDebug() << "数据库关闭";
}


void TopWidget::setSqlSentence(const QString &sqlSentence)
{
    m_sqlSentence = sqlSentence;
}

//设置sql服务器参数
void TopWidget::setSqlServerParameter(const QString &DatabaseName,
                                   const QString &UserName,
                                   const QString &Password,
                                   const QString &HostName,
                                   const int &port)
{
    m_DatabaseName = DatabaseName;
    m_UserName = UserName;
    m_Password = Password;
    m_HostName = HostName;
    m_port = port;
}



void TopWidget::sqlConnect()
{
    //创建一个sqlDatabase
    m_db = QSqlDatabase::addDatabase("QMYSQL");

    /* 设置链接的相关属性 */
    //设置database名称
    m_db.setDatabaseName(m_DatabaseName);
    //设置用户名
    m_db.setUserName(m_UserName);
    //设置密码
    m_db.setPassword(m_Password);
    //设置链接地址
    m_db.setHostName(m_HostName);
    //设置端口号
    m_db.setPort(m_port);


    //判断数据库是否打开
    if(!m_db.open())
    {
        qDebug() << "数据库打开失败...";
        QMessageBox::information(this,"注意","无法连接到数据库！<br>此功能暂时无法使用");
//        return;
    }
    else
    {
        qDebug() << "数据库打开成功...";
        m_query = new QSqlQuery(m_db);
    }
}

void TopWidget::sqlShow()
{
    m_model.setQuery(*m_query);
    m_view.setParent(this);
    m_view.setModel(&m_model);
    m_view.resize(420,400);
    m_view.show();
}

