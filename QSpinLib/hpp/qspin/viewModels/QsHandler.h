#ifndef QSPIN_H
#define QSPIN_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QQmlEngine>
#include "qspin/QmlImportNames.h"
#include "qspin/models/QsProject.h"

class QsHandler : public QObject
{
		Q_OBJECT
		Q_PROPERTY(QsProject* project READ project NOTIFY projectChanged)
		QsProject* _project;
	public: // properties
		QsProject* project()const{ return _project; }
	signals:// properties
		void projectChanged();
	public:
        static void registerAsQml();
        explicit QsHandler(QObject *parent = nullptr);

		static bool saveProject(const QsProject& project){
			QFile saveFile( QStringLiteral("save.json"));

			if (!saveFile.open(QIODevice::WriteOnly)) {
				qWarning("Couldn't open save file.");
				return false;
			}

			QJsonObject projectObject;
			project.write(projectObject);
			QJsonDocument saveDoc(projectObject);
			saveFile.write(saveDoc.toJson());

			return true;
		}
		static bool loadProject(QsProject* project){

		}
	signals:

	public slots:
};

#endif // QSPIN_H
