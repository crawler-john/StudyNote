#pragma once
#include <QThread>
class EchoServer :
	public QThread
{
public:
	EchoServer(void);
	~EchoServer(void);
private:
	void run();
};

