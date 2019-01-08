#include <iostream>
#include <string.h>
#include "usuario.h"
#include <vector>
#include "twitter.h"
#include <cstring>
#include <string>
usuario::usuario(char *login,char *nome)
{
    this->id = GeradorDeIDuser++;
    this->seguidores = 0;
    this->seguindo = 0;
    strcpy(this->login,login);
    strcpy(this->nome,nome);
}

void usuario::Sseguindo(char *aSeguir, int idaSeguir)
{
    feed[aSeguir] = idaSeguir;
}

void usuario::setseguindo(char *aSeguir, int idaSeguir)
{
    feed[aSeguir] = idaSeguir;
    ++seguindo;
}

map<string, int> usuario::retornafeed()
{
    return feed;
}

void usuario::setlogin(char *login)
{
    strcpy(this->login,login);
}

void usuario::setnome(char *nome)
{
    strcpy(this->login,login);
}

void usuario::setseguidores()
{
    seguidores++;
}

int usuario::getid()
{
    return id;
}
int usuario::getseguidores()
{
    return seguidores;
}
int usuario::getseguindo()
{
    return seguindo;
}
char* usuario::getlogin()
{
    return login;

}

char* usuario::getnome()
{
    return nome;
}

void usuario::setmensusuario(int i)
{
    idsmensagens[i] = i;
}

map<int,int> usuario::getmensusuario()
{
    return idsmensagens;
}

usuario::usuario(ifstream& is)
{
    char aux[50]= {-1};
    int aux2 = -1;
    is.read((char*)&id, sizeof(int));
    is.read(login,sizeof(char[50]));
    is.read(senha, sizeof(char[10]));
    is.read(nome,sizeof(char[50]));
    is.read((char*)&seguidores,sizeof(int));
    is.read((char*)&seguindo,sizeof(int));
    while(is.good())
    {
        aux2 = -1;
        is.read(aux, sizeof(char[50]));
        is.read((char*)&aux2, sizeof(int));
        cout<<endl<<aux<<"      |      "<<aux2<<endl;
        if (aux2 != -1) Sseguindo(aux,aux2);
    }
}

ostream& operator<<(ostream& os, usuario& user)
{
    map<int, int> mensagens = user.getmensusuario();
    map<int, int>::iterator it;
    for (it = mensagens.begin(); it != mensagens.end(); ++it)
    {
        os.write((char*)&it->first, sizeof(int));
        cout<<endl<<it->first<<"     ";
        os.write((char*)&it->second, sizeof(int));
        cout<<it->second;
    }
    return os;
}

ostream& operator>>(ostream& os, usuario& user)
{
    cout << endl << "ID " << user.getid() << "/" << user.id
            << endl << "login " << user.login
            << endl << "nome " << user.nome
            << endl << "seguidores " << user.seguidores
            << endl << "seguindo " << user.seguindo;

    map<string, int> FeedAux = user.retornafeed();
    map<string, int>::iterator itAux;
    for (itAux = FeedAux.begin(); itAux != FeedAux.end(); ++itAux)
    {
        cout << endl << "it->first" << itAux->first
                << endl << "it->second " << itAux->second << endl;

    }

    os.write((char*)&user.id, sizeof(int));
    os.write(user.login,sizeof(char[50]));
    os.write(user.senha, sizeof(char[10]));
    os.write(user.nome,sizeof(char[50]));
    os.write((char*)&user.seguidores,sizeof(int));
    os.write((char*)&user.seguindo,sizeof(int));
    os<<"\n";
    map<string, int> Feed = user.retornafeed();
    map<string, int>::iterator it;
    for (it = Feed.begin(); it != Feed.end(); ++it)
    {
        char escreve[50]; strcpy(escreve, it->first.c_str());
        os.write(escreve, sizeof(char[50]));
        os.write((char*)&it->second, sizeof(int));
    }
    return os;
}

void usuario::pegamens(ifstream& is)
{
    int aux = -1;
    int aux2 = -1;
    while(is.good())
    {

        is.read((char*)&aux, sizeof(int));
        is.read((char*)&aux2, sizeof(int));
        cout<<endl<<"mens:  "<<aux<<"      |      "<<aux2<<endl;
        if (aux != (-1)) setmensusuario(aux);

    }
}

void usuario::armazenaMsg(usuario u)
{
    ofstream ofs;
    string result = twitter::instancia()->convertInt(u.getid());
    string auxNome = result + "Msg";
    ofs.open(auxNome,ios::out|ios::binary|ios::in|ios::trunc);
    ofs<<u;
    ofs.close();
}

void usuario::armazenaFeed(usuario u)
{
    ofstream ofs;
    string result = twitter::instancia()->convertInt(u.getid());
    string auxNome = result + "Feed";
    ofs.open(auxNome,ios::out|ios::binary|ios::in|ios::trunc);
    ofs>>u;
    ofs.close();
}
