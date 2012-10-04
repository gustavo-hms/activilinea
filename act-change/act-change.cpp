#include <KActivities/Consumer>
#include <KActivities/Controller>
#include <QCoreApplication>
#include <QString>
#include <QTextStream>


QString findId()
{
	KActivities::Consumer consumer;
	QStringList list = consumer.listActivities();
	
	QString id;
	foreach (id, list) {
		if (id != consumer.currentActivity()) {
			break;
		}
	}
	
	return id;
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	QString current = findId();
	KActivities::Controller controller;
	controller.setCurrentActivity(current);
	
	return 0;
}
