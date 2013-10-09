#include <lf/Lightfeather.h>
#include "CTutorial1.h"


int main(int argc, char *argv[])
{

    lf::initLF();
    CTutorial1 *ex = new CTutorial1();

    ex->run();

    delete ex;
    lf::deinitLF();
    return 0;
}


