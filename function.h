#include<stdio.h>
#include<unistd.h>
#include<lib.h>
#define MAX_PUB 1
#define MAX_SUB 5
#define MAX_PID 6
#define MAX_GRP 8
#define BUF_SIZE 5
#define TRUE 1
#define FALSE 0
typedef struct IG 
{
	int IGid;
	int num_pub;
	int num_sub;
	char *ptr[BUF_SIZE];
	int buffer_size;
	int pub_pid[MAX_PUB];
	int sub_pid[2][MAX_SUB];
	int pida[MAX_PID];
	int num_pid;
	int flag;
	int sorp;
	int grpleadid;
	struct IG * next;
}IG;
typdef struct normal_user 
{
	int password;
	int uid;
	int gid[MAX_GRP];
	int perm[3];
}norm;
extern  IG * head = NULL;
extern message mbuf ;
extern int pass = 007;



