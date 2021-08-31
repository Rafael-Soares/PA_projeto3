#include <iostream>
#include "circuito.h"
#include "bool3S.h"

using namespace std;

///Classe Port
//Construtor
Port::Port(unsigned NI)
{
    if(NI>0) {Nin=NI;}
    for(int i=0; i<NUM_MAX_INPUTS_PORT; i++)
    {
        id_in[i] = 0;
    }
   saida=bool3S::UNDEF;
}
//construtor por copia
Port::Port(const Port& P)
{
    this->Nin=P.Nin;
    for(int i=0; i<NUM_MAX_INPUTS_PORT; i++)
    {
        this->id_in[i]=P.id_in[i];
    }
    this->saida = P.saida;
}
///Funcoes de testagem
bool Port::validNumInputs(unsigned NI) const
{
    return (NI>=2 && NI<=NUM_MAX_INPUTS_PORT);
}

bool Port::validIndex(unsigned I) const
{
    return (I>=0 && I<=Nin-1);
}

bool Port::valid() const
{
    bool aux = true;
    for(int i=0; i<int(Nin)-1; i++){if(id_in[i]!= 0){aux=false;}}
    return (validNumInputs(Nin)&& aux);
}

