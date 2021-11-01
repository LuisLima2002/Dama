#ifndef PECA_HPP
#define PECA_HPP
namespace final{
    class peca{
        unsigned time; //Atributo que determina o time do jogador, o vermelho é representado pelo 1 e o azul, pelo 2
        bool dama; //Atributo que indica se a peça é uma dama. Se dama for True, a peça é uma dama.
        unsigned coord[2]; // Atributo que recebe as coordenadas x (linha) e y (coluna) da peça no tabuleiro 
        public:
        //Construtor
        peca(unsigned i=0,unsigned x=0,unsigned y=0);
        //Retorna coordenadas da peça
        unsigned X() const{
            return coord[0]; 
        }
        unsigned Y() const{
            return coord[1];
        }
        //Seta coordenadas da peça
        void X(unsigned x){
            coord[0] = x; //coordenada x é armazenada na posição 0 do vetor
        }
        void Y(unsigned y){
            coord[1] = y; //coordenada y é armazenada na posição 1 do vetor
        }
        //Retorna se peça é dama
        bool Dama(){
            return dama;
        }
        //Seta o atributo dama. É utilizado q  uando a peça se torna dama
        void Dama(bool b){
            dama = b;
        }

    };
    //Construtor
    peca::peca(unsigned i,unsigned x,unsigned y){ 
        time=i; //Atributo time recebe 0 por padrão
        dama=false; //Atributo dama é setado para falso, fazendo com que todas as peças não sejam damas no começo do jogo
        coord[0]=x; //Atributo coord na posição 0 recebe 0 por padrão
        coord[1]=y; //Atributo coord na posição 1 recebe 0 por padrão
    }

}
#endif