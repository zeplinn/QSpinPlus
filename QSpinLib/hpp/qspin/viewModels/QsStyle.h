#ifndef QSPINSTYLE_H
#define QSPINSTYLE_H

#include <QObject>
#include <QtQml>
#include <QColor>
#include <QQmlEngine>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "qspin/QObjectBase.h"
#include "qspin/QmlImportNames.h"
#include "qspin/models/IQsSerialization.h"
#include <QSharedPointer>


// QsStyle object
class QsStyle : public QObjectBase
{
    Q_OBJECT
    Q_PROPERTY(ButtonStyle* button READ button CONSTANT)
    Q_PROPERTY(GeneralStyle* general READ general CONSTANT)
    Q_PROPERTY(SpinBoxStyle* spinbox READ spinbox CONSTANT)
    Q_PROPERTY(ComboBoxStyle* combobox READ combobox CONSTANT)
    Q_PROPERTY(PromelaEditor* promelaEditor READ promelaEditor CONSTANT)
    ColorScheme* _colorScheme = qs().colorScheme();
public:
public: // properties
  ButtonStyle* button()const;
  SpinBoxStyle* spinbox()const;
  ComboBoxStyle* combobox()const;
  GeneralStyle* general()const;
  PromelaEditor* promelaEditor()const;

public:
  using QObjectBase::QObjectBase;
    static void registerAsQml();
    static QsStyle* qmlAttachedProperties(QObject* parent=nullptr);


public slots:
};
QML_DECLARE_TYPEINFO(QsStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QSPINSTYLE_H
