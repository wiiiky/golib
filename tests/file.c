#include <jio/jfile.h>
#include <jlib/jlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
    char *data =
        j_file_readall("/home/wiky/Documents/CODE/Git/jlib/tests/file.c");
    printf("%s", data);
    if (data == NULL) {
        return 1;
    }
    j_free(data);
    return 0;
}
