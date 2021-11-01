<h1>Jogo de Damas
<h2>Objetivo

O objetivo desse trabalho é utilizar os conhecimentos desenvolvidos durante da disciplina de Programação III para criar um jogo de Damas.

<h2>Regras

* O primeiro a jogar é o time vermelho.
* As peças podem apenas mover-se na sua diagonal, uma casa por vez, não podendo retornar, apenas mover-se adiante.
* Quando a peça atravessar todo o tabuleiro, ela se torna uma Dama.
* A Dama pode andar para frente e para trás, na sua diagonal, podendo andar mais de uma casa por vez.
* Quando for possível comer uma peça, ou seja, quando o próximo espaço é ocupado por uma peça adversária e o seguinte é livre,  a movimentação para tal fim é obrigatória.
* O jogador será avisado da obrigatoriedade pelo círculo no canto inferior direito da interface, que ficará totalmente verde.
* Se duas peças puderem comer a mesma peça, a peça que inicialmente estava mais próxima ao canto superior  esquerdo  do tabuleiro tem a preferência.
*  Se duas peças do mesmo time puderem comer outras duas peças ao mesmo tempo, a peça que estava mais próxima ao canto superior  esquerdo do tabuleiro tem a preferência.
* Após comer uma peça, o time ganha mais  uma movimentação.

<h2>Pré Requisitos

1. g++ 9.3.0
2. GNU Make 4.2.1
3. C++ 17
4. libsfml-dev  2.5.1+dfsg-1build1 (SFML)

<h2>Instalação e execução

Ubuntu 20.04.2 LTS:
$ sudo apt-get install  libsfml-dev --fix-missing
$ cd Vfinal (pasta do projeto)
$ make

