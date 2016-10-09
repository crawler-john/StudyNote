/* soapH.h
   Generated by gSOAP 2.8.36 for soapInterface.h

gSOAP XML Web services tools
Copyright (C) 2000-2016, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#ifndef soapH_H
#define soapH_H
#include "soapStub.h"
#ifndef WITH_NOIDREF

#ifdef __cplusplus
extern "C" {
#endif
SOAP_FMAC3 void SOAP_FMAC4 soap_markelement(struct soap*, const void*, int);

#ifdef __cplusplus
}
#endif
SOAP_FMAC3 int SOAP_FMAC4 soap_putindependent(struct soap*);
SOAP_FMAC3 int SOAP_FMAC4 soap_getindependent(struct soap*);
#endif

#ifdef __cplusplus
extern "C" {
#endif
SOAP_FMAC3 void *SOAP_FMAC4 soap_getelement(struct soap*, int*);
SOAP_FMAC3 int SOAP_FMAC4 soap_putelement(struct soap*, const void*, const char*, int, int);

#ifdef __cplusplus
}
#endif
SOAP_FMAC3 int SOAP_FMAC4 soap_ignore_element(struct soap*);

SOAP_FMAC3 const char ** SOAP_FMAC4 soap_faultcode(struct soap *soap);
SOAP_FMAC3 void * SOAP_FMAC4 soap_instantiate(struct soap*, int, const char*, const char*, size_t*);
SOAP_FMAC3 int SOAP_FMAC4 soap_fdelete(struct soap_clist*);
SOAP_FMAC3 int SOAP_FMAC4 soap_fbase(int, int);
SOAP_FMAC3 void SOAP_FMAC4 soap_finsert(struct soap*, int, int, void*, size_t, const void*, void**);

#ifndef SOAP_TYPE_byte_DEFINED
#define SOAP_TYPE_byte_DEFINED

inline void soap_default_byte(struct soap *soap, char *a)
{
	(void)soap; /* appease -Wall -Werror */
#ifdef SOAP_DEFAULT_byte
	*a = SOAP_DEFAULT_byte;
#else
	*a = (char)0;
#endif
}
SOAP_FMAC3 int SOAP_FMAC4 soap_out_byte(struct soap*, const char*, int, const char *, const char*);
SOAP_FMAC3 char * SOAP_FMAC4 soap_in_byte(struct soap*, const char*, char *, const char*);

SOAP_FMAC3 char * SOAP_FMAC4 soap_new_byte(struct soap *soap, int n = -1);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_byte(struct soap*, const char *, const char*, const char*);

inline int soap_write_byte(struct soap *soap, char const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || soap_put_byte(soap, p, "byte", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 char * SOAP_FMAC4 soap_get_byte(struct soap*, char *, const char*, const char*);

inline int soap_read_byte(struct soap *soap, char *p)
{
	if (p)
	{	if (soap_begin_recv(soap) || soap_get_byte(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef SOAP_TYPE_int_DEFINED
#define SOAP_TYPE_int_DEFINED

inline void soap_default_int(struct soap *soap, int *a)
{
	(void)soap; /* appease -Wall -Werror */
#ifdef SOAP_DEFAULT_int
	*a = SOAP_DEFAULT_int;
#else
	*a = (int)0;
#endif
}
SOAP_FMAC3 int SOAP_FMAC4 soap_out_int(struct soap*, const char*, int, const int *, const char*);
SOAP_FMAC3 int * SOAP_FMAC4 soap_in_int(struct soap*, const char*, int *, const char*);

SOAP_FMAC3 int * SOAP_FMAC4 soap_new_int(struct soap *soap, int n = -1);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_int(struct soap*, const int *, const char*, const char*);

inline int soap_write_int(struct soap *soap, int const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || soap_put_int(soap, p, "int", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 int * SOAP_FMAC4 soap_get_int(struct soap*, int *, const char*, const char*);

inline int soap_read_int(struct soap *soap, int *p)
{
	if (p)
	{	if (soap_begin_recv(soap) || soap_get_int(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef SOAP_TYPE_std__string_DEFINED
#define SOAP_TYPE_std__string_DEFINED

inline void soap_default_std__string(struct soap *soap, std::string *p)
{
	(void)soap; /* appease -Wall -Werror */
	p->erase();
}
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_std__string(struct soap*, const std::string *);

#define soap_std__string2s(soap, a) ((a).c_str())
SOAP_FMAC3 int SOAP_FMAC4 soap_out_std__string(struct soap*, const char*, int, const std::string*, const char*);

#define soap_s2std__string(soap, s, a) soap_s2stdchar((soap), (s), (a), 0, -1, NULL)
SOAP_FMAC3 std::string * SOAP_FMAC4 soap_in_std__string(struct soap*, const char*, std::string*, const char*);
SOAP_FMAC1 std::string * SOAP_FMAC2 soap_instantiate_std__string(struct soap*, int, const char*, const char*, size_t*);

inline std::string * soap_new_std__string(struct soap *soap, int n = -1)
{
	return soap_instantiate_std__string(soap, n, NULL, NULL, NULL);
}

inline std::string * soap_new_req_std__string(
	struct soap *soap)
{
	std::string *_p = soap_new_std__string(soap);
	if (_p)
	{	soap_default_std__string(soap, _p);
	}
	return _p;
}

inline std::string * soap_new_set_std__string(
	struct soap *soap)
{
	std::string *_p = soap_new_std__string(soap);
	if (_p)
	{	soap_default_std__string(soap, _p);
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_std__string(struct soap*, const std::string *, const char*, const char*);

inline int soap_write_std__string(struct soap *soap, std::string const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || soap_put_std__string(soap, p, "string", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 std::string * SOAP_FMAC4 soap_get_std__string(struct soap*, std::string *, const char*, const char*);

inline int soap_read_std__string(struct soap *soap, std::string *p)
{
	if (p)
	{	if (soap_begin_recv(soap) || soap_get_std__string(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Fault_DEFINED
#define SOAP_TYPE_SOAP_ENV__Fault_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Fault(struct soap*, const char*, int, const struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_in_SOAP_ENV__Fault(struct soap*, const char*, struct SOAP_ENV__Fault *, const char*);
SOAP_FMAC1 struct SOAP_ENV__Fault * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);

inline struct SOAP_ENV__Fault * soap_new_SOAP_ENV__Fault(struct soap *soap, int n = -1)
{
	return soap_instantiate_SOAP_ENV__Fault(soap, n, NULL, NULL, NULL);
}

inline struct SOAP_ENV__Fault * soap_new_req_SOAP_ENV__Fault(
	struct soap *soap)
{
	struct SOAP_ENV__Fault *_p = soap_new_SOAP_ENV__Fault(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Fault(soap, _p);
	}
	return _p;
}

inline struct SOAP_ENV__Fault * soap_new_set_SOAP_ENV__Fault(
	struct soap *soap,
	char *faultcode,
	char *faultstring,
	char *faultactor,
	struct SOAP_ENV__Detail *detail,
	struct SOAP_ENV__Code *SOAP_ENV__Code,
	struct SOAP_ENV__Reason *SOAP_ENV__Reason,
	char *SOAP_ENV__Node,
	char *SOAP_ENV__Role,
	struct SOAP_ENV__Detail *SOAP_ENV__Detail)
{
	struct SOAP_ENV__Fault *_p = soap_new_SOAP_ENV__Fault(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Fault(soap, _p);
		_p->faultcode = faultcode;
		_p->faultstring = faultstring;
		_p->faultactor = faultactor;
		_p->detail = detail;
		_p->SOAP_ENV__Code = SOAP_ENV__Code;
		_p->SOAP_ENV__Reason = SOAP_ENV__Reason;
		_p->SOAP_ENV__Node = SOAP_ENV__Node;
		_p->SOAP_ENV__Role = SOAP_ENV__Role;
		_p->SOAP_ENV__Detail = SOAP_ENV__Detail;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Fault(struct soap*, const struct SOAP_ENV__Fault *, const char*, const char*);

inline int soap_write_SOAP_ENV__Fault(struct soap *soap, struct SOAP_ENV__Fault const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Fault(soap, p), 0) || soap_put_SOAP_ENV__Fault(soap, p, "SOAP-ENV:Fault", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct SOAP_ENV__Fault * SOAP_FMAC4 soap_get_SOAP_ENV__Fault(struct soap*, struct SOAP_ENV__Fault *, const char*, const char*);

inline int soap_read_SOAP_ENV__Fault(struct soap *soap, struct SOAP_ENV__Fault *p)
{
	if (p)
	{	soap_default_SOAP_ENV__Fault(soap, p);
		if (soap_begin_recv(soap) || soap_get_SOAP_ENV__Fault(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Reason_DEFINED
#define SOAP_TYPE_SOAP_ENV__Reason_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Reason(struct soap*, const char*, int, const struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_in_SOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason *, const char*);
SOAP_FMAC1 struct SOAP_ENV__Reason * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);

inline struct SOAP_ENV__Reason * soap_new_SOAP_ENV__Reason(struct soap *soap, int n = -1)
{
	return soap_instantiate_SOAP_ENV__Reason(soap, n, NULL, NULL, NULL);
}

inline struct SOAP_ENV__Reason * soap_new_req_SOAP_ENV__Reason(
	struct soap *soap)
{
	struct SOAP_ENV__Reason *_p = soap_new_SOAP_ENV__Reason(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Reason(soap, _p);
	}
	return _p;
}

inline struct SOAP_ENV__Reason * soap_new_set_SOAP_ENV__Reason(
	struct soap *soap,
	char *SOAP_ENV__Text)
{
	struct SOAP_ENV__Reason *_p = soap_new_SOAP_ENV__Reason(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Reason(soap, _p);
		_p->SOAP_ENV__Text = SOAP_ENV__Text;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Reason(struct soap*, const struct SOAP_ENV__Reason *, const char*, const char*);

inline int soap_write_SOAP_ENV__Reason(struct soap *soap, struct SOAP_ENV__Reason const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Reason(soap, p), 0) || soap_put_SOAP_ENV__Reason(soap, p, "SOAP-ENV:Reason", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct SOAP_ENV__Reason * SOAP_FMAC4 soap_get_SOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *, const char*, const char*);

inline int soap_read_SOAP_ENV__Reason(struct soap *soap, struct SOAP_ENV__Reason *p)
{
	if (p)
	{	soap_default_SOAP_ENV__Reason(soap, p);
		if (soap_begin_recv(soap) || soap_get_SOAP_ENV__Reason(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Detail_DEFINED
#define SOAP_TYPE_SOAP_ENV__Detail_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Detail(struct soap*, const char*, int, const struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_in_SOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail *, const char*);
SOAP_FMAC1 struct SOAP_ENV__Detail * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);

inline struct SOAP_ENV__Detail * soap_new_SOAP_ENV__Detail(struct soap *soap, int n = -1)
{
	return soap_instantiate_SOAP_ENV__Detail(soap, n, NULL, NULL, NULL);
}

inline struct SOAP_ENV__Detail * soap_new_req_SOAP_ENV__Detail(
	struct soap *soap,
	int __type,
	void *fault)
{
	struct SOAP_ENV__Detail *_p = soap_new_SOAP_ENV__Detail(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Detail(soap, _p);
		_p->__type = __type;
		_p->fault = fault;
	}
	return _p;
}

inline struct SOAP_ENV__Detail * soap_new_set_SOAP_ENV__Detail(
	struct soap *soap,
	char *__any,
	int __type,
	void *fault)
{
	struct SOAP_ENV__Detail *_p = soap_new_SOAP_ENV__Detail(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Detail(soap, _p);
		_p->__any = __any;
		_p->__type = __type;
		_p->fault = fault;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Detail(struct soap*, const struct SOAP_ENV__Detail *, const char*, const char*);

inline int soap_write_SOAP_ENV__Detail(struct soap *soap, struct SOAP_ENV__Detail const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Detail(soap, p), 0) || soap_put_SOAP_ENV__Detail(soap, p, "SOAP-ENV:Detail", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct SOAP_ENV__Detail * SOAP_FMAC4 soap_get_SOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *, const char*, const char*);

inline int soap_read_SOAP_ENV__Detail(struct soap *soap, struct SOAP_ENV__Detail *p)
{
	if (p)
	{	soap_default_SOAP_ENV__Detail(soap, p);
		if (soap_begin_recv(soap) || soap_get_SOAP_ENV__Detail(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Code_DEFINED
#define SOAP_TYPE_SOAP_ENV__Code_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Code(struct soap*, const char*, int, const struct SOAP_ENV__Code *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_in_SOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code *, const char*);
SOAP_FMAC1 struct SOAP_ENV__Code * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);

inline struct SOAP_ENV__Code * soap_new_SOAP_ENV__Code(struct soap *soap, int n = -1)
{
	return soap_instantiate_SOAP_ENV__Code(soap, n, NULL, NULL, NULL);
}

inline struct SOAP_ENV__Code * soap_new_req_SOAP_ENV__Code(
	struct soap *soap)
{
	struct SOAP_ENV__Code *_p = soap_new_SOAP_ENV__Code(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Code(soap, _p);
	}
	return _p;
}

inline struct SOAP_ENV__Code * soap_new_set_SOAP_ENV__Code(
	struct soap *soap,
	char *SOAP_ENV__Value,
	struct SOAP_ENV__Code *SOAP_ENV__Subcode)
{
	struct SOAP_ENV__Code *_p = soap_new_SOAP_ENV__Code(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Code(soap, _p);
		_p->SOAP_ENV__Value = SOAP_ENV__Value;
		_p->SOAP_ENV__Subcode = SOAP_ENV__Subcode;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Code(struct soap*, const struct SOAP_ENV__Code *, const char*, const char*);

inline int soap_write_SOAP_ENV__Code(struct soap *soap, struct SOAP_ENV__Code const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Code(soap, p), 0) || soap_put_SOAP_ENV__Code(soap, p, "SOAP-ENV:Code", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct SOAP_ENV__Code * SOAP_FMAC4 soap_get_SOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *, const char*, const char*);

inline int soap_read_SOAP_ENV__Code(struct soap *soap, struct SOAP_ENV__Code *p)
{
	if (p)
	{	soap_default_SOAP_ENV__Code(soap, p);
		if (soap_begin_recv(soap) || soap_get_SOAP_ENV__Code(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_SOAP_ENV__Header_DEFINED
#define SOAP_TYPE_SOAP_ENV__Header_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_SOAP_ENV__Header(struct soap*, const char*, int, const struct SOAP_ENV__Header *, const char*);
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_in_SOAP_ENV__Header(struct soap*, const char*, struct SOAP_ENV__Header *, const char*);
SOAP_FMAC1 struct SOAP_ENV__Header * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);

inline struct SOAP_ENV__Header * soap_new_SOAP_ENV__Header(struct soap *soap, int n = -1)
{
	return soap_instantiate_SOAP_ENV__Header(soap, n, NULL, NULL, NULL);
}

inline struct SOAP_ENV__Header * soap_new_req_SOAP_ENV__Header(
	struct soap *soap)
{
	struct SOAP_ENV__Header *_p = soap_new_SOAP_ENV__Header(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Header(soap, _p);
	}
	return _p;
}

inline struct SOAP_ENV__Header * soap_new_set_SOAP_ENV__Header(
	struct soap *soap)
{
	struct SOAP_ENV__Header *_p = soap_new_SOAP_ENV__Header(soap);
	if (_p)
	{	soap_default_SOAP_ENV__Header(soap, _p);
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_SOAP_ENV__Header(struct soap*, const struct SOAP_ENV__Header *, const char*, const char*);

inline int soap_write_SOAP_ENV__Header(struct soap *soap, struct SOAP_ENV__Header const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_SOAP_ENV__Header(soap, p), 0) || soap_put_SOAP_ENV__Header(soap, p, "SOAP-ENV:Header", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct SOAP_ENV__Header * SOAP_FMAC4 soap_get_SOAP_ENV__Header(struct soap*, struct SOAP_ENV__Header *, const char*, const char*);

inline int soap_read_SOAP_ENV__Header(struct soap *soap, struct SOAP_ENV__Header *p)
{
	if (p)
	{	soap_default_SOAP_ENV__Header(soap, p);
		if (soap_begin_recv(soap) || soap_get_SOAP_ENV__Header(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#endif

#ifndef SOAP_TYPE_ns__login_DEFINED
#define SOAP_TYPE_ns__login_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__login(struct soap*, struct ns__login *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__login(struct soap*, const struct ns__login *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__login(struct soap*, const char*, int, const struct ns__login *, const char*);
SOAP_FMAC3 struct ns__login * SOAP_FMAC4 soap_in_ns__login(struct soap*, const char*, struct ns__login *, const char*);
SOAP_FMAC1 struct ns__login * SOAP_FMAC2 soap_instantiate_ns__login(struct soap*, int, const char*, const char*, size_t*);

inline struct ns__login * soap_new_ns__login(struct soap *soap, int n = -1)
{
	return soap_instantiate_ns__login(soap, n, NULL, NULL, NULL);
}

inline struct ns__login * soap_new_req_ns__login(
	struct soap *soap,
	const std::string& account,
	const std::string& password,
	const std::string& mode)
{
	struct ns__login *_p = soap_new_ns__login(soap);
	if (_p)
	{	soap_default_ns__login(soap, _p);
		_p->account = account;
		_p->password = password;
		_p->mode = mode;
	}
	return _p;
}

inline struct ns__login * soap_new_set_ns__login(
	struct soap *soap,
	const std::string& account,
	const std::string& password,
	const std::string& mode)
{
	struct ns__login *_p = soap_new_ns__login(soap);
	if (_p)
	{	soap_default_ns__login(soap, _p);
		_p->account = account;
		_p->password = password;
		_p->mode = mode;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__login(struct soap*, const struct ns__login *, const char*, const char*);

inline int soap_write_ns__login(struct soap *soap, struct ns__login const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_ns__login(soap, p), 0) || soap_put_ns__login(soap, p, "ns:login", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct ns__login * SOAP_FMAC4 soap_get_ns__login(struct soap*, struct ns__login *, const char*, const char*);

inline int soap_read_ns__login(struct soap *soap, struct ns__login *p)
{
	if (p)
	{	soap_default_ns__login(soap, p);
		if (soap_begin_recv(soap) || soap_get_ns__login(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef SOAP_TYPE_ns__loginResponse_DEFINED
#define SOAP_TYPE_ns__loginResponse_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__loginResponse(struct soap*, struct ns__loginResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__loginResponse(struct soap*, const struct ns__loginResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__loginResponse(struct soap*, const char*, int, const struct ns__loginResponse *, const char*);
SOAP_FMAC3 struct ns__loginResponse * SOAP_FMAC4 soap_in_ns__loginResponse(struct soap*, const char*, struct ns__loginResponse *, const char*);
SOAP_FMAC1 struct ns__loginResponse * SOAP_FMAC2 soap_instantiate_ns__loginResponse(struct soap*, int, const char*, const char*, size_t*);

inline struct ns__loginResponse * soap_new_ns__loginResponse(struct soap *soap, int n = -1)
{
	return soap_instantiate_ns__loginResponse(soap, n, NULL, NULL, NULL);
}

inline struct ns__loginResponse * soap_new_req_ns__loginResponse(
	struct soap *soap,
	const std::string& resault)
{
	struct ns__loginResponse *_p = soap_new_ns__loginResponse(soap);
	if (_p)
	{	soap_default_ns__loginResponse(soap, _p);
		_p->resault = resault;
	}
	return _p;
}

inline struct ns__loginResponse * soap_new_set_ns__loginResponse(
	struct soap *soap,
	const std::string& resault)
{
	struct ns__loginResponse *_p = soap_new_ns__loginResponse(soap);
	if (_p)
	{	soap_default_ns__loginResponse(soap, _p);
		_p->resault = resault;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__loginResponse(struct soap*, const struct ns__loginResponse *, const char*, const char*);

inline int soap_write_ns__loginResponse(struct soap *soap, struct ns__loginResponse const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_ns__loginResponse(soap, p), 0) || soap_put_ns__loginResponse(soap, p, "ns:loginResponse", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct ns__loginResponse * SOAP_FMAC4 soap_get_ns__loginResponse(struct soap*, struct ns__loginResponse *, const char*, const char*);

inline int soap_read_ns__loginResponse(struct soap *soap, struct ns__loginResponse *p)
{
	if (p)
	{	soap_default_ns__loginResponse(soap, p);
		if (soap_begin_recv(soap) || soap_get_ns__loginResponse(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef SOAP_TYPE_ns__echo_DEFINED
#define SOAP_TYPE_ns__echo_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__echo(struct soap*, struct ns__echo *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__echo(struct soap*, const struct ns__echo *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__echo(struct soap*, const char*, int, const struct ns__echo *, const char*);
SOAP_FMAC3 struct ns__echo * SOAP_FMAC4 soap_in_ns__echo(struct soap*, const char*, struct ns__echo *, const char*);
SOAP_FMAC1 struct ns__echo * SOAP_FMAC2 soap_instantiate_ns__echo(struct soap*, int, const char*, const char*, size_t*);

inline struct ns__echo * soap_new_ns__echo(struct soap *soap, int n = -1)
{
	return soap_instantiate_ns__echo(soap, n, NULL, NULL, NULL);
}

inline struct ns__echo * soap_new_req_ns__echo(
	struct soap *soap,
	const std::string& str)
{
	struct ns__echo *_p = soap_new_ns__echo(soap);
	if (_p)
	{	soap_default_ns__echo(soap, _p);
		_p->str = str;
	}
	return _p;
}

inline struct ns__echo * soap_new_set_ns__echo(
	struct soap *soap,
	const std::string& str)
{
	struct ns__echo *_p = soap_new_ns__echo(soap);
	if (_p)
	{	soap_default_ns__echo(soap, _p);
		_p->str = str;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__echo(struct soap*, const struct ns__echo *, const char*, const char*);

inline int soap_write_ns__echo(struct soap *soap, struct ns__echo const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_ns__echo(soap, p), 0) || soap_put_ns__echo(soap, p, "ns:echo", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct ns__echo * SOAP_FMAC4 soap_get_ns__echo(struct soap*, struct ns__echo *, const char*, const char*);

inline int soap_read_ns__echo(struct soap *soap, struct ns__echo *p)
{
	if (p)
	{	soap_default_ns__echo(soap, p);
		if (soap_begin_recv(soap) || soap_get_ns__echo(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef SOAP_TYPE_ns__echoResponse_DEFINED
#define SOAP_TYPE_ns__echoResponse_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_default_ns__echoResponse(struct soap*, struct ns__echoResponse *);
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_ns__echoResponse(struct soap*, const struct ns__echoResponse *);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_ns__echoResponse(struct soap*, const char*, int, const struct ns__echoResponse *, const char*);
SOAP_FMAC3 struct ns__echoResponse * SOAP_FMAC4 soap_in_ns__echoResponse(struct soap*, const char*, struct ns__echoResponse *, const char*);
SOAP_FMAC1 struct ns__echoResponse * SOAP_FMAC2 soap_instantiate_ns__echoResponse(struct soap*, int, const char*, const char*, size_t*);

inline struct ns__echoResponse * soap_new_ns__echoResponse(struct soap *soap, int n = -1)
{
	return soap_instantiate_ns__echoResponse(soap, n, NULL, NULL, NULL);
}

inline struct ns__echoResponse * soap_new_req_ns__echoResponse(
	struct soap *soap,
	const std::string& resault)
{
	struct ns__echoResponse *_p = soap_new_ns__echoResponse(soap);
	if (_p)
	{	soap_default_ns__echoResponse(soap, _p);
		_p->resault = resault;
	}
	return _p;
}

inline struct ns__echoResponse * soap_new_set_ns__echoResponse(
	struct soap *soap,
	const std::string& resault)
{
	struct ns__echoResponse *_p = soap_new_ns__echoResponse(soap);
	if (_p)
	{	soap_default_ns__echoResponse(soap, _p);
		_p->resault = resault;
	}
	return _p;
}
SOAP_FMAC3 int SOAP_FMAC4 soap_put_ns__echoResponse(struct soap*, const struct ns__echoResponse *, const char*, const char*);

inline int soap_write_ns__echoResponse(struct soap *soap, struct ns__echoResponse const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || (soap_serialize_ns__echoResponse(soap, p), 0) || soap_put_ns__echoResponse(soap, p, "ns:echoResponse", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 struct ns__echoResponse * SOAP_FMAC4 soap_get_ns__echoResponse(struct soap*, struct ns__echoResponse *, const char*, const char*);

inline int soap_read_ns__echoResponse(struct soap *soap, struct ns__echoResponse *p)
{
	if (p)
	{	soap_default_ns__echoResponse(soap, p);
		if (soap_begin_recv(soap) || soap_get_ns__echoResponse(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason_DEFINED
#define SOAP_TYPE_PointerToSOAP_ENV__Reason_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Reason(struct soap*, const char *, int, struct SOAP_ENV__Reason *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Reason(struct soap*, const char*, struct SOAP_ENV__Reason **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason *const*, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Reason ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Reason(struct soap*, struct SOAP_ENV__Reason **, const char*, const char*);
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail_DEFINED
#define SOAP_TYPE_PointerToSOAP_ENV__Detail_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Detail(struct soap*, const char *, int, struct SOAP_ENV__Detail *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Detail(struct soap*, const char*, struct SOAP_ENV__Detail **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail *const*, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Detail ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Detail(struct soap*, struct SOAP_ENV__Detail **, const char*, const char*);
#endif

#endif

#ifndef WITH_NOGLOBAL

#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code_DEFINED
#define SOAP_TYPE_PointerToSOAP_ENV__Code_DEFINED
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*);
SOAP_FMAC3 int SOAP_FMAC4 soap_out_PointerToSOAP_ENV__Code(struct soap*, const char *, int, struct SOAP_ENV__Code *const*, const char *);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_in_PointerToSOAP_ENV__Code(struct soap*, const char*, struct SOAP_ENV__Code **, const char*);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code *const*, const char*, const char*);
SOAP_FMAC3 struct SOAP_ENV__Code ** SOAP_FMAC4 soap_get_PointerToSOAP_ENV__Code(struct soap*, struct SOAP_ENV__Code **, const char*, const char*);
#endif

#endif

#ifndef SOAP_TYPE__XML_DEFINED
#define SOAP_TYPE__XML_DEFINED
#endif

#ifndef SOAP_TYPE__QName_DEFINED
#define SOAP_TYPE__QName_DEFINED

inline void soap_default__QName(struct soap *soap, char **a)
{
	(void)soap; /* appease -Wall -Werror */
#ifdef SOAP_DEFAULT__QName
	*a = SOAP_DEFAULT__QName;
#else
	*a = (char *)0;
#endif
}
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize__QName(struct soap*, char *const*);

#define soap__QName2s(soap, a) soap_QName2s(soap, (a))
SOAP_FMAC3 int SOAP_FMAC4 soap_out__QName(struct soap*, const char*, int, char*const*, const char*);

#define soap_s2_QName(soap, s, a) soap_s2QName((soap), (s), (char**)(a), 0, -1, NULL)
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in__QName(struct soap*, const char*, char **, const char*);

SOAP_FMAC3 char * * SOAP_FMAC4 soap_new__QName(struct soap *soap, int n = -1);
SOAP_FMAC3 int SOAP_FMAC4 soap_put__QName(struct soap*, char *const*, const char*, const char*);

inline int soap_write__QName(struct soap *soap, char *const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || soap_put__QName(soap, p, "QName", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 char ** SOAP_FMAC4 soap_get__QName(struct soap*, char **, const char*, const char*);

inline int soap_read__QName(struct soap *soap, char **p)
{
	if (p)
	{	if (soap_begin_recv(soap) || soap_get__QName(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#ifndef SOAP_TYPE_string_DEFINED
#define SOAP_TYPE_string_DEFINED

inline void soap_default_string(struct soap *soap, char **a)
{
	(void)soap; /* appease -Wall -Werror */
#ifdef SOAP_DEFAULT_string
	*a = SOAP_DEFAULT_string;
#else
	*a = (char *)0;
#endif
}
SOAP_FMAC3 void SOAP_FMAC4 soap_serialize_string(struct soap*, char *const*);

#define soap_string2s(soap, a) (a)
SOAP_FMAC3 int SOAP_FMAC4 soap_out_string(struct soap*, const char*, int, char*const*, const char*);

#define soap_s2string(soap, s, a) soap_s2char((soap), (s), (char**)(a), 0, -1, NULL)
SOAP_FMAC3 char * * SOAP_FMAC4 soap_in_string(struct soap*, const char*, char **, const char*);

SOAP_FMAC3 char * * SOAP_FMAC4 soap_new_string(struct soap *soap, int n = -1);
SOAP_FMAC3 int SOAP_FMAC4 soap_put_string(struct soap*, char *const*, const char*, const char*);

inline int soap_write_string(struct soap *soap, char *const*p)
{
	soap_free_temp(soap);
	if (p)
	{	if (soap_begin_send(soap) || soap_put_string(soap, p, "string", "") || soap_end_send(soap))
			return soap->error;
	}
	return SOAP_OK;
}
SOAP_FMAC3 char ** SOAP_FMAC4 soap_get_string(struct soap*, char **, const char*, const char*);

inline int soap_read_string(struct soap *soap, char **p)
{
	if (p)
	{	if (soap_begin_recv(soap) || soap_get_string(soap, p, NULL, NULL) == NULL || soap_end_recv(soap))
			return soap->error;
	}
	return SOAP_OK;
}
#endif

#endif

/* End of soapH.h */
