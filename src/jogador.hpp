#ifndef JOGADOR_HPP
#define jOGADOR_HPP

namespace final{
    
    class jogador{

        unsigned pont; //Atributo que recebe a pontuação

        public:
            jogador(); 
            void increase();
            unsigned pontuacao(){ //Método que acessa a pontuação
                return pont;
            }


    };

    //Construtor que seta a pontuação para zero
    jogador::jogador(): pont{0}{}; 
    
    //Método que aumenta a pontuação do jogador
    void jogador::increase(){ 
        pont++;
    }

}


#endif