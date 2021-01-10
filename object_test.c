#include <object_code.h>

int main()
{
    symbol_table[0].LC = 0x4;
    generate_object_code("test.lst", "main.obj");
    return 0;
}
