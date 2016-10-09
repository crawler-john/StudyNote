#include "EchoServer.h"
#include "EchoService.hpp"
#include <fstream>


EchoServer::EchoServer(void)
{
}


EchoServer::~EchoServer(void)
{
}

void EchoServer::run()
{
	//新建服务的log记录，所有服务的错误信息都会记录
	std::ofstream _log("EchoService.log", std::ios::app);
	//创建EchoService服务
	EchoService echo;
	int _error = SOAP_OK;
	echo.bind_flags = SO_REUSEADDR;
	while(true)
	{
		//在8080端口开启服务
		_error = echo.run(8080);
		//如果服务出错，则在标准错误流中打印错误信息
		echo.soap_stream_fault(std::cerr);
		//如果服务出错，则在log记录中写入错误信息
		echo.soap_stream_fault(_log);
		_log.flush();
		//错误处理完毕，重新开始服务
	}
}