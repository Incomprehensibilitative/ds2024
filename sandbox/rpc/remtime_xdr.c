/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "remtime.h"

bool_t xdr_datestr(XDR *xdrs, datestr *objp) {
  register int32_t *buf;

  if (!xdr_string(xdrs, objp, MAXSTRLEN))
    return FALSE;
  return TRUE;
}
