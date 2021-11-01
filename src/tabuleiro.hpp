#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP
#include <iostream>
#include "peça.hpp"


namespace final{    
    class tabuleiro
    {
    private:
        
        int** map; //atributo map, que é um ponteiro para um ponteiro
        peca* red; //atributo red, que é um ponteiro do tipo peça. O red é utilizado para as peças do time vermelho
        peca* blue; //atributo blue, que é um ponteiro do tipo peça. O blue é utilizado para as peças do time azul
    public:
        //Construtor e destrutor
        tabuleiro();
        ~tabuleiro();
        //Sobrecarga do operador de saída para printar o tabuleiro no terminal. 
        friend std::ostream& operator<<(std::ostream& os, tabuleiro &tabuleiro)
        {
                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        os<< tabuleiro.map[i][j]<<" ";
                    }
                    os<<"\n";
                }
                return os;
        }
        //Altera o valor da matriz na posição desejada
        void mudaMatriz(int x, int y, int value){
            if(x<0||x>7||y<0||y>7)    return; //Verifica argumentos
            map[x][y]=(value);
        };
        //Retorna o valor armazenado na matriz em certa posição
        int consultaMatriz(int x, int y){
            if(int(x)<0||int(x)>7||int(y)<0||int(y)>7)  return -1; //Verifica argumentos
            return (map[x][y]);
        }
        //Retorna coordenadas de certa peça
        unsigned X(unsigned time,unsigned i){
            if(int(i)<0||int(i)>11)     return 99; //Verifica argumentos
            if(time==1){
                return red[i].X(); //Retorna a coordenada X do time vermelho
            }else{
                return blue[i].X(); //Retorna a coordenada Y do time azul
            }
        }
        unsigned Y(unsigned time,unsigned i){
            if(int(i)<0||int(i)>11)    return 99; //Verifica argumentos
            if(time==1){
                return red[i].Y(); //Retorna a coordenada Y do time vermelho
            }else{
                return blue[i].Y(); //Retorna a coordenada Y do time azul
            }
        }
        //Retorna se certa peça é Dama, em caso afirmativo, retornará True
        bool Dama(int time,int index){
            if (index >=0 && index<11){
                if(time==1){
                    return red[index].Dama(); 
                }else if(time==2){
                    return blue[index].Dama();
                }
            }
            return false;
        }
        //Seta o atributo dama da classe peça para True no caso da peça ser dama
        void Dama(int time,int index, bool b){
            if (index >=0 && index<11){
                if(time==1){
                    red[index].Dama(b);
                }else if(time==2){
                    blue[index].Dama(b);
                }
            }
        }
        //Retorna indice da peça na coordenada para saber qual peça está naquela posição
        int at(int x,int y){
            if (x>=0 && x<8 && y>=0 && y<8){
                for (int i = 0; i < 12; i++)
                {
                    if((int(blue[i].X())==x && int(blue[i].Y())==y)){
                        return i;
                    }else if((int(red[i].X())==x && int(red[i].Y())==y)){
                        return i;
                    }
                }
            }
            return -1;
        }
        //Seta coordenada de certa peça 
        void X(unsigned time,unsigned i, unsigned x){
            if(int(i)<0||int(i)>11)    return; //Verifica argumentos
            if(time==1){
                red[i].X(x); //seta a coordenada X da peça escolhida do time vermelho para a posição desejada
            }else{
                blue[i].X(x); //seta a coordenada X da peça escolhida do time azul para a posição desejada
            }
        }
        void Y(unsigned time,unsigned i, unsigned y){
            if(int(i)<0||int(i)>11)    return; //Verifica argumentos
            if(time==1){
                red[i].Y(y); //seta a coordenada Y da peça escolhida do time vermelho para a posição desejada
            }else{
                blue[i].Y(y); //seta a coordenada Y da peça escolhida do time azul para a posição desejada
            }
        }

    };

    tabuleiro::tabuleiro()
    {
        //inicializando times com 12 peças cada um
        //seta a posição de cada peça, sendo o primeiro parâmetro o time, o segundo, a fileira e o terceiro, a coluna
        red = new peca[12];
        red[0]= peca(1,0,1); 
        red[1]= peca(1,0,3);
        red[2]= peca(1,0,5);
        red[3]= peca(1,0,7);
        red[4]= peca(1,1,0);
        red[5]= peca(1,1,2);
        red[6]= peca(1,1,4);
        red[7]= peca(1,1,6);
        red[8]= peca(1,2,1);
        red[9]= peca(1,2,3);
        red[10]= peca(1,2,5);
        red[11]= peca(1,2,7);

        blue = new peca[12];
        blue[0]= peca(2,5,0);
        blue[1]= peca(2,5,2);
        blue[2]= peca(2,5,4);
        blue[3]= peca(2,5,6);
        blue[4]= peca(2,6,1);
        blue[5]= peca(2,6,3);
        blue[6]= peca(2,6,5);
        blue[7]= peca(2,6,7);
        blue[8]= peca(2,7,0);
        blue[9]= peca(2,7,2);
        blue[10]= peca(2,7,4);
        blue[11]= peca(2,7,6);
        
        //Inicializando o mapa
        map = new int*[8];
        for (int i = 0; i < 8; i++)
        {
            map[i]= new int[8];
        }
        

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                map[i][j]=0;
            }
        }
        for (int i = 0; i < 12; i++)
        {
            map[red[i].X()][red[i].Y()]=1;
            map[blue[i].X()][blue[i].Y()]=2;
        }
        

    }

    tabuleiro::~tabuleiro()
    {
        //desaloca memória
        delete [] red;
        delete [] blue;
        for (int i = 0; i < 8; i++)
        {
            delete [] map[i];
        }
        delete [] map;
    }

}
#endif