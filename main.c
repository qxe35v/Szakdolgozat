#include <stdio.h>
#include <stdlib.h>
//#include "test3.h"
#include "szakdoga.h"
#include "iconv_him.h"
#include "hashtable.h"

void feltolt(hashtable* aliases) {
    const char* encoding_ascii = "ascii";
    hashtable_put(aliases,&encoding_ascii,&encoding_ascii);
    const char* alias_Ascii_for_ascii = "Ascii";
    hashtable_put(aliases,&alias_Ascii_for_ascii,&encoding_ascii);
    const char* encoding_a = "a";
    hashtable_put(aliases,&encoding_a,&encoding_a);
    printf("\n%p %p %i\n",encoding_a,&encoding_a,*encoding_a);
}

void iconv_test(){
    const char *kiindulo = "Ascii";
    const char *cel = "UTF8";
    iconv_t cd = iconv_open(cel,kiindulo);

    char *inbuf="the quick brown fox jumps over the lazy dog";
    size_t inbytesleft=strlen(inbuf)+1;
    char *outbuf=(char*) malloc(sizeof(char[44]));
    char *outbuf2 = outbuf;
    size_t outbytesleft=sizeof(char[44]);
    iconv(cd,&inbuf,&inbytesleft,&outbuf,&outbytesleft);

    printf("%s\n",outbuf2);
    iconv_close(cd);
}

int main() {
    printf("Hello world!\n");

    ///hashtable test
    /*hashtable *x=hashtable_init(256,sizeof(char[10]),sizeof(char[10]));
    char* temp = "aaaaaa\0\0\0";
    char* a = (char*) malloc(sizeof(char[10]));
    memcpy(a,temp,10);
    printf("%d -> ",x->usage);
    hashtable_put(x,a,a);
    printf("%d\n",x->usage);
    printf("%d\n",sizeof(temp));
    printf("%s %c %p %p %p\n",a,*a,&a[0],&a[1],a);

    char* akeres = (char*) malloc(sizeof(char[10]));
    memcpy(akeres,temp,10);

    printf("%s %c %p %p %p\n",akeres,*akeres,&akeres[0],&akeres[1],akeres);
    int n=memcmp ( a, akeres, sizeof(char[10]) );
    printf("%i\n",n);
    char* atalal = (char*) malloc(sizeof(char[10]));

    if( hashtable_get(x,akeres,atalal)
            == HASH_NOTFOUND )
        printf("*alias error\n");
    else
        printf("%s\n",atalal);

    free(a);
    free(atalal);
    free(akeres);
    hashtable_free(x);*/

    ///memcmp test
    /*char buffer1[] = "abcd\0\0\0";
    char buffer2[] = "abcd\0\0\0";
    int n;
    n=memcmp ( buffer1, buffer2, sizeof(buffer1) );
    if (n>0)
        printf ("'%s' is greater than '%s'.\n",buffer1,buffer2);
    else if (n<0)
        printf ("'%s' is less than '%s'.\n",buffer1,buffer2);
    else
        printf ("'%s' is the same as '%s'.\n",buffer1,buffer2);*/


    ///aliases_hashtable test
    printf("---------aliases-------\n");
    const char *fromcode = "Ascii";
    char *fromcode_realname = (char*) malloc(sizeof(char[10]));

    hashtable *aliases=aliases_hashbtable();
    ///hashtable* aliases = hashtable_init(256, sizeof(char**), sizeof(char**));
    ///feltolt(aliases);

    printf("\n%i\n",aliases->usage);
    printf("%p %p %i\n",fromcode,&fromcode,*fromcode);

    if( hashtable_get(aliases,fromcode,fromcode_realname)
            == HASH_NOTFOUND )
        printf("*alias error\n");
    else
        printf("%s\n",fromcode_realname);
    hashtable_free(aliases);


    ///hashtable test with nums
    /*printf("\n");
    hashtable *x=hashtable_init(128,sizeof(char[10]),sizeof(uint8_t));
    char* temp = "aaaaaa\0\0\0";
    char* a = (char*) malloc(sizeof(char[10]));
    memcpy(a,temp,10);
    uint8_t aertek=2;
    printf("%d -> ",x->usage);
    hashtable_put(x,a,&aertek);
    printf("%d\n",x->usage);
    printf("%s %c %p %p %p\n",a,*a,&a[0],&a[1],a);

    char* akeres = (char*) malloc(sizeof(char[10]));
    memcpy(akeres,temp,10);

    printf("%s %c %p %p %p\n",akeres,*akeres,&akeres[0],&akeres[1],akeres);
    int n=memcmp ( a, akeres, sizeof(char[10]) );
    printf("%i\n",n);
    uint8_t atalal;
    printf("%p %d\n",&atalal,&atalal);

    if( hashtable_get(x,akeres,&atalal)
            == HASH_NOTFOUND )
        printf("*length error\n");
    else
        printf("%p %d %u %x\n",&atalal,atalal,atalal,atalal,atalal);

    free(a);
    free(akeres);
    hashtable_free(x);
    */

    ///unit_length test
    printf("\n----------length--------\n");
    const char *tocode = "UTF8";
    hashtable* lengths = unit_lenghts();
    printf("table ok\n");
    uint8_t from_length;
    printf("%d\n",lengths->usage);
    if( hashtable_get(lengths, tocode, &from_length)
            == HASH_NOTFOUND)
        printf("*unit length error");
    else
        printf("%i\n",from_length);
    hashtable_free(lengths);


    ///mappings test
    /*printf("\n--------mappings------\n");
    hashtable* maps=mappings();
    printf("table ok %d\n",maps->usage);

    hashtable* temp;
    if( hashtable_get(maps, fromcode_realname, &temp)
            == HASH_NOTFOUND)
        printf("*\"from\" table error\n");
    else
        printf("table #2 ok %i\n",temp->usage);

    hashtable* map;
    if( hashtable_get(temp, tocode, &map)
            == HASH_NOTFOUND)
        printf("*\"to\" table error\n");
    else
        printf("table #3 ok %i\n",map->usage);


    char *p="abcd";
    uint32_t egyik=*p;

    uint8_t masik;
    if( hashtable_get(map, &egyik, &masik)
            == HASH_NOTFOUND)
        printf("*\"conversion\" table error\n");
    else
        printf("table #4 ok %i\n",masik);
    */


    ///iconv_open test
    printf("\n----------open--------\n");
    printf("%s %s\n",fromcode,tocode);
    iconv_t test2 = iconv_open(tocode,fromcode);
    if(test2!=(iconv_t)-1) {
        iconv_t_data *test= (iconv_t_data*) test2;
        uint8_t fromvalue;
        uint32_t tovalue;

        for(int i=67; i<73; i++) {
            fromvalue=i;
            if(hashtable_get(test->mapping,&fromvalue,&tovalue)!=HASH_NOTFOUND)
                printf("to:   %d\n",tovalue);
            else
                printf("from: %d\n",fromvalue);
        }
    } else
        printf("error %i %i\n",errno,(int)test2);

    ///iconv test
    /*printf("\n----------iconv--------\n");
    char* inbuf="the quick brown fox jumps over the lazy dog";
    //..........0.........01........01........01.......01..4
    size_t inbytesleft=strlen(inbuf)+1;
    char* outbuf=(char*) malloc(sizeof(char[44]));
    char* outbuf2=outbuf;
    size_t outbytesleft=sizeof(char[44]);
    iconv(test2,&inbuf,&inbytesleft,&outbuf,&outbytesleft);
    printf("%s\n",outbuf2);*/

    /*
    //char* p="aaab";
    uint32_t a=p[0];
    for(int i=2;i<=3;i++){
        a=(a<<8)+p[0+i-1];
    }
    printf("%d\n",a);
    char b=a;
    for(int i=1;i<=3;i++){
        b=(a&(0xFF<<((3-i)*8) ))>> ((3-i)*8);
        printf("%c",b);
    }*/

    //iconv_test();


    printf("\n----------iso88592--------\n");
    const char *source = "iso88592";
    const char *target = "ascii";
    iconv_t cd = iconv_open(target,source);

    if(cd!=-1){
        FILE *file_in=fopen("from.txt","r");
        FILE *file_ou=fopen("to.txt","w");
        char *inbuf=(char*) malloc(sizeof(char[100]));
        char *inbuf2=inbuf;
        char *outbuf=(char*) malloc(sizeof(char[100]));
        char *outbuf2=outbuf;
        if(file_ou==NULL) printf("file error 2");
        else if(file_in==NULL)printf("file error");
        else while(fgets(inbuf,100,file_in)!=NULL){
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

    return 0;
}
