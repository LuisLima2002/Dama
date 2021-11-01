#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "jogador.hpp"
#include <SFML/Graphics.hpp>
#include <string>

namespace final{
    class manager{
        
        final::jogador* redPlayer; //ponteiro do tipo jogador usado para o time vermelho
        final::jogador* bluePlayer; //ponteiro do tipo jogador usado para o time azul
        
        public:
            //Construtor
            manager(){
                redPlayer= new final::jogador;
                bluePlayer= new final::jogador;
            }
            //Destrutor
            ~manager(){
                delete redPlayer;
                delete bluePlayer;
            }
            //Retorna uma string com a pontuação do jogador
            std::string pontuacao(unsigned time){
                if(time == 1){
                    std::string str="Pontuacao jogador ";
                    str+= std::to_string(time);
                    str+= " :";
                    str+= std::to_string(redPlayer->pontuacao());
                    return str;
                }else if(time == 2){
                    std::string str="Pontuacao jogador ";
                    str+= std::to_string(time);
                    str+= " :";
                    str+= std::to_string(bluePlayer->pontuacao());
                    return str;
                }
                return " ";
            };
            //Retorna a pontuação do jogador
            int pontuacaoInt(unsigned time){
                if(time==1){
                    return int(redPlayer->pontuacao());
                }else if(time==2){
                    return int(bluePlayer->pontuacao());
                }
                return 99;
            }
            //Seta a pontuação do jogador
            void increase(unsigned time){
                if(time==1){
                    (redPlayer->increase());
                }else if(time==2){
                    (bluePlayer->increase());
                }
            }
    };
}
#endif