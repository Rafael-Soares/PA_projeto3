#include <iostream>
#include "circuito.h"
#include "bool3S.h"

using namespace std;
///------------------------------------------------------------classe port-----------------------------------------------
///Classe Port
//Construtor
Port::Port(unsigned NI): Nin(NI), saida(bool3S::UNDEF)
{
    if(!validNumInputs(NI)) Nin=0;
    for(int i=0; i<NUM_MAX_INPUTS_PORT; i++)
    {
        id_in[i] = 0;
    }
}
//construtor por copia
Port::Port(const Port& P)
{
    Nin=P.Nin;
    for(int i=0; i<NUM_MAX_INPUTS_PORT; i++)
    {
        this->id_in[i]=P.id_in[i];
    }
    saida = P.saida;
}
Port::~Port(){}

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
    for(unsigned i=0; i<Nin; i++){if(id_in[i] == 0){aux=false;}}
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
        cout<<"Nº de entradas: ";
        cin>> Nin;
        if (!validNumInputs(Nin)){cout<<"Valor fora do escopo, digite novamente.\n";}

    } while(!validNumInputs(Nin));

    cout<<"Digite o id's de entrada";
    for(int i=0; i<int(Nin); i++)
    {

        do
        {
        cin>>id_in[i];
        if(!valid()){cout<<"Voce digitou uma id invalida, digite outra.\n";}
        }while(!valid());

    }
 }
bool Port::ler(std::istream& ArqI)
{
    ArqI>>Nin;
    if(this->validNumInputs(Nin))
    {
         char c;
         ArqI>>c;
         if(c==':') for(unsigned i=0; i<Nin; i++)
         {
            ArqI>>id_in[i];
         }
        else
        {
            Nin=0;
        }
    }
    if (!valid())
    {
        Nin = 0;
        return false;
    }
    return true;
}

ostream& Port::imprimir(ostream& ArqO) const
{
    ArqO<<this->getName()<<' ';
    ArqO<<Nin<<":";
    unsigned i;
    for(i=0; i<Nin; i++){ArqO << ' ' << id_in[i];}
    return ArqO;
}


std::ostream& operator<<(std::ostream& O, const Port& X)
{
    (&X)->imprimir(O);
    return O;
}
///---------------------------------------------------implementacao das portas logicas------------------------------------
///Classe Port_NOT
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
    cout<<"Digite o id de entrada";
    do
    {
        cout<<"Digite o id de entrada: ";
        cin>>id_in[0];
        if(id_in[0]==0){cout<<"Voce digitou uma id invalida\n";}
    }while(id_in[0]==0);
}

//funcao que simula a porta not
bool3S Port_NOT::simular(const bool3S In[])
{
        saida = ~In[0];
        return saida;
}

///Classe port_AND
//construtor
Port_AND::Port_AND(): Port(){}

//clone
ptr_Port Port_AND::clone() const
{
    return new Port_AND(*this);
}
//metodo que retorna a sigla da porta
std::string Port_AND::getName() const{return "AN";}
//funcao que simula a porta and
bool3S Port_AND::simular(const bool3S In[])
{
    saida = In[0];
    for(unsigned i=1; i<getNumInputs(); i++)
    {
       if (saida == bool3S::FALSE) break;
       saida = saida & In[i];
    }
    return saida;
}

///Classe port_NAND
//construtor
Port_NAND::Port_NAND(): Port(){}

//clone
ptr_Port Port_NAND::clone() const
{
    return new Port_NAND(*this);
}
//metodo que retorna a sigla da porta
std::string Port_NAND::getName() const{return "NA";}
//funcao que simula a porta and
bool3S Port_NAND::simular(const bool3S In[])
{
    saida = In[0];
    for(unsigned i=1; i<getNumInputs(); i++)
    {
       if (saida == bool3S::FALSE) break;
       saida = saida & In[i];
    }
    return ~saida;
}
///Classe Port_OR
//construtor
Port_OR::Port_OR(): Port(){}

//clone
ptr_Port Port_OR::clone() const
{
    return new Port_OR(*this);
}
//metodo que retorna a sigla da porta
std::string Port_OR::getName() const{return "OR";}
//funcao que simula a porta OR
bool3S Port_OR::simular(const bool3S In[])
{
    saida = In[0];
    for(unsigned i=1; i<getNumInputs(); i++)
    {
        if(saida == bool3S::TRUE) break;
        saida = saida | In[i];
    }
    return saida;
}

///Classe Port_NOR
//construtor
Port_NOR::Port_NOR(): Port(){}

//clone
ptr_Port Port_NOR::clone() const
{
    return new Port_NOR(*this);
}
//metodo que retorna a sigla da porta
std::string Port_NOR::getName() const{return "NO";}
//funcao que simula a porta NOR
bool3S Port_NOR::simular(const bool3S In[])
{
    saida = In[0];
    for(unsigned i=1; i<getNumInputs(); i++)
    {
        if(saida == bool3S::TRUE) break;
        saida = saida | In[i];
    }
    return ~saida;
}

///Classe Port_XOR
//construtor
Port_XOR::Port_XOR(): Port(){}

//clone
ptr_Port Port_XOR::clone() const
{
    return new Port_XOR(*this);
}
//metodo que retorna a sigla da porta
std::string Port_XOR::getName() const{return "XO";}
//funcao que simula a porta XOR
bool3S Port_XOR::simular(const bool3S In[])
{
    saida = In[0];
    for(unsigned i=1; i<getNumInputs(); i++)
    {
        saida = saida^In[i];
    }
    return saida;
}

///Classe Port_NXOR
//construtor
Port_NXOR::Port_NXOR(): Port(){}

//clone
ptr_Port Port_NXOR::clone() const
{
    return new Port_NXOR(*this);
}
//metodo que retorna a sigla da porta
std::string Port_NXOR::getName() const{return "NX";}
//funcao que simula a porta NXOR
bool3S Port_NXOR::simular(const bool3S In[])
{
    saida = In[0];
    for(unsigned i=1; i<getNumInputs(); i++)
    {
        saida = saida^In[i];
    }
    return ~saida;
}
///------------------------------------------------------classe circuito----------------------------------------------

//construtor
Circuit::Circuit(): inputs(), id_out(), ports() {}

// Construtor por copia
Circuit::Circuit(const Circuit& C)
{
    for (unsigned i=0; i<C.getNumPorts(); i++) {ports.push_back(C.ports[i]->clone());}
}
//destrutor
Circuit::~Circuit(){clear();}

void Circuit::clear()
{
  for (unsigned i=0; i<getNumPorts(); i++) if (ports[i]!=nullptr) delete ports[i];
  ports.clear();
}
// Caracteristicas do circuito
// Retorna o tamanho (size) dos vetores correspondentes:
// inputs, id_out e ports, respectivamente
unsigned Circuit::getNumInputs() const{ return inputs.size();}
unsigned Circuit::getNumOutputs() const{ return id_out.size();}
unsigned Circuit::getNumPorts() const{return ports.size();}

  // Operador de atribuicao
void Circuit::operator=(const Circuit& C)
{
    inputs = C.inputs;
    id_out = C.id_out;
    ports = C.ports;
}

void Circuit::resize(unsigned NI, unsigned NO, unsigned NP)
{
    if(NI==0 || NO==0 || NP==0) return;
    clear();
    inputs.resize(NI);
    id_out.resize(NO);
    ports.resize(NP);
    for (unsigned i=0; i<getNumInputs(); i++) inputs[i] = bool3S::UNDEF;
    for (unsigned i=0; i<getNumOutputs(); i++) id_out[i] = 0;
    for (unsigned i=0; i<getNumPorts(); i++) ports[i] = nullptr;
}

bool Circuit::validIdInput(int IdInput) const
{
    return (IdInput<=-1 && IdInput>=-int(getNumInputs()));
}
bool Circuit::validIdOutput(int IdOutput) const
{
    return (IdOutput>=1 && IdOutput<=int(getNumOutputs()));
}

bool Circuit::validIdPort(int IdPort) const
{
    return (IdPort>=1 && IdPort<=int(getNumPorts()));
}

bool Circuit::validIdOrig(int IdOrig) const
{
    return (validIdInput(IdOrig) || validIdPort(IdOrig));
}

bool Circuit::valid() const
{
    if(getNumInputs()==0) return false;
    if(getNumOutputs()==0) return false;
    if(getNumPorts()==0) return false;
    for(unsigned i=0; i<getNumOutputs(); i++)
    {
        if(!validIdOrig(getIdOutput(i+1))) return false;
    }
    return true;
}
bool3S Circuit::getInput(int IdInput) const
{
    if(validIdInput(IdInput)) {return inputs[-IdInput-1];}
    else{ return bool3S::UNDEF;}
}

int Circuit::getIdOutput(int IdOutput) const
{
    if(validIdOutput(IdOutput)) return id_out[IdOutput-1];
    return 0;
}

bool3S Circuit::getOutput(int IdOutput) const
{
    bool3S prov(bool3S::UNDEF);
    int id = getIdOutput(IdOutput);
    if (validIdOrig(id))
    {
        if(id>0){prov = ports[id-1]->getOutput();}
        else{ prov = inputs[-id-1];}
    }
    return prov;
}
std::string Circuit::getNamePort(int IdPort) const
{
    if(validIdPort(IdPort) && ports[IdPort-1]!=nullptr) return ports[IdPort-1]->getName();
    return "??";
}

unsigned Circuit::getNumInputsPort(int IdPort) const
{
    if(validIdPort(IdPort) && ports[IdPort-1]!=nullptr) return ports[IdPort-1]->getNumInputs();
    return 0;
}

int Circuit::getId_inPort(int IdPort, unsigned I) const
{
    if(validIdPort(IdPort) && ports[IdPort-1]!=nullptr) return ports[IdPort-1]->getId_in(I);
    return 0;
}
//funcao auxiliar para testar sigla da porta
bool namePortValid(const string& tipo)
{
    if(tipo=="NT"||tipo=="AN"||tipo=="NA"||tipo=="OR"||tipo=="NO"||tipo=="XO"||tipo=="NX") return true;
    return false;
}
// funcao auxiliar que criar uma nova area de memoria
ptr_Port PortAloca(const string& tipo)
{
    if(!namePortValid(tipo)) return nullptr;
    if(tipo=="NT"){ return new Port_NOT();}
    if(tipo=="AN"){ return new Port_AND();}
    if(tipo=="NA"){ return new Port_NAND();}
    if(tipo=="OR"){ return new Port_OR();}
    if(tipo=="NO"){ return new Port_NOR();}
    if(tipo=="XO"){ return new Port_XOR();}
    if(tipo=="NX"){ return new Port_NXOR();}

    return nullptr;
}
void Circuit::setPort(int IdPort, const std::string& Tipo, unsigned NIn)
{
    if(!validIdPort(IdPort)) return;
    if(!namePortValid(Tipo)) return;
    if(Tipo=="NT") { if(NIn!=1) return;}
    else
    {
        if(NIn<2 || NIn>NUM_MAX_INPUTS_PORT) return;
    }
    if(ports[IdPort-1]!=nullptr) delete ports[IdPort-1];
    ports[IdPort-1] = PortAloca(Tipo);
    ports[IdPort-1]->setNumInputs(NIn);
}
void Circuit::setId_inPort(int IdPort, unsigned I, int IdOrig) const
{
    if(!validIdPort(IdPort)) return;
    if(ports[IdPort-1] == nullptr) return;
    if(!ports[IdPort-1]->validIndex(I)) return;
    if(!validIdOrig(IdOrig)) return;
    ports[IdPort-1]->setId_in(I,IdOrig);
}
void Circuit::setIdOutput(int IdOut, int IdOrig)
{
    if(validIdOutput(IdOut) && validIdOrig(IdOrig))
    {
        id_out[IdOut-1] = IdOrig;
    }
}

bool Circuit::simular(const std::vector<bool3S>& Inputs)
{
    bool tudo_def,algum_def;
    bool3S in[NUM_MAX_INPUTS_PORT];
    int id;
    for (int i = 0;i < (getNumPorts()-1); i++)
    {
     porta[i].saida = bool3s::UNDEF;
    }
    do
    {
        tudo_def = 1;
        algum_def = 0;
        for (int i = 0;i < (getNumPorts()-1); i++)
        {
            if(porta[i].saida == bool3s::UNDEF)
            {
                    for (int j = 0;j < (getNumInputs()-1); j++)
                    {
                        id = porta[i].id_in[j];
                        if(id>0)
                            in[j] = porta[id-1].saida;
                        else
                            in[j] = inputs_circ[-id-1];

                    }
                    porta[i].simular[in];

                    if(porta[i].saida == bool3s::UNDEF)
                        tudo_def = 0;
                    else
                        algum_def = 1;
            }

        }

    }while(!tudo_def && algum_def);
}






