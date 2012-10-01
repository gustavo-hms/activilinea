#include <KActivities/Consumer>
#include <KActivities/Info>
#include <QCoreApplication>
#include <QString>
#include <QTextStream>

QString getActivityName()
{
	KActivities::Consumer consumer;
	KActivities::Info info(consumer.currentActivity());
	return info.name();
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QTextStream out(stdout);
	out << getActivityName() << endl;
	
	return 0;
}
