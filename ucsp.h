#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>

#ifndef UCSP_   /* Include guard */
#define UCSP_

#define MAJOR_VERSION 0
#define MINOT_VERSION 1

#define PCAP_LOOP_CNT -1
#define PCAP_DONOTBLOCK 1
#define SNAPLEN 2312
#define PROMISC 1
#define TIMEOUT 500

#define BUFFER_SIZE 2048
#define SYSCALL_SIZE 1000
#define ERROR_HEADER_SIZE 29

#define UCSP_LOG_NAME "u.log"
#define MONITOR_LOG_NAME "t.log"
#define LOG_CNT_CAP 2000
#define MONITOR_SLEEP 120

#define _DEBUG

int 
is_log_full(void);

char*
get_ts(void);

void 
init_error_header(void);

void
init_event_log(void);

void 
init_log(char l_host[], char l_port[], char mac[], char log_path[], char l_file_names[], char ic_file_name[]);

void 
write_log(char *format, ...);

void
send_error(char*);

void
send_log(void);

void
print_packet(u_char *user, u_char *cp, u_int caplen, u_int length, u_int seconds, u_int useconds);

void 
print_bytes(u_int caplen, u_char *cp);

int
read_i();

int
read_c();

int 
arg_option(char *arg, char *option);

int 
Base64encode_len(int len);

int 
Base64encode(char * coded_dst, const char *plain_src,int len_plain_src);

int 
Base64decode_len(const char * coded_src);

int 
Base64decode(char * plain_dst, const char *coded_src);
//int
//is_target_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

void 
print_version(void);

int 
uc_main(int argc, char **argv);

int 
ul_main(int argc, char **argv);

int 
un_main(int argc, char **argv);

void
b64_main(int argc, char **argv);
#endif // UCSP_
