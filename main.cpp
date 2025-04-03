#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

#define larguraMapa 24
#define alturaMapa 24
#define telaLargura 800
#define telaAltura 800

int mapaMundo[larguraMapa][alturaMapa] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int main(int argc, char *argv[])
{
    double posX = 22, posY = 12;      // posicoes iniciais
    double dirX = -1, dirY = 0;       // vetor inicial de direcao
    double planoX = 0, planoY = 0.66; // Plano da camera

    double tempo = 0;      // tempo atual
    double tempoVelho = 0; // tempo do frame anterior

    screen(telaLargura, telaAltura, 0, "Lanca Raios");

    while (!done())
    {
        for (int x = 0; x < w; x++)
        {
            // calcula a posição do raio e a direção dele
            double cameraX = 2 * x / double(w) - 1;
            double raioDirX = dirX + planoX * cameraX;
            double raioDirY = dirY + planoY * cameraX;

            // qual posição do mapa  estamos

            int mapaX = int(posX);
            int mapaY = int(posY);

            // comprimento do raio da posição atual até o próxima lado ( fronteira ) em X ou Y

            double ladoDistX;
            double ladoDistY;

            // distancia necessária para o raio atravessar um ladrilho,

            double deltaDistX = (raioDirX == 0) ? 1e30 : std::abs(1 / raioDirX);
            double deltaDistY = (raioDirY == 0) ? 1e30 : std::abs(1 / raioDirY);
            double perpPardeDist;

            // escolhe a direção a ser seguida
            int passoX;
            int passoY;

            // Teve colisão? foi vertical ou horizontal

            int acerto = 0;
            int lado;

            if (raioDirX < 0)
            {
                passoX = -1;
                ladoDistX = (posX - mapaX) * deltaDistX;
            }
            else
            {
                passoX = 1;
                ladoDistX = (mapaX + 1 - posX) * deltaDistX;
            }

            if (raioDirY < 0)
            {
                passoY = -1;
                ladoDistY = (posY - mapaY) * deltaDistY;
            }
            else
            {
                passoY = 1;
                ladoDistY = (mapaY + 1 - posY) * deltaDistY;
            }

            // Inicia o DDA

            while (acerto == 0)
            {
                // pula par o próximo quadrado, sendo sempre a menor distância
                // pelo que entendi o caminho parece ser um zigue zague mas no final fica igual a uma linha reta

                if (ladoDistX < ladoDistY)
                {
                    ladoDistX += deltaDistX;
                    mapaX += passoX;
                    lado = 0;
                }
                else
                {
                    ladoDistY += deltaDistY;
                    mapaY += passoY;
                    lado = 1;
                }

                if (mapaMundo[mapaX][mapaY] > 0)
                {

                    // para calcular a altura da parede, não é usado as distancias reais do ponto até a parede, pois iria ficar com efeito de olho de peixe
                    // imagine que temos uma parde reta, se usarmos a distância real, haverá distancias diferentes entre o jogador e as paredes, distorcendo a rendereização
                    // portanto usamos a distancia do plano camera até a parede acertada

                    acerto = 1;
                    if (lado == 0)
                        perpPardeDist = (ladoDistX - deltaDistX);
                    else
                        perpPardeDist = (ladoDistY - deltaDistY);

                    // inicio renderização

                    int alturaLinha = int(h / perpPardeDist);

                    // calcula o pixel mais baixo para desenhar
                    int inicioDesenha = -alturaLinha / 2 + h / 2;
                    if (inicioDesenha < 0)
                        inicioDesenha = 0;
                    // calcula o pixel mais baixo para desenhar
                    int fimDesenha = alturaLinha / 2 + h / 2;
                    if (fimDesenha >= h)
                        fimDesenha = h - 1;

                    // Pinta as paredes

                    ColorRGB cor;
                    switch (mapaMundo[mapaX][mapaY])
                    {
                    case 1:
                        cor = RGB_Red;
                        break;

                    case 2:
                        cor = RGB_Green;
                        break;

                    case 3:
                        cor = RGB_Blue;
                        break;

                    case 4:
                        cor = RGB_White;
                        break;

                    default:
                        cor = RGB_Yellow;
                        break;
                    }
                    // da uma cor diferente para os lados
                    if (lado == 1)
                        cor = cor / 2;

                    // desenha os pixels de uma linha vertical

                    verLine(x, inicioDesenha, fimDesenha, cor);
                }
            }
        }
        // temporizador para input e contador de FPS
        tempoVelho = tempo;
        tempo = getTicks();
        double tempoQuadro = (tempo - tempoVelho) / 1000; // quanto tempo demorou em segundos
        print(1.0 / tempoQuadro);                         // contador de FPS
        redraw();
        cls();

        // modificadores de velocidade

        double velocidadeMov = tempoQuadro * 5.0; // velocidade constante independente do processador
        double velocidadeRot = tempoQuadro * 3.0;

        // leitura de inputs do usuário

        readKeys();
        // anda para frente se não houver parede
        if (keyDown(SDLK_UP))
        {
            if (mapaMundo[int(posX + dirX * velocidadeMov)][int(posY)] == false)
                posX += dirX * velocidadeMov;
            if (mapaMundo[int(posX)][int(posY + dirY * velocidadeMov)] == false)
                posY += dirY * velocidadeMov;
        }
        // anda para trás se não houver parede
        if (keyDown(SDLK_DOWN))
        {
            if (mapaMundo[int(posX - dirX * velocidadeMov)][int(posY)] == false)
                posX -= dirX * velocidadeMov;
            if (mapaMundo[int(posX)][int(posY - dirY * velocidadeMov)] == false)
                posY -= dirY * velocidadeMov;
        }
        // Gira a camera para a direita

        if (keyDown(SDLK_RIGHT))
        {
            double velhoDirX = dirX;
            dirX = dirX * cos(-velocidadeRot) - dirY * sin(-velocidadeRot);
            dirY = velhoDirX * sin(-velocidadeRot) + dirY * cos(-velocidadeRot);
            double velhoPlanoX = planoX;
            planoX = planoX * cos(-velocidadeRot) - planoY * sin(-velocidadeRot);
            planoY = velhoPlanoX * sin(-velocidadeRot) + planoY * cos(-velocidadeRot);
        }

        // girar para a camera esquerda

        if (keyDown(SDLK_LEFT))
        {
            double velhoDirX = dirX;
            dirX = dirX * cos(velocidadeRot) - dirY * sin(velocidadeRot);
            dirY = velhoDirX * sin(velocidadeRot) + dirY * cos(velocidadeRot);
            double velhoPlanoX = planoX;
            planoX = planoX * cos(velocidadeRot) - planoY * sin(velocidadeRot);
            planoY = velhoPlanoX * sin(velocidadeRot) + planoY * cos(velocidadeRot);
        }
    }

    return 0;
}