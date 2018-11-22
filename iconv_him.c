#include "iconv_him.h"

char* calcString(char* s){
    char* ret=(char*) malloc(sizeof(char[10]));
    for(int i=0;i<9;i++){
        if(i<strlen(s)) ret[i]=s[i];
        else ret[i]='\0';
    }
    ret[9]='\0';
    return ret;
}

iconv_t iconv_open(const char *tocode2, const char *fromcode2)
{
    char* tocode=calcString(tocode2);
    char* fromcode=calcString(fromcode2);
    iconv_t_data *returnval=(iconv_t_data*) malloc(sizeof(iconv_t_data));
    char *fromcode_realname= (char*) malloc(sizeof(char[10]));
    hashtable *aliases = aliases_hashbtable();
    if( hashtable_get(aliases,fromcode,fromcode_realname)
            == HASH_NOTFOUND )
        {errno=EINVAL;return ((iconv_t)-1);}
    hashtable_free(aliases);

    hashtable* lengths = unit_lenghts();
    if( hashtable_get(lengths, fromcode_realname, &(returnval->from_length))
            == HASH_NOTFOUND ||
            hashtable_get(lengths, tocode, &(returnval->to_length))
            == HASH_NOTFOUND)
        {errno= EINVAL;return (iconv_t) -1;}
    hashtable_free(lengths);

    returnval->allmappings = mappings();
    hashtable *frommapping;
    if( hashtable_get(returnval->allmappings,fromcode_realname,&frommapping)
            == HASH_NOTFOUND)
        {errno= EINVAL;return (iconv_t) -1;}
    if( hashtable_get(frommapping, tocode, &(returnval->mapping))
            == HASH_NOTFOUND)
        {errno= EINVAL;return (iconv_t) -1;}

    return (iconv_t)(void*)returnval;
}

int iconv_close(iconv_t cd)
{
    if(cd!=(iconv_t)-1)
    {
        iconv_t_data *x = (iconv_t_data*) cd;
        hashtable_free(x->allmappings);
    }
    return 0;
}

size_t iconv(iconv_t cd,
             char **restrict inbuf,  size_t *restrict inbytesleft,
             char **restrict outbuf, size_t *restrict outbytesleft)
{
    if(cd==(iconv_t)-1)
        {errno= EBADF;return (size_t)-1;}
    iconv_t_data *con=(iconv_t_data*) cd;
    if(*outbytesleft<con->to_length)
        {errno = E2BIG;return (size_t)-1;}
    size_t returnval;
    uint32_t fromvalue,tovalue;
    do
    {
        fromvalue=(*inbuf)[0];
        for(int i=2; i<=con->from_length; i++)
            fromvalue=(fromvalue<<8)+(*inbuf)[0+i-1];
        if(hashtable_get(con->mapping,&fromvalue,&tovalue)==HASH_NOTFOUND)
            tovalue=fromvalue;
        char b;
        for(int i=1; i<=con->to_length; i++)
        {
            b=(tovalue&(0xFF<<((con->to_length-i)*8)))>>((con->to_length-i)*8);
            **outbuf=b;
            *outbuf=*outbuf+sizeof(char);
        }
        if(*inbytesleft>=con->from_length && *outbytesleft>=con->to_length)
        {
            *inbuf=*inbuf+con->from_length;
            *inbytesleft=*inbytesleft-con->from_length;
            *outbytesleft=*outbytesleft-con->to_length;
        }
    }
    while(*inbytesleft>=con->from_length && *outbytesleft>=con->to_length);
    return 0;
}
