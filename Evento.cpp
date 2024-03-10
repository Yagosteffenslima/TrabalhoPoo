#include "Evento.h"

// Implementação do construtor da classe Evento
Evento::Evento(int timeStamp) : timeStamp(timeStamp) {}

// Implementação do método getTimeStamp da classe Evento
int Evento::getTimeStamp() const {
    return timeStamp;
}
