#include <stdio.h>
#include <stdlib.h>
//#include "test3.h"
#include "szakdoga.h"
#include "iconv_him.h"
#include "hashtable.h"

void iconv_test()
{
    const char *source = "Ascii";
    const char *target = "UTF8";
    iconv_t cd = iconv_open(target,source);

    char *inbuf="the quick brown fox jumps over the lazy dog";
    size_t inbytesleft=strlen(inbuf)+1;
    char *outbuf=(char*) malloc(sizeof(char[44]));
    char *outbuf2 = outbuf;
    size_t outbytesleft=sizeof(char[44]);
    iconv(cd,&inbuf,&inbytesleft,&outbuf,&outbytesleft);

    printf("%s\n",outbuf2);
    iconv_close(cd);
}

void iconv_file_test()
{
    const char *source = "iso88592";
    const char *target = "ascii";
    iconv_t cd = iconv_open(target,source);

    if(cd!=-1)
    {
        FILE *file_in=fopen("from.txt","r");
        FILE *file_ou=fopen("to.txt","w");
        char *inbuf=(char*) malloc(sizeof(char[100]));
        char *inbuf2=inbuf;
        char *outbuf=(char*) malloc(sizeof(char[100]));
        char *outbuf2=outbuf;
        if(file_ou==NULL) printf("file error 2");
        else if(file_in==NULL)printf("file error");
        else while(fgets(inbuf,100,file_in)!=NULL)
            {
                size_t inbytesleft=strlen(inbuf)+1;
                size_t outbytesleft=sizeof(char[100]);
                outbuf=outbuf2;
                iconv(cd,&inbuf,&inbytesleft,&outbuf,&outbytesleft);
                fprintf(file_ou,"%s",outbuf2);
                inbuf=inbuf2;
            }
        fclose(file_in);
        fclose(file_ou);
    }

    iconv_close(cd);
}

int main()
{
    printf("Hello world!\n");

    ///iconv_test();

    iconv_file_test();

    return 0;
}
