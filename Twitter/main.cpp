/*
INTEGRANTES: DOUGLAS - 28614
             GUSTAVO - 31404
             MARCO   - 30749
             PEDRO   - 28882
*/
#include "usuario.h"
#include "mensagem.h"
#include "binarioarq.h"
#include "twitter.h"
#include <windows.h> //Usar system("cls")
using namespace std;
int GeradorDeIDuser = 0;
int GeradorDeIDMensagem = 0;

int main()
{
    fstream fs; // Abre o arquivo de IDs na primeira execução do programa
    fs.open("ids");
    fs>> GeradorDeIDuser;
    fs>> GeradorDeIDMensagem;
    fs.close();
    twitter::instancia()->recebeusuario(); //Instancia da classe twitter
    int opcao;
    while(true)
    {
        inicio:
        cout << "\tTWITTER ECOi08 - 2.0\n"
                << "\n 1- Cadastro\n 2- Login\n 0- Sair\n\n";
        cin>>opcao;
        system("PAUSE");
        system ("cls");
        switch(opcao)
        {
        case 1:
        {

            char auxL[50], auxN[50];
            cout << "\nCadastro: Login / Nome\n";
            fflush(stdin);
            gets(auxL);
            fflush(stdin);
            gets(auxN);
            usuario temp(auxL, auxN);
            twitter::instancia()->cadastro(temp);
            system("PAUSE");
            system("cls");
            break;
        }
        case 2:
        {

            char auxL[50];
            cout << "\nInsira Login\n";
            cin >> auxL;
            system("PAUSE");
            system("cls");
            if (twitter::instancia()->login(auxL))
            {
                int opcao2 = -1;
                while (opcao2 != 8)
                {
                    cout << "\tOpcoes:\n"
                            << "\n 3- Seguir usuario\n 4- Postar\n 5- Buscar termo\n 6- Buscar usuario\n 7- Retornar ao feed\n 8- Deslogar\n 9- Sair\n\n";
                    cin >> opcao2;
                    system("PAUSE");
                    system("cls");
                    switch (opcao2)
                    {
                    case 3:
                    {
                        char auxN[50];
                        cout << "\nInsira quem deseja seguir:\n";
                        cin >> auxN;
                        if(twitter::instancia()->seguir(auxN))
                        {
                            cout<< "\n Voce esta seguindo o usuario com login: "<<auxN<<endl;
                        }
                        system("PAUSE");
                        system("cls");
                        break;
                    }
                    case 4:
                    {
                        char auxM[140];
                        cout << "\nTwittar\n";
                        fflush(stdin);
                        gets(auxM);
                        twitter::instancia()->enviartwitter(auxM);
                        cout<<" \n|Mensagem enviada|\n";
                        system("PAUSE");
                        system("cls");
                        break;
                    }
                    case 5:
                    {
                        char auxM[140];
                        cout << "\nMensagem a procurar\n";
                        cin >> auxM;
                        twitter::instancia()->procurarmensagemeretwitter(auxM);
                        system("PAUSE");
                        system("cls");
                        break;
                    }
                    case 6:
                    {
                        char auxM[140];
                        cout << "\nLogin do usuario que deseja procurar\n";
                        cin >> auxM;
                        if(twitter::instancia()->procuraperfilusuario(auxM)== false )
                        {
                            cout<<"\n Usuario nao encontrado\n";
                        }
                        system("PAUSE");
                        system("cls");
                        break;
                    }
                    case 7:
                    {
                        twitter::instancia()->feed();
                        system("PAUSE");
                        system("cls");
                        break;
                    }
                    case 8:
                    {
                        goto inicio;
                    }
                    case 9:
                    {
                        twitter::instancia()->armazenausuario(); //Armazena usuários em seus respectivos arquivos
                        ofstream ofs; //Salva no arquivo de IDs ao fechar o programa
                        ofs.open("ids");
                        ofs<< GeradorDeIDuser << endl;
                        ofs<< GeradorDeIDMensagem;
                        ofs.close();
                        return 0;
                    }
                    }
                }
            }
            break;
        }

        case 0:
        {
            twitter::instancia()->armazenausuario();
            ofstream ofs;  //Salva no arquivo de IDs ao fechar o programa
            ofs.open("ids");
            ofs<< GeradorDeIDuser << endl;
            ofs<< GeradorDeIDMensagem;
            ofs.close();
            return 0;
        }
        }
    }
}
