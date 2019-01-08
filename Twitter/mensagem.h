#ifndef MENSAGEM_H_INCLUDED
#define MENSAGEM_H_INCLUDED
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "usuario.h"
using namespace std;

extern int GeradorDeIDMensagem;

class mensagem
{
private:
    int idUser;
    int id;
    char conteudo [140];
public:
    mensagem(); //Construtor default para mensagem
    mensagem(char conteudo[]); //Construtor que recebe um texto para uma nova mensagem
    mensagem(ifstream &is,int id); //Construtor que recebe uma mensagem do arquivo binário
    void setidUser(int idUser);
    void setconteudo(char conteudo[]);
    void setid(int id);
    int getid();
    int getidUser();
    char* getconteudo ();
    friend ostream& operator<<(ostream& os,const mensagem& msg); //Sobrecarga de operador para saída de mensagens
    friend istream& operator>>(istream &is,mensagem& msg); //Sobrecarga de operador para entrada de mensagens
    static void armazenabin(mensagem m); //Armazena uma mensagem m no arquivo binário
};
#endif
