#include "gsoapsolution.h"

gSOAPSolution::gSOAPSolution(QWidget *parent)
	: QWidget(parent),m_echo("http://localhost:8080")
{
	ui.setupUi(this);
}

gSOAPSolution::~gSOAPSolution()
{

}

void gSOAPSolution::on_callEcho_clicked()
{
	std::string _return;
	int _rt = m_echo.echo(ui.echo->text().toStdString(),_return);
	if(_rt == SOAP_OK)
	{
		ui.textBrowser->append(QString::fromStdString(_return));
	}else
	{
		ui.textBrowser->append(QString::fromLocal8Bit(m_echo.soap_fault_string()));
		ui.textBrowser->append(QString::fromLocal8Bit(m_echo.soap_fault_detail()));
		m_echo.soap_stream_fault(std::cerr);
	}
}	

void gSOAPSolution::on_callLogin_clicked()
{
	std::string _return;
	int _rt = m_echo.login(ui.account->text().toStdString(),ui.password->text().toStdString(),std::string(),_return);
	if(_rt == SOAP_OK)
	{
		ui.textBrowser_2->append(QString::fromStdString(_return));
	}else
	{
		ui.textBrowser_2->append(QString::fromLocal8Bit(m_echo.soap_fault_string()));
		ui.textBrowser_2->append(QString::fromLocal8Bit(m_echo.soap_fault_detail()));
		m_echo.soap_stream_fault(std::cerr);
	}
}
