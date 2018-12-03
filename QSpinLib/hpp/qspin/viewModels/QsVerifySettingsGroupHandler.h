#ifndef QSVERIFYSETTINGSGROUPHANDLER_H
#define QSVERIFYSETTINGSGROUPHANDLER_H
#include <QObject>
#include "qspin/QObjectBase.h"
#include "qspin/models/QsVerificationConfiguration.h"
#include "qspin/viewModels/QsCodeEditorHandler.h"
class QsVerifySettingsGroupHandler: public QObjectBase{
    Q_OBJECT
    Q_PROPERTY(VerificationConfiguration* item READ item NOTIFY itemChanged)
    Q_PROPERTY(VerificationConfiguration* reference READ reference WRITE setReference NOTIFY referenceChanged)
    VerificationConfiguration *_default_item;
    QPointer<VerificationConfiguration> _item,_ref;
    Q_PROPERTY(QsCodeEditorHandler* ltlEditorHandler READ ltlEditorHandler WRITE setLtlEditorHandler NOTIFY ltlEditorHandlerChanged)
    QsCodeEditorHandler* _ltlEditorHandler;
    Q_PROPERTY(bool isEditable READ isEditable NOTIFY isEditableChanged)
    bool _isEditable;

public:
    VerificationConfiguration* item()const;
    VerificationConfiguration* reference()const;
    void setReference(VerificationConfiguration* value);
    QsCodeEditorHandler* ltlEditorHandler()const;
    void setLtlEditorHandler(QsCodeEditorHandler* value);
    bool isEditable()const;
    void setIsEditable(bool value);
    explicit QsVerifySettingsGroupHandler(QObject* parent = nullptr,EventAggregator* msg = nullptr);
private:
    void setItem(VerificationConfiguration* value);
signals:
    void referenceChanged();
    void ltlEditorHandlerChanged();
    void itemChanged();
    void isEditableChanged();
public slots:
    QString isValidLtlName(QString name);
};

#endif // QSVERIFYSETTINGSGROUPHANDLER_H
