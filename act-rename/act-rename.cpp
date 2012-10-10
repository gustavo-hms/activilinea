#include <KAboutData>
#include <KActivities/Consumer>
#include <KActivities/Controller>
#include <KCmdLineArgs>
#include <KCmdLineOptions>
#include <QCoreApplication>
#include <QString>

QString activityId(const KCmdLineArgs *args)
{
	if (args->count() < 2) {
		KActivities::Consumer consumer;
		return consumer.currentActivity();
	}
	
	return args->arg(0);
}

QString newName(const KCmdLineArgs *args)
{
	int argsNumber = args->count();
	if (argsNumber < 1 || argsNumber > 2) {
		return "";
	}
	
	return args->arg(argsNumber - 1);
}

void rename(const QString id, const QString newName)
{
	KActivities::Controller controller;
	controller.setActivityName(id, newName);
}

int main(int argc, char *argv[])
{
	KAboutData about("act-rename", 0, ki18n("Act-Rename"), "0.1",
	                 ki18n("Rename activities"), 
	                 KAboutData::License_GPL_V3,
	                 ki18n("(c) 2012, Gustavo H. Montesião de Sousa"));
	about.addAuthor(ki18n("Gustavo H. Montesião de Sousa"), ki18n("Developer"),
	                "gustavo@cecm.usp.br");
	
	KCmdLineArgs::init(argc, argv, &about);
	
	KCmdLineOptions options;
	options.add("+[id]", ki18n("The id of the activity to rename. Default to current activity"));
	options.add("+name", ki18n("The new name"));
	
	KCmdLineArgs::addCmdLineOptions(options);
		
	QCoreApplication app(argc, argv);
	
	KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
	QString id = activityId(args);
	QString name = newName(args);
	if (name.isEmpty()) {
		KCmdLineArgs::usageError(ki18n("Wrong number of arguments").toString());
	}
	
	rename(id, name);
}
