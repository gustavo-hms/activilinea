#include <KActivities/Consumer>
#include <KActivities/Info>
#include <QCoreApplication>
#include <QString>
#include <QStringList>
#include <QTextStream>

QString prettyPrint(QString activityId)
{
	KActivities::Info info(activityId);
	return info.name();
}

QString allActivities()
{
	KActivities::Consumer consumer;
	QStringList original = consumer.listActivities();
	QStringList output;
	foreach (QString activity, original) {
		output << prettyPrint(activity);
	}
	
	return output.join("\n");
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QTextStream out(stdout);
	out << allActivities() << endl;
	
	return 0;
}
