#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

#define larguraMapa 24
#define alturaMapa 24
#define telaAltura 640
#define telaLargura 480

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
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int main()
{
    double posX = 22, posY = 0;       // posicoes iniciais
    double dirX = -1, dirY = 0;       // vetor inicial de direcao
    double planoX = 0, planoY = 0.66; // Plano da camera

    screen(telaAltura, telaLargura, 0, "Lanca Raios");

    while (!done)
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
                ladoDistY = (posY - mapaY) * ladoDistY;
            }
            else
            {
                passoY = 1;
                ladoDistY = (mapaY + 1 - posY);
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
                    mapaY = +passoX;
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
                }
            }
        }
    }

    return 0;
}