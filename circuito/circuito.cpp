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
    return (I>=0 && I<Nin);
}

bool Port::valid() const
{
    bool aux = true;
    for(int i=0; i<int(Nin)-1; i++){if(id_in[i]!= 0){aux=false;}}
    return (validNumInputs(Nin)&& aux);
}
//funcoes de consulta
// Caracteristicas da porta
unsigned Port::getNumInputs() const
 {
     return Nin;
 }
bool3S Port::getOutput() const
{
    return saida;
}
int Port::getId_in(unsigned I) const
{
    if(validIndex(I)){return id_in[I];}
    else{return 0;}
}
//funcoes de modificação
void Port::setNumInputs(unsigned N)
{
    if(validNumInputs(N)){Nin = N;}
}

void Port::setOutput(bool3S S){saida=S;}

void Port::setId_in(unsigned I, int Id)
{
    if(validIndex(I) && Id!= 0){id_in[I] = Id;}
}

//funcao de digitação
 void Port::digitar()
 {
    do
    {
        //cout<<"Nº de entradas: ";
        cin>> Nin;
    } while(Nin<2 || Nin>NUM_MAX_INPUTS_PORT);

    for(int i=0; i<int(Nin); i++)
    {
        //cout<<"Digite o id de entrada";
        do
        {
        cin>>id_in[i];
        if(id_in[i]==0){cout<<"Voce digitou uma id invalida\n";}
        }while(id_in[i]==0);

    }
 }
bool Port::ler(std::istream& ArqI)
{
    ArqI>>Nin;
    if(validNumInputs(Nin)){}else{return false;}
    for(int i=0; i<int(Nin); i++)
    {
        ArqI>>id_in[i];
    }
    return true;
}

std::ostream& Port::imprimir(std::ostream& ArqO) const
{
  ///precisa implementar
}


std::ostream& operator<<(std::ostream& O, const Port& X)
{
    (&X)->imprimir(O);
    return O;
}

///Classe Port_not
//construtor
Port_NOT::Port_NOT(): Port(1){}
//clone
ptr_Port Port_NOT::clone() const
{
    return new Port_NOT(*this);
}

//metodo que retorna a sigla da porta
std::string Port_NOT::getName() const{return "NT";}

//funcao que testa a validade do numero de entradas
bool Port_NOT::validNumInputs(unsigned NI) const{ return NI==1;}

// funcao de digitação
void Port_NOT::digitar()
{
    Nin=1;
    //cout<<"Digite o id de entrada";
    do
    {
        cin>>id_in[0];
        if(id_in[0]==0){cout<<"Voce digitou uma id invalida\n";}
    }while(id_in[0]==0);
}

//funcao que simula o circuito
bool3S Port_NOT::simular(const bool3S In[])
{
    ///farei na tarde de 07/09
}








