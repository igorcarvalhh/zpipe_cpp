#include <iostream>
#include <fstream>
#include <string>
#include "zlib.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

using namespace std;

int def(istream &source, ostream &dest, int level) {

    int ret, flush;
    unsigned have;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    char* inp = (char*) in;
    char* outp = (char*) out;

    z_stream strm;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    
    ret = deflateInit(&strm, level);
    if (ret != Z_OK) {
        return ret;
    }

    do {
        strm.avail_in = source.readsome(inp, CHUNK);

        // [TODO] write validation to confirm that all bytes were read
        // example:
        // if (ferror(source)) {
        //     (void)deflateEnd(&strm);
        //     return Z_ERRNO;
        // }
    
        streamsize count = source.gcount();
        flush = (count < CHUNK) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = deflate(&strm, flush); 
            have = CHUNK - strm.avail_out;
            dest.write(outp, have);

            // [TODO] write validation to confirm that all bytes were written
            // example: 
            // if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
            //     (void)deflateEnd(&strm);
            //     return Z_ERRNO;
            // }

        } while (strm.avail_out == 0);

    } while (flush != Z_FINISH);

    (void)deflateEnd(&strm);
    return Z_OK;
}

int inf(istream &source, ostream &dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    char* inp = (char*) in;
    char* outp = (char*) out;

    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;

    ret = inflateInit(&strm);
    if (ret != Z_OK) {
        return ret;
    }

    do {
        strm.avail_in = source.readsome(inp, CHUNK);

        // [TODO] write validation to confirm that all bytes were read
        // example:
        // if (ferror(source)) {
        //     (void)inflateEnd(&strm);
        //     return Z_ERRNO;
        // }

        if (strm.avail_in == 0)
            break;
        strm.next_in = in;

        do {
            strm.avail_out = CHUNK;
            strm.next_out = out;
            ret = inflate(&strm, Z_NO_FLUSH);
            switch (ret) {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&strm);
                    return ret;
            }
            have = CHUNK - strm.avail_out;
            dest.write(outp, have);

            // [TODO] write validation to confirm that all bytes were written
            // example:
            // if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
            //     (void)inflateEnd(&strm);
            //     return Z_ERRNO;
            // }

        } while (strm.avail_out == 0);

    } while (ret != Z_STREAM_END);

    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}

int main(int argc, char* argv[]) {

    ifstream source("input.txt");
    ofstream dest("output.txt");

    def(source, dest, Z_DEFAULT_COMPRESSION);
    // inf(source, dest);

    return 0;
}