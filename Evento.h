#ifndef EVENTO_H
#define EVENTO_H

// Classe abstrata que representa um evento no simulador
class Evento {
protected:
    // Timestamp do evento
    int timeStamp;

public:
    // Construtor da classe Evento
    Evento(int timeStamp);

    // Getter para obter o timestamp do evento
    int getTimeStamp() const;

    // Método virtual puro que será implementado nas subclasses
    virtual void execute() = 0;
};

#endif
