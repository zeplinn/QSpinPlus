#ifndef QSPROMELAHANDLER_H
#define QSPROMELAHANDLER_H
#include <QObject>
#include <QUrl>
#include <QFileInfo>
#include <QDir>
#include "qspin/QObjectBase.h"
#include "qspin/models/QSpinPlus.h"
#include "qspin/viewModels/QsCodeEditorHandler.h"
#include <QDateTime>
#include <functional>
class QsPromelaHandler : public QObjectBase{
    Q_OBJECT
    // --> ############ begin properties ############################
    Q_PROPERTY(QsCodeEditorHandler* editor READ editor WRITE setEditor NOTIFY editorChanged)
    QsCodeEditorHandler* _editor;
    Q_PROPERTY(bool isEditable READ isEditable NOTIFY isEditableChanged)
    bool _isEditable=false;
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    bool _isOpen =false;

public:
    QsCodeEditorHandler* editor()const;
    void setEditor(QsCodeEditorHandler* value);
    bool isEditable()const;
    void setIsEditable(bool value);
    bool isOpen()const;
    void setIsOpen(bool value);
signals:
    void editorChanged();
    void isEditableChanged();
    void isOpenChanged();
    // <--- ############ end properties ############################

private:
    QSpinPlus* _project=nullptr;
public:
    using QObjectBase::QObjectBase;

signals:
    void projectSaved(QUrl url);
    void validatedocumentFailed();
public slots:
    void saveDocument(QUrl fileUrl);
    void openDocument(QUrl fileUrl);

    void createDocument(QString name,QUrl folder);
    void closeDocument(QUrl fileUrl =QUrl());


};

#endif // QSPROMELAHANDLER_H
