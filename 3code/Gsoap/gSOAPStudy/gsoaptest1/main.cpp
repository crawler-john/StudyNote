#include "soapcalcProxy.h"
#include "calc.nsmap"

using namespace std;

int main()
{
	calcProxy service;
	double result;
	if(service.add(1.0,2.0,result) == SOAP_OK)
	{
		cout << "The sum of 1.0 and 2.0 is " << result << endl;
	}else
	{
		service.soap_stream_fault(std::cerr);
	}
	service.destroy();
}
