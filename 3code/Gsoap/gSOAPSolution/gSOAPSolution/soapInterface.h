//gsoap ns service name: Echo
//gsoap ns service protocol:SOAP
//gsoap ns service style: rpc

#include <string>

int ns__echo(std::string str,std::string &resault);
int ns__login(std::string account,std::string password,std::string mode,std::string &resault);