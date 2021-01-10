#include <ld_lib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./ld input_file output_file\n");
        return 1;
    }
    
    const char *in = argv[1];
    const char *out = argv[2];

    link(in, out);

    return 0;
}
