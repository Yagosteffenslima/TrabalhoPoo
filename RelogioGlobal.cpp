#include "RelogioGlobal.h"


long RelogioGlobal::dataAtual = 0;


void RelogioGlobal::setData(long newData) {
    dataAtual = newData;
}

long RelogioGlobal::getData() {
    return dataAtual;
}
