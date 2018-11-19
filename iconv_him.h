#ifndef ICONV_HIM
#define ICONV_HIM

#include<stdlib.h>
#include<errno.h>

#include "test3.h"
#include "hashtable.h"


typedef struct {
    hashtable *allmappings;
    hashtable *mapping;
    uint8_t from_length;
    uint8_t to_length;
} iconv_t_data;

typedef void* iconv_t;

iconv_t iconv_open(const char *tocode, const char *fromcode);
int iconv_close(iconv_t cd);
size_t iconv(iconv_t cd,
    char **restrict inbuf,  size_t *restrict inbytesleft,
    char **restrict outbuf, size_t *restrict outbytesleft);


#endif // ICONV_HIM
