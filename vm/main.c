/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <turiyafy (AT) gmail(DOT)com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return -- Kaustubh Pratap Chand
 * ----------------------------------------------------------------------------
 */
 
 
#include "globals.h"

char *buff;
int buf_size;


int fSize(FILE *fp)
{
    long int size;
    fseek(fp,0,SEEK_END);
    size=ftell(fp);
    rewind(fp);
    return size;
}

int load_file(char *file)
{
    FILE *fp;
    fp=fopen(file,"r");
    if(!fp){
        fputs("vm: Error in opening file!\n",stderr);
        return -1;
        }

    long int size=fSize(fp);
    buff=(char*)malloc(size);
    if(!buff){
        fputs("vm: Unable to initialize mem\n",stderr);
        return -1;
    }

    long int rs=fread(buff,1,size,fp);
    fclose(fp);
    return rs;

}

int main(int argc,char *argv[])
{
    if(argc!=2){
        fputs("vm: <file>\n",stderr);
        return 1;
    }


    buf_size=load_file(argv[1]);
    bf_run(buff,buf_size);
    return 0;
}
