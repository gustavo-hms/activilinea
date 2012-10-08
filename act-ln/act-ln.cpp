#include <KAboutData>
#include <KActivities/Consumer>
#include <KCmdLineArgs>
#include <KCmdLineOptions>
#include <QCoreApplication>
#include <QDir>
#include <QList>
#include <QString>
#include <QTextStream>
#include <QUrl>

QList<QUrl> parseFilesToLink(const KCmdLineArgs *args)
{
	QDir dir;
	QList<QUrl> filesToLink;
	
	for (int i = 0; i < args->count(); ++i) {
		QUrl file(dir.absoluteFilePath(args->arg(i)));
		filesToLink << file;
	}
	
	return filesToLink;
}

QString parseActivityId(const KCmdLineArgs *args)
{
	QString activityId = args->getOption("activity");
	if (activityId.isEmpty()) {
		KActivities::Consumer consumer;
		activityId = consumer.currentActivity();
	}
	
	return activityId;
}

bool parseRecurse(const KCmdLineArgs *args)
{
	return args->isSet("recursively");
}

bool parseExcludeDirs(const KCmdLineArgs *args)
{
	return args->isSet("exclude-dirs");
}

QList<QUrl> directoryContent(QUrl dirUri) {
	QDir dir(dirUri.path());
	QStringList contentNames = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);
	QList<QUrl> content;
	foreach (QString fileName, contentNames) {
		QUrl uri(dir.filePath(fileName));
		content << uri;
	}
	
	return content;
}

void linkFilesToActivity(QList<QUrl> files, QString activityId,
                         bool recursively, bool excludeDirs)
{
	KActivities::Consumer consumer;
	
	foreach (QUrl uri, files) {
		QFileInfo info(uri.path());
		if (info.isDir()) {
			if (recursively) {
				QList<QUrl> content = directoryContent(uri);
				linkFilesToActivity(content, activityId, recursively, excludeDirs);
			}
			
			if (excludeDirs) {
				continue;
			}
		}
		
		consumer.linkResourceToActivity(uri, activityId);
	}
}

int main(int argc, char *argv[])
{
	KAboutData about("act-ln", 0, ki18n("Act-Add"), "0.1",
	                 ki18n("Link files to an activity"), 
	                 KAboutData::License_GPL_V3,
	                 ki18n("(c) 2012, Gustavo H. Montesião de Sousa"));
	about.addAuthor(ki18n("Gustavo H. Montesião de Sousa"), ki18n("Developer"),
	                "gustavo@cecm.usp.br");
	
	KCmdLineArgs::init(argc, argv, &about);
	
	KCmdLineOptions options;
	options.add("+files", ki18n("The list of files to link to the activity"));
	options.add("r").add("recursively", ki18n("Link files recursing the directory tree"));
	options.add("a").add("activity <id>",
	                     ki18n("The id of the activity to link the files to. Default to the current activity"));
	options.add("exclude-dirs", ki18n("Do not link directories. If used with --recursively, link all directories contents recursively, without linking directories themselves though"));
	KCmdLineArgs::addCmdLineOptions(options);
		
	QCoreApplication app(argc, argv);
	
	KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
	
	QString activityId = parseActivityId(args);
	bool recursive = parseRecurse(args);
	bool excludeDirs = parseExcludeDirs(args);
	QList<QUrl> files = parseFilesToLink(args);
	linkFilesToActivity(files, activityId, recursive, excludeDirs);
}
