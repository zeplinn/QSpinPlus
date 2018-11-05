#ifndef QSTABLEHANDLER_H
#define QSTABLEHANDLER_H
#include <QObject>
#include <QRegularExpression>
#include "qspin/QpropertyHelper.h"
#include <QAbstractListModel>
class QsTableColumn;

namespace{
}
class QsTableColumn: public QObject{
    Q_OBJECT
    // ################ properties ###########################################
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    QString _text, _text_role;
public:
    QString text()const;
    void setText(QString value);
signals:
    void textChanged();
    // ############## End Properties ########################################
private:
    static const QRegularExpression& trim(){
        static QRegularExpression r("^([a-zA-Z_].)");
        return r;
    }
public:
    explicit QsTableColumn(QObject* parent = nullptr): QObject( parent){
    }
    QString textRole()const{ return _text_role; }

};

//class QsAbstractTableModel: public QAbstractListModel{
//    Q_OBJECT
//    // ##################### begin properties #####################################

//    // ###################### end properties ######################################


//private:
//    QList<QsTableColumn*>* _columns;
//public:
//    void setColumns(QList<QsTableColumn>* columns){
//        _columns;
//    }
//};

class QsTableHandler: public QObject{
    Q_OBJECT
    // ##################### begin properties #####################################
    //Q_PROPERTY(QAbstractListModel* model READ model WRITE setModel NOTIFY modelChanged)


    // ###################### end properties ######################################
};

#endif // QSTABLEHANDLER_H
