#include "mensagem.h"
#include "usuario.h"

mensagem::mensagem()
{
    id = 0;
    strcpy(this->conteudo,"nada");
}

mensagem::mensagem(ifstream& is,int i)
{
    is.seekg(i*(149),ios::beg);
    is.read((char*)&id,sizeof(int));
    is.read(conteudo,sizeof(char[140]));
    is.read((char*)&idUser,sizeof(int));
}

void mensagem::setidUser(int idUser)
{
    this->idUser = idUser;
}

int mensagem::getidUser()
{
    return idUser;
}

void mensagem::setconteudo(char conteudo[])
{
    strcpy(this->conteudo,conteudo);
}

void mensagem::setid(int id)
{
    this->id = id;
}
int mensagem::getid()
{
    return id;
}

char *mensagem::getconteudo()
{
    return *&conteudo;//mitei <--
}

ostream& operator<<(ostream& os, const mensagem& msg)
{
    os.ostream::seekp(msg.id*(149),ios::beg);
    os.write((char*)&msg.id, sizeof(int));
    os.write(msg.conteudo,sizeof(char[140]));
    os.write((char*)&msg.idUser,sizeof(int));
    os<<"\n";
    return os;
}

void mensagem::armazenabin(mensagem m)
{
    ofstream ofs;
    ofs.open("arquivo.bin",ios::out|ios::binary|ios::in);
    ofs<<m;
    ofs.close();
}



