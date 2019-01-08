#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED
#include <fstream>
#include <map>
using namespace std;

extern int GeradorDeIDuser;

class usuario
{
private:
    int id;
    int seguidores = 0;
    int seguindo = 0;
    char login[50];
    char nome[50];
    char senha[10];
    map <int,int> idsmensagens;
    map <string, int> feed;
public:
    usuario(ifstream&); //Construtor que constr�i a partir de um arquivo
    usuario(char *login,char *nome); //Construtor para cadastro de usuarios
    void setid(int id);
    void setseguindo(char*, int);
    void setseguidores();
    void setlogin(char *login);
    void setnome(char *nome);
    void setmensusuario(int i);
    map<int,int> getmensusuario(); //Retorna as mensagens do map de IDs de mensagens do usu�rio
    int getid();
    int getseguidores();
    int getseguindo();
    char* getlogin();
    char* getnome();
    friend ostream& operator<<(ostream& os, usuario& user); //Sobrecarga para escrita das mensagens do usu�rio em arquivo
    static void armazenabin(usuario user); //Armazena um usu�rio (user) em arquivo bin�rio
    map<string, int> retornafeed(); //Retorna a mensagem mais recente dos usu�rios que o usu�rio segue
    friend ostream& operator>>(ostream& os, usuario& user); //Sobrecarga para escrita dos seguidores do usu�rio em arquivo
    static void armazenaMsg(usuario); //Armazena as mensagens do usu�rio em arquivo
    static void armazenaFeed(usuario); //Armazena os seguidores do usu�rio em arquivo
    void Sseguindo(char *aSeguir, int idaSeguir); //Define o n�mero de seguidores no arquivo
    void pegamens(ifstream&); //L� as mensagens do arquivo
};

#endif
