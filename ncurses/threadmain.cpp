#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

volatile bool start = 0;

void * thread_run(void *)
{
 while(1)
 {
 if(start)
 {
 cout << "Thread malloc" << endl;
 char *buf = new char[1024];
 start = 0;
 }
 sleep(1);
 }
}

int main()
{
 pthread_t th;

 getchar();
 getchar();
 pthread_create(&th, 0, thread_run, 0);

 while((getchar()))
 {
 start = 1;
 }
 return 0;
}
