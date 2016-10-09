#include <QtCore/QUuid>

#include "gSOAP/soapEchoService.h"
#include "gSOAP/Echo.nsmap"

int EchoService::echo(std::string str, std::string &resault)
{
	resault = str;
	if(resault == "error")
	{
		QString _str = QString::fromLocal8Bit("你输入了一个错误");
		return soap_receiverfault("You put a error",_str.toUtf8().constData());
	}else
	{
		return SOAP_OK;
	}
}

int EchoService::login(std::string account,std::string password,std::string mode,std::string &resault)
{
	if(account == "admin" && password == "admin")
	{
		resault = QUuid::createUuid().toString().toStdString();
		return SOAP_OK;
	}
	else
	{
		QString _str = QString::fromLocal8Bit("用户名和密码都是admin，请重试。");
		return soap_receiverfault("Login error",_str.toUtf8().constData());
	}
}