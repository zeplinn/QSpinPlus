#ifndef QSVERIFYRESULTHANDLER_H
#define QSVERIFYRESULTHANDLER_H

#include <QObject>
#include "qspin/models/QsVerificationResults.h"
#include <memory>
#include <QFileSystemWatcher>
#include <QPointer>
#include "qspin/QObjectBase.h"
#include "qspin/models/QSpinPlus.h"
#include "qspin/models/QsVerifyResultList.h"
#include "qspin/models/VerificationResultContainer.h"
#include "qspin/models/QsVerificationResults.h"
#include "qspin/viewModels/QsCodeEditorHandler.h"

//#include "qspin/viewModels/EventAggregator.h"
//#include "qspin/Qs.h"
// missing subscription object
class QsVerifyResultHandler
        : public QObjectBase
        , public ISubscriber<ProjectOpened>
        , public ISubscriber<ProjectSaved>
        , public ISubscriber<ProjectClosed>
        , public ISubscriber<VerificationResultFileChanged>
{
    Q_OBJECT

    Q_PROPERTY(VerificationResultContainer* currentItem READ currentItem NOTIFY currentItemChanged)
    VerificationResultContainer* _currentItem;
    Q_PROPERTY(VerificationResults* selectedResults READ selectedResults NOTIFY selectedResultsChanged)
    VerificationResults* _selectedResults;
    Q_PROPERTY(QsVerifyResultList* results READ results CONSTANT)
    QsVerifyResultList* _resultList;
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged)
    int _currentIndex=-1;
    Q_PROPERTY(QString spinCommands READ spinCommands NOTIFY currentItemChanged)
    Q_PROPERTY(QString gccCommands READ gccCommands NOTIFY currentItemChanged)
    Q_PROPERTY(QString panCommands READ panCommands NOTIFY currentItemChanged)
    Q_PROPERTY(QString unreached READ unreached NOTIFY currentItemChanged)





    // ############### result properties start ##################################


public:// result properies only
    QsVerifyResultList* results()const;

    VerificationResultContainer* currentItem()const;
    void setCurrentItem(VerificationResultContainer* value);

    VerificationResults* selectedResults()const;
    void setSelectedResults(VerificationResults* value);

    int currentIndex()const;
    void setCurrentIndex(int value);

    QString spinCommands()const;
    QString gccCommands()const;
    QString panCommands()const;

    QString unreached()const;
signals:
    void selectedResultsChanged();
    void currentItemChanged();
    void currentIndexChanged();
private:
    QPointer<QSpinPlus> _project;
    QFileSystemWatcher* _fileWatcher;
    QHash<qint64,bool> _watchedFiles;
protected:
public:
    explicit QsVerifyResultHandler(QObject* parent = nullptr, EventAggregator* msg=nullptr);

public: // ISubscriber interface
    void subscriber(const ProjectOpened& event)override;
    void subscriber(const ProjectSaved& event)override;
    void subscriber(const ProjectClosed& event)override;
    void subscriber(const VerificationResultFileChanged& event)override;
public slots:
    // note that removeal is controlled soly by file updated
    // which is called when file on disk changes
    void remove(int index);
    bool compareToCurrentDocument();
    QString getXmlReport();
private slots:

    void fileUpdated(QString path);
};

#endif // QSVERIFYRESULTHANDLER_H
