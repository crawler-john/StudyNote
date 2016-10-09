#include "gsoapsolution.h"
#include <QtWidgets/QApplication>
#include "EchoServer.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	gSOAPSolution w;
	w.show();
	EchoServer _server;
	_server.start();
	return a.exec();
}
