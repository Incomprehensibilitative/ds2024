/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _REMTIME_H_RPCGEN
#define _REMTIME_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAXSTRLEN 80

typedef char *datestr;

#define REMTIMEPROG 0x20650609
#define REMTIMEVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define GETDATESTR 1
extern  datestr * getdatestr_1(void *, CLIENT *);
extern  datestr * getdatestr_1_svc(void *, struct svc_req *);
extern int remtimeprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define GETDATESTR 1
extern  datestr * getdatestr_1();
extern  datestr * getdatestr_1_svc();
extern int remtimeprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_datestr (XDR *, datestr*);

#else /* K&R C */
extern bool_t xdr_datestr ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_REMTIME_H_RPCGEN */
