#ifndef FTP_HTTP_H
#define FTP_HTTP_H

  struct http_request
  {
      char * method;
      char * element;
      double version;
      char * host;
  };

  struct http_response
  {
      double version;
      int status;
      char * status_message;
      char * date;
      char * server;
      char * last_modified;
      char * transfer_encoding;
      char * connection;
      char * content_type;
      char * charset;
      char * content;
      char * (*to_string)(struct * http_response);
  };

  struct * http_request parse_http_request (char *);

  struct * http_response parse_http_response (char *);

#endif
