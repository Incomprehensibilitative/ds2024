/*
 * rpc protocol spec for remote time worksheet
 * */

const MAXSTRLEN = 80; /* max string length */
typedef string datestr<MAXSTRLEN>; /* date string */

program REMTIMEPROG {
  version REMTIMEVERS {
    datestr GETDATESTR() = 1;
  } = 1;
} = 0x20650609;
