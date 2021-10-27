#include "instructions.h"

int main () {

    int ret;
    
    init_sys ();
    load_program ();

    do {
        fetch ();
        ret = decode ();
    } while (ret);

    return ret;
}
