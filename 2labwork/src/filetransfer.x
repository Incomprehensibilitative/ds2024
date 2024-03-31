/*
 * rpc protocol spec for remote file transfer
 * */

/* The maximum length of all data being transfer */
const MAXLEN = 1024;


/* Define a union for the send_file result */
union send_file_res switch (int errno) {
  case 0:
    void; /* success */
  default:
    string errmsg<MAXLEN>; /* error message */
};


/* Define a union for the retreive_file result */
union retreive_file_res switch (int errno) {
  case 0:
    string data<MAXLEN>; /* success, return file data */
  default:
    string errmsg<MAXLEN>; /* error message */
};

/* Define a struct for the send_file arguments */
struct send_file_args {
    string fname<MAXLEN>;
    string fdata<MAXLEN>;
};

program FILETRANSFER_PROG {
  version FILETRANSFER_VERS {
    retreive_file_res retreive_file(string filename<MAXLEN>) = 1;
    send_file_res send_file(send_file_args) = 2;
  } = 1;
} = 0x20000000;
