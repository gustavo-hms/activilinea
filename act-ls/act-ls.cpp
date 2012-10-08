#include <KActivities/Consumer>
#include <KActivities/Info>
#include <QCoreApplication>
#include <QTextStream>
#include <QString>

QString prettyPrint(KUrl url)
{
	return url.pathOrUrl();
}

QString listFiles()
{
	KActivities::Consumer consumer;
	QString current = consumer.currentActivity();
	KActivities::Info info(current);
	KUrl::List list = info.linkedResources();
	QStringList output;
	foreach (KUrl url, list) {
		output << prettyPrint(url);
	}
	
	return output.join("\n");
}

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QTextStream out(stdout);
	out << listFiles() << endl;
	return 0;
}
