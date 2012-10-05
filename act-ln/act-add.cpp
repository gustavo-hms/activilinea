#include <KAboutData>
#include <KActivities/Consumer>
#include <KCmdLineArgs>
#include <KCmdLineOptions>
#include <QCoreApplication>
#include <QDir>
#include <QString>
#include <QTextStream>
#include <QUrl>

bool recursively(const KCmdLineArgs *args)
{
	return args->isSet("recursively");
}

void linkFilesToActivity(const KCmdLineArgs *args)
{
	KActivities::Consumer consumer;
	QString activityId = args->getOption("activity");
	if (activityId.isEmpty()) {
		activityId = consumer.currentActivity();
	}
	
	QDir dir;
	for (int i = 0; i < args->count(); ++i) {
		QUrl file(dir.absoluteFilePath(args->arg(i)));
		consumer.linkResourceToActivity(file, activityId);
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
	KCmdLineArgs::addCmdLineOptions(options);
		
	QCoreApplication app(argc, argv);
	
	KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
	linkFilesToActivity(args);
}