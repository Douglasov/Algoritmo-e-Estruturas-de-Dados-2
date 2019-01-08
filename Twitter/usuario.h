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
    usuario(ifstream&); //Construtor que constrói a partir de um arquivo
    usuario(char *login,char *nome); //Construtor para cadastro de usuarios
    void setid(int id);
    void setseguindo(char*, int);
    void setseguidores();
    void setlogin(char *login);
    void setnome(char *nome);
    void setmensusuario(int i);
    map<int,int> getmensusuario(); //Retorna as mensagens do map de IDs de mensagens do usuário
    int getid();
    int getseguidores();
    int getseguindo();
    char* getlogin();
    char* getnome();
    friend ostream& operator<<(ostream& os, usuario& user); //Sobrecarga para escrita das mensagens do usuário em arquivo
    static void armazenabin(usuario user); //Armazena um usuário (user) em arquivo binário
    map<string, int> retornafeed(); //Retorna a mensagem mais recente dos usuários que o usuário segue
    friend ostream& operator>>(ostream& os, usuario& user); //Sobrecarga para escrita dos seguidores do usuário em arquivo
    static void armazenaMsg(usuario); //Armazena as mensagens do usuário em arquivo
    static void armazenaFeed(usuario); //Armazena os seguidores do usuário em arquivo
    void Sseguindo(char *aSeguir, int idaSeguir); //Define o número de seguidores no arquivo
    void pegamens(ifstream&); //Lê as mensagens do arquivo
};

#endif
