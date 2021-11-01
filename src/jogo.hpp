#ifndef JOGO_HPP
#define JOGO_HPP
#include "tabuleiro.hpp"

namespace final{
    class jogo{

        final::tabuleiro* map; //ponteiro do tipo tabuleiro
        public:
            jogo();
            ~jogo();
            //Mostra o jogo, se desejado, no terminal
            void mostraJogo(){
                std::cout<< *map;
            }
            //Altera o valor da matriz na posição desejada
            void mudaMatriz(int x,int y, int value){
                map->mudaMatriz(x,y,value);
            }
            //Consulta o valor da matriz na posição desejada
            int consultaMatriz(int x, int y){
                return map->consultaMatriz(x,y);
            }
            //Retorna coordenadas de certa peça
            unsigned X(unsigned time,unsigned i){
                return map->X(time,i);
            }
            unsigned Y(unsigned time,unsigned i){
                return map->Y(time,i);
            }
            //Seta coordenada de certa peça
            void X(unsigned time,unsigned i, unsigned x){
                map->X(time,i, x);
            }
            void Y(unsigned time,unsigned i, unsigned y){
                map->Y(time,i, y);
            }
            //Retorna indice da peça na coordenada para saber qual peça está naquela posição
            int at(int x, int y){
                return map->at(x,y);
            }
            //Seta o atributo dama (True no caso da peça ser dama)
            bool Dama(int time,int index){
                return map->Dama(time, index);
            }
            //Retorna se peça é dama
            void Dama(int time,int index,bool b){
                return map->Dama(time, index, b);
            }
    };
    //Construtor
    jogo::jogo(){
        map = new final::tabuleiro();
    }
    //Destrutor
    jogo::~jogo(){
        delete map;
    }
}



#endif