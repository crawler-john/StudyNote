#ifndef GSOAPSOLUTION_H
#define GSOAPSOLUTION_H

#include <QtWidgets/QWidget>
#include "ui_gsoapsolution.h"
#include "gSOAP/soapEchoProxy.h"

class gSOAPSolution : public QWidget
{
	Q_OBJECT

public:
	gSOAPSolution(QWidget *parent = 0);
	~gSOAPSolution();

private slots:
	void on_callEcho_clicked();
	void on_callLogin_clicked();

private:
	Ui::gSOAPSolutionClass ui;
	EchoProxy m_echo;
};

#endif // GSOAPSOLUTION_H
