#ifndef WINDOWN_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "jogo.hpp"
#include "manager.hpp"
#include <string>

namespace final{

    //classe da interface gráfica que é um jogo devido a herança
    class window:private jogo{ 
        //atributos da interface gráfica
        sf::RenderWindow* janela;
        //Sprint e Texture Tabuleiro
        sf::Texture* tBoard;
        sf::Sprite* sBoard;
        //Sprint e Texture Peças
        sf::Texture* tDoot;
        sf::Sprite* redDoot;
        sf::Sprite* blueDoot;
        //Sprint e Texture Luzes indicadoras de captura
        sf::Texture* tOn;
        sf::Sprite* sOn;
        sf::Texture* tOff;
        sf::Sprite* sOff;
        //Fonte
        sf::Font* font;
        //Texto da pontuação
        sf::Text* ponts;
        //Ponteiro do tipo manager
        final::manager* gerente;
        //Remove a peça do tabuleiro da interface gráfica
        void removeDoot(unsigned time,int index){
            if(time==1){
                redDoot[index].setPosition(-100,-100);
                gerente->increase(2); //Aumenta a pontuação do time 1
            }else if(time==2){
                blueDoot[index].setPosition(-100,-100);
                gerente->increase(1); //Aumenta a pontuação do time 2
            }
        }
        //Altera a textura da peça para mostrar que é uma dama
        void DamaSprite(unsigned time,sf::Sprite* doot){
            if(time==1){
                doot->setTextureRect(sf::IntRect(0,57,57,58));
            }else{
                doot->setTextureRect(sf::IntRect(57,57,57,58));
            }
        }
        public:
        window();
        ~window();
        void start();
    };
    //Construtor
    window::window(){
        janela = new sf::RenderWindow(sf::VideoMode(454, 555), "Dama",sf::Style::Titlebar);
        janela->hasFocus();
        //Carrega textura do tabuleiro e cria sprite
        tBoard = new sf::Texture;
        tBoard->loadFromFile("figures/board0.png");
        sBoard = new sf::Sprite;
        sBoard->setTexture(*tBoard);
        //Carrega textura das peças/Doots
        tDoot= new sf::Texture;
        tDoot->loadFromFile("figures/figures.png");

        //Sprite Times
        redDoot = new sf::Sprite[12];
        blueDoot = new sf::Sprite[12];
        //Manager
        gerente = new final::manager;

        //Cria sprites de cada peça
        for (unsigned i = 0; i < 12; i++)
        {
            redDoot[i].setTexture(*tDoot);
            redDoot[i].setTextureRect(sf::IntRect(0,0,57,58));
            redDoot[i].setPosition(float(56*Y(1,i)),float(56.875*X(1,i)));
            blueDoot[i].setTexture(*tDoot);
            blueDoot[i].setTextureRect(sf::IntRect(57,0,57,58));
            blueDoot[i].setPosition(float(56*Y(2,i)),float(56.875*X(2,i)));
        }

        //Carrega Fonte
        font = new sf::Font;
        font->loadFromFile("./fonts/Hamberger-Bold.ttf");
        //Texto da pontuação
        ponts = new sf::Text[2];
        for (int i = 0; i < 2; i++)
        {
            ponts[i].setFont(*font);
            ponts[i].setPosition(float(0),float(455+50*i));
            ponts[i].setFillColor(sf::Color::Black);
        }
        //Botões indicadores de captura
        tOn = new sf::Texture;
        tOff = new sf::Texture;
        sOn= new sf::Sprite;
        sOff= new sf::Sprite;
        tOn->loadFromFile("figures/buttonon.png"); 
        tOff->loadFromFile("figures/buttonoff.png"); 
        sOn->setTexture(*tOn);
        sOff->setTexture(*tOff);
        sOn->setPosition(float(340),float(465));
        sOff->setPosition(float(340),float(465));
    }
    //Destrutor
    window::~window(){
        delete janela;
        delete tBoard;
        delete sBoard;
        delete tDoot;
        delete font;
        delete[] ponts;
        delete[] redDoot;
        delete[] blueDoot;
        delete tOn;
        delete tOff;
        delete sOn;
        delete sOff;
        delete gerente;
    }
    void window::start(){
        int moving[2] = {-1,-1}; //Vetor que guarda, na posição 0, o time que está se movendo e na 1, o index da peça
        unsigned previousx=0; //Coordenada x antes da movimentação
        unsigned previousy=0; //Coordenada y antes da movimentação
        unsigned rodada=1; //Indica a vez do time. 1 indica vez do time vermelho e 2, do azul
        int indiceCapturado=-1; //Indice da peça que pode ser capturada
        
        while (janela->isOpen())
            {

                //Eventos
                sf::Event e;
                while (janela->pollEvent(e))
                {
                    if (e.type == sf::Event::Closed)
                        janela->close();
                        
                }
                janela->clear(sf::Color(255, 255, 255));
                //checa se algum dos times ganhou
                if(gerente->pontuacaoInt(2)==12){
                    sf::Text texto("Jogador azul ganhou", *font);
                    texto.setFillColor(sf::Color::Black);
                    janela->draw(texto);
                    janela->display();                    
                    continue;
                }else if(gerente->pontuacaoInt(1)==12){
                    sf::Text texto("Jogador vermelho ganhou", *font);
                    texto.setFillColor(sf::Color::Black);
                    janela->draw(texto);
                    janela->display();
                    continue;
                }
                

                //Inputs
                sf::Vector2i posMouse= sf::Mouse::getPosition(*janela);

                //Drag and Drop
                //Possibilita que o usuário arraste a peça até a posição desejada
                float dx=0;
                float dy=0;
                //coordenadas da peça que deve ser capturada
                int xCaptura=0;
                int yCaptura=0;
                bool capturar = false;
                unsigned pecaCaptura=0;

                //Verificando se pode comer a peça
                janela->draw(*sOff);
                for (int i = 0; i < 12; i++)
                {
                        //Vez do vermelho
                        if(rodada==1){
                            auto x = X(unsigned(1),unsigned(i)); //recebe a coordenada x da peça
                            auto y = Y(unsigned(1),unsigned(i)); //recebe a coordenada y da peça
                            for (int k = -1; k < 2; k+=2)
                            {
                                if(capturar) break;//break se a captura for possível
                                if((x+2)>7|| int(y)+k*2<0 ||int(y)+k*2>7) continue; //Restrições para não acessar vetor em index inapropriado
                                if(consultaMatriz(int(x)+1,int(y)+k)==2 && consultaMatriz(int(x)+2,int(y)+k*2)==0){ //É possível capturar
                                    capturar=true; //Indica que a captura é possível e obrigatória
                                    janela->draw(*sOn); 
                                    pecaCaptura=unsigned(i); //Indica qual peça realizará a captura
                                    xCaptura=int(x)+2; //Coordenada x da peça após a captura
                                    yCaptura= int(y)+(k*2); //Coordenada y da peça após a captura
                                    indiceCapturado= at(int(x)+1,int(y)+k); //Recebe o indice da peça que foi capturada
                                }     
                            }
                            if(Dama(1,i)){
                                for (int k = -1; k < 2; k+=2)
                                {
                                    for(int h=-1; h<2;h+=2){
                                        for (int m = 1; m < 7; m++) //percorre o tabuleiro de uma diagonal a outra
                                        {   
                                            if(capturar) break;//break se a captura for possível
                                            if(int(x)+(k*m)+k>7 || int(x)+(k*m)+k<0|| int(y)+(h*m)+h<0 ||int(y)+(h*m)+h>7) continue;//Restrições para não acessar vetor em index inapropriado
                                            if(consultaMatriz(int(x)+(k*m),int(y)+(h*m))==2 && consultaMatriz(int(x)+(k*m)+k,int(y)+(h*m)+h)==0){ //é possível capturar
                                                capturar=true; //indica que a captura é possível e obrigatória
                                                janela->draw(*sOn);
                                                pecaCaptura=unsigned(i);  //indica qual peça realizará a captura
                                                xCaptura=int(x)+(k*m)+k; //Coordenada x da peça após a captura
                                                yCaptura= int(y)+(h*m)+h; //Coordenada y da peça após a captura
                                                indiceCapturado= at(int(x)+(k*m),int(y)+(h*m)); //Recebe o indice da peça que foi capturada
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        //Vez do azul
                        else if(rodada==2){
                            auto x = X(unsigned(2),unsigned(i)); //recebe a coordenada x da peça
                            auto y = Y(unsigned(2),unsigned(i)); //recebe a coordenada y da peça
                            for (int k = -1; k < 2; k+=2)
                            {
                                if(capturar) break;//break se a captura for possível
                                int t = int(x)-2;
                                if(t<0||(( int(y)+k*2)<0) ||((int(y)+k*2)>7)) continue;//Restrições para não acessar vetor em index inapropriado
                                if(consultaMatriz(int(x)-1,int(y)+k)==1 && consultaMatriz(int(x)-2,int(y)+k*2)==0){ //é possível capturar
                                    capturar=true; //indica que a captura é possível e obrigatória
                                    janela->draw(*sOn);
                                    pecaCaptura=unsigned(i); //indica qual peça realizará a captura
                                    xCaptura=int(int(x)-2); //Coordenada x da peça após a captura
                                    yCaptura= int(y)+(k*2); //Coordenada y da peça após a captura
                                    indiceCapturado= at((int(x)-1),(int(y)+k)); //Recebe o indice da peça que foi capturada
                                }    
                            }
                            if(Dama(2,i)){
                                for (int k = -1; k < 2; k+=2)
                                {
                                
                                    for(int h=-1; h<2;h+=2){
                                        for (int m = 1; m < 7; m++) //percorre o tabuleiro de uma diagonal a outra
                                        {   
                                            if(capturar) break;//break se a captura for possível
                                            if(int(x)+(k*m)+k>7 || int(x)+(k*m)+k<0|| int(y)+(h*m)+h<0 ||int(y)+(h*m)+h>7) continue;//Restrições para não acessar vetor em index inapropriado
                                            if(consultaMatriz(int(x)+(k*m),int(y)+(h*m))==1 && consultaMatriz(int(x)+(k*m)+k,int(y)+(h*m)+h)==0){
                                                capturar=true; //indica que a captura é possível e obrigatória
                                                janela->draw(*sOn);
                                                pecaCaptura=unsigned(i); //indica qual peça realizará a captura
                                                xCaptura=int(x)+(k*m)+k; //Coordenada x da peça após a captura
                                                yCaptura= int(y)+(h*m)+h; //Coordenada y da peça após a captura
                                                indiceCapturado= at(int(x)+(k*m),int(y)+(h*m)); //Recebe o indice da peça que foi capturada
                                            }
                                        }
                                        
                                    }
                                }
                            }
                        }
                }
                
                if(e.type== sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && moving[0]==-1){
                    for (int i = 0; i < 12; i++)
                    {
                       
                        if(redDoot[i].getGlobalBounds().contains(float(posMouse.x),float(posMouse.y))){
                            //Variação relativa da posiçãoo da peça. Possibilita que a peça seja arrastada até sua nova posição
                            dx=float(posMouse.x)- redDoot[moving[1]].getPosition().x;
                            dy=float(posMouse.y)- redDoot[moving[1]].getPosition().y;
                            moving[0]=1;
                            moving[1]=i;
                            //Recebe a posição da peça vermelha que foi selecionada para se mover
                            previousx= X(unsigned(1),unsigned(moving[1])); 
                            previousy= Y(unsigned(1),unsigned(moving[1]));
                        }
                        if(blueDoot[i].getGlobalBounds().contains(float(posMouse.x),float(posMouse.y))){
                            moving[0]=2;
                            moving[1]=i;
                            //Recebe a posição da peça azul que foi selecionada para se mover
                            previousx= X(unsigned(2),unsigned(moving[1]));
                            previousy= Y(unsigned(2),unsigned(moving[1]));;  
                        }
                    }
                    
                }
                //Checa se a posição é valida para fazer o movimento
                if(e.type==sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left ){
                    //Movimentação do vermelho
                    if(moving[0]==1){
                        //Coordenadas da peça após a movimentação
                        //Conversão das coordenadas na interface gráfica para a posição utilizada no código (entre 0 e 7)
                        auto x = int(float(redDoot[moving[1]].getPosition().x+25)/float(56.75)); 
                        auto y = int(float(redDoot[moving[1]].getPosition().y+25)/float(56.875));
                        
                        //Impede que duas peças são colocadas no mesmo lugar, erros de segmentção e movimentações fora da diagonal
                        //Testa se a posição desejada é vazia e está na diagonal, delimita os intervalos de x e y, testa se é a vez do jogador 1, se a captura não é possível e se a peça não é uma dama
                        if(consultaMatriz(y,x)==0 && x>=0 && x<8 && y<8 && y>=0 && abs(x-int(previousy))==1 && y-int(previousx)==1 && rodada==1 && !capturar && !Dama(1,moving[1])){
                            redDoot[moving[1]].setPosition(float(56*x),float(56.875*y)); //Muda a posição da peça na interface gráfica
                            mudaMatriz(y,x,1); //Altera a matriz na posição onde chega a peça para indicar que a posição está ocupada
                            mudaMatriz(int(X(1,unsigned(moving[1]))),int(Y(1,unsigned(moving[1]))),0); //Altera a matriz na posição de onde sai a peça para indicar que agora ela é vazia
                            X(1,unsigned(moving[1]),unsigned(y));//Altera a coordenada x da peça para sua nova posição
                            Y(1,unsigned(moving[1]),unsigned(x));//Altera a coordenada y da peça para sua nova posição
                            //Peça se transforma em Dama
                            if(y==7){
                                Dama(1,moving[1],true);
                                DamaSprite(1,&redDoot[moving[1]]);

                            }
                            rodada=2; //Passa a vez para o próximo time
                        }
                        //Movimentação caso a peça seja uma Dama
                        //Possibilita andar mais de uma posição na diagonal
                        else if(consultaMatriz(y,x)==0 && x>=0&& x<8 && y<8 && y>=0 && rodada==1 &&  abs(x-int(previousy))== abs(y-int(previousx)) && !capturar && Dama(1,moving[1])){
                            redDoot[moving[1]].setPosition(float(56*x),float(56.875*y)); //Muda a posição da peça na interface gráfica
                            mudaMatriz(y,x,1); //Altera a matriz na posição onde chega a peça para indicar que a posição está ocupada
                            mudaMatriz(int(X(1,unsigned(moving[1]))),int(Y(1,unsigned(moving[1]))),0); //Altera a matriz na posição de onde sai a peça para indicar que agora ela é vazia
                            X(1,unsigned(moving[1]),unsigned(y)); //Altera a coordenada x da peça para sua nova posição
                            Y(1,unsigned(moving[1]),unsigned(x)); //Altera a coordenada y da peça para sua nova posição
                            rodada=2; //Passa a vez para o próximo time
                        }

                        //Movimentação com captura
                        //Checa se a captura é possível e se está sendo feita de forma correta
                        else if(capturar && xCaptura==y && yCaptura==x && moving[1]==int(pecaCaptura)){
                            redDoot[moving[1]].setPosition(float(56*x),float(56.875*y)); //Muda a posição da peça na interface gráfica
                            mudaMatriz(y,x,1); //Altera a matriz na posição onde chega a peça para indicar que a posição está ocupada
                            mudaMatriz(int(X(1,unsigned(moving[1]))),int(Y(1,unsigned(moving[1]))),0); //Altera a matriz na posição de onde sai a peça para indicar que agora ela é vazia
                            X(1,unsigned(moving[1]),unsigned(y)); //Altera a coordenada x da peça para sua nova posição
                            Y(1,unsigned(moving[1]),unsigned(x)); //Altera a coordenada y da peça para sua nova posição
                            removeDoot(2,indiceCapturado); //Remove a peça capturada do tabuleiro na interface gráfica
                            mudaMatriz(int(X(2,unsigned(indiceCapturado))),int(Y(2,unsigned(indiceCapturado))),0); //Altera a matriz na posição da peça capturada para indicar que a posição está vazia
                            X(2,unsigned(indiceCapturado),99); //Altera a coordenada x da peça capturada para uma posição fora do tabuleiro
                            Y(2,unsigned(indiceCapturado),99); //Altera a coordenada y da peça capturada para uma posição fora do tabuleiro
                            //Peça se transforma em Dama
                            if(y==7){
                                Dama(1,moving[1],true);
                                DamaSprite(1,&redDoot[moving[1]]);
                            }
                        //Movimentação indevida volta a peça para sua posição atual
                        }else{
                            redDoot[moving[1]].setPosition(float(56*previousy),float(56.875*previousx));

                        }
                    }

                    //Movimentação do azul
                    if(moving[0]==2){
                        //Coordenadas da peça após a movimentação
                        //Conversão das coordenadas na interface gráfica para a posição utilizada no código (entre 0 e 7)
                        auto x = int(float(blueDoot[moving[1]].getPosition().x+25)/float(56.75));
                        auto y = int(float(blueDoot[moving[1]].getPosition().y+25)/float(56.875));
                        
                        //Impede que duas peças são colocadas no mesmo lugar, erros de segmentção e movimentações fora da diagonal
                        //Testa se a posição desejada é vazia e está na diagonal, delimita os intervalos de x e y, testa se é a vez do jogador 2, se a captura não é possível e se a peça não é uma dama
                        if(consultaMatriz(y,x)==0 && x>=0&& x<8 && y<8 && y>=0 && abs(x-int(previousy))==1 && y-int(previousx)==-1 && rodada==2 && !capturar && !Dama(2,moving[1])){
                            blueDoot[moving[1]].setPosition(float(56*x),float(56.875*y)); //Muda a posição da peça na interface gráfica
                            mudaMatriz(y,x,2); //Altera a matriz na posição onde chega a peça para indicar que a posição está ocupada
                            mudaMatriz(int(X(2,unsigned(moving[1]))),int(Y(2,unsigned(moving[1]))),0); //Altera a matriz na posição de onde sai a peça para indicar que agora ela é vazia
                            X(2,unsigned(moving[1]),unsigned(y)); //Altera a coordenada x da peça para sua nova posição
                            Y(2,unsigned(moving[1]),unsigned(x)); //Altera a coordenada y da peça para sua nova posição
                            //Peça se transforma em Dama
                            if(y==0){
                                Dama(2,moving[1],true);
                                DamaSprite(2,&blueDoot[moving[1]]);
                            }
                            rodada=1; //Passa a vez para o time vermelho
                        }

                        //Movimentação caso a peça seja uma Dama
                        //Possibilita andar mais de uma posição na diagonal
                        else if(consultaMatriz(y,x)==0 && x>=0&& x<8 && y<8 && y>=0 &&  abs(x-int(previousy))== abs(y-int(previousx))  && rodada==2 && !capturar && Dama(2,moving[1])){
                            blueDoot[moving[1]].setPosition(float(56*x),float(56.875*y)); //Muda a posição da peça na interface gráfica
                            mudaMatriz(y,x,2); //Altera a matriz na posição onde chega a peça para indicar que a posição está ocupada
                            mudaMatriz(int(X(2,unsigned(moving[1]))),int(Y(2,unsigned(moving[1]))),0); //Altera a matriz na posição de onde sai a peça para indicar que agora ela é vazia
                            X(2,unsigned(moving[1]),unsigned(y)); //Altera a coordenada x da peça para sua nova posição
                            Y(2,unsigned(moving[1]),unsigned(x));  //Altera a coordenada y da peça para sua nova posição
                            rodada=1; //Passa a vez para o time vermelho
                        }
                        
                        //Movimentação com captura
                        //Checa se a captura é possível e se está sendo feita de forma correta
                        else if(capturar && xCaptura==y && yCaptura==x && moving[1]==int(pecaCaptura)){
                            blueDoot[moving[1]].setPosition(float(56*x),float(56.875*y)); //Muda a posição da peça na interface gráfica
                            mudaMatriz(y,x,2); //Altera a matriz na posição onde chega a peça para indicar que a posição está ocupada
                            mudaMatriz(int(X(2,unsigned(moving[1]))),int(Y(2,unsigned(moving[1]))),0); //Altera a matriz na posição de onde sai a peça para indicar que agora ela é vazia
                            X(2,unsigned(moving[1]),unsigned(y)); //Altera a coordenada x da peça para sua nova posição
                            Y(2,unsigned(moving[1]),unsigned(x)); //Altera a coordenada y da peça para sua nova posição
                            removeDoot(1,indiceCapturado); //Remove a peça capturada do tabuleiro na interface gráfica
                            mudaMatriz(int(X(1,unsigned(indiceCapturado))),int(Y(1,unsigned(indiceCapturado))),0); //Altera a matriz na posição da peça capturada para indicar que a posição está vazia
                            X(1,unsigned(indiceCapturado),99); //Altera a coordenada x da peça capturada para uma posição fora do tabuleiro
                            Y(1,unsigned(indiceCapturado),99); //Altera a coordenada y da peça capturada para uma posição fora do tabuleiro
                            //Peça se transforma em Dama
                            if(y==0){
                                Dama(2,moving[1],true);
                                DamaSprite(2,&blueDoot[moving[1]]);
                            }
                        }
                        //Movimentação indevida volta a peça para sua posição atual
                        else{
                             blueDoot[moving[1]].setPosition(float(56*previousy),float(56.875*previousx));
                        }
                    }
                    moving[0] = -1;

                }

                //Permite que apenas as peças do time da rodada sejam arrastadas
                if(moving[0]!=-1){
                    if(moving[0]==1 && rodada==1){
                        redDoot[moving[1]].setPosition(float(posMouse.x)-dx-28,float(posMouse.y)-dy-float(28));
                    }else if (moving[0]==2 && rodada==2){
                        blueDoot[moving[1]].setPosition(float(posMouse.x)-dx-28,float(posMouse.y)-dy-float(28));
                    }
                }
                //Interface gráfica - Draw
                janela->draw(*sBoard);
                for (int i = 0; i < 12; i++)
                {
                    janela->draw(redDoot[i]);
                    janela->draw(blueDoot[i]);
                }
                for (int i = 0; i < 2; i++)
                {
                    ponts[i].setString(gerente->pontuacao(unsigned(i+1)));
                    janela->draw(ponts[i]);
                }
                janela->display();
            }
        //Após encerramento do jogo o tabuleiro e as pontuações são mostrados no terminal
        mostraJogo();
        std::cout<<gerente->pontuacao(1)<< "\n";
        std::cout<<gerente->pontuacao(2)<< "\n";
    }
}

#endif