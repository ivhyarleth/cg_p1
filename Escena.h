//
// Created by carlo on 29/04/2023.
//

#ifndef CG2023_ESCENA_H
#define CG2023_ESCENA_H

#include "Objeto.h"
#include "Camara.h"
#include <ctime>
class Escena {
public:
    Camara cam;
    void escena1() {
        vector<Objeto*> objetos;
        Objeto *p1;
        p1 = new Esfera(vec3(10,0,0), 8, vec3(0,0,1));
        p1->setConstantes(1, 0);
        p1->ke = 1;
        objetos.emplace_back(p1);
        p1 = new Esfera(vec3(10,0,20), 8, vec3(0.1,0.1,0.1));
        p1->setConstantes(0.8, 0.2);
        p1->ke = 0.9;
        p1->es_transparente = true;
        p1->ior=1.5;
        objetos.emplace_back(p1);
        p1 = new Esfera(vec3(0,10,0), 8, vec3(1,0,0));
        p1->setConstantes(0.6, 0.4, 32);
        p1->ke = 0.8;
        p1->es_transparente = false;
        p1->ior = 1.2;
        objetos.emplace_back(p1);

        p1 = new Plano(vec3(0,1,0), 1, vec3(0.123, 0.456, 0.789));
        p1->setConstantes(0.9, 0.1);
        p1->ke = 0.1;
        objetos.emplace_back(p1);

        p1 = new Cilindro(vec3(-20,0,0), vec3(-10,10,0),5, vec3(0,1,1));
        p1->setConstantes(0.7,0.3,8);
        objetos.emplace_back(p1);


        vector<Luz*> luces;
        Luz luz(vec3(30,30,30), vec3(1,1,1));
        luces.emplace_back(&luz);

        for (int x = 0, n=1; x < 5; x++, n++){
            cam.configurar(3,60,600,800,
                           vec3(x,5,50),
                           vec3(0,0,0),
                           vec3(0,1,0));
            cam.renderizar(objetos, luces, n);
        }
    }

    void escena2() {
        vector<Objeto*> objetos;
        Objeto *p1;
        p1 = new Plano(vec3(0,1,0), 1, vec3(0.123, 0.456, 0.789));
        p1->setConstantes(0.9, 0.1);
        p1->ke = 0.1;
        objetos.emplace_back(p1);

        p1 = new Cilindro(vec3(5,4,0), vec3(5,140,0),50, vec3(0,1,1));
        p1->setConstantes(0.7,0.3,8);
        p1->es_transparente = true;
        p1->ior = 1.3;
        objetos.emplace_back(p1);

        p1 = new Esfera(vec3(5,0,-20), 10, vec3(1,0.1,0.1));
        p1->setConstantes(0.8, 0.2);
        p1->ke = 0.9;
        p1->es_transparente = true;
        p1->ior=1.5;
        objetos.emplace_back(p1);

        vec3 posLuz1(5,30,0);
        vec3 colorLuz1(1,1,0);
        p1 = new Esfera(posLuz1, 3, colorLuz1);
        p1->es_luz = true;
        objetos.emplace_back(p1);

        vector<Luz*> luces;
        Luz luz(vec3(30,30,30), vec3(1,1,1));
        //luces.emplace_back(&luz);
        Luz *pLuz = new Luz(posLuz1, colorLuz1);
        luces.emplace_back(pLuz);

        for (int y = 1, n=1; y < 100; y+=4, n++){
            cam.configurar(3,60,600,800,
                           vec3(1,y,500),
                           vec3(0,0,0),
                           vec3(0,1,0));
            cam.renderizar(objetos, luces, n);
        }
    }

    //movimiento de luciernagas
    vec3 move(vec3& posLuz, Cilindro &cilindro){
        srand(time(NULL));
        float   lim_max_x = cilindro.pa.x + cilindro.ra,
                lim_min_x = cilindro.pa.x - cilindro.ra,
                lim_max_y = cilindro.pb.y,
                lim_min_y = cilindro.pa.y,
                lim_max_z = cilindro.pa.z + cilindro.ra,
                lim_min_z = cilindro.pa.z - cilindro.ra;

        float speedx = -2 + (rand()%3);
        float speedy = -2 + (rand()%4);
        float speedz = -2 + (rand()%3);

        if (posLuz.x >= lim_max_x || posLuz.x <= lim_min_x) {
            speedx *= -1;
        }
        if (posLuz.y >= lim_max_y || posLuz.y <= lim_min_y) {
            speedy *= -1;
        }
        if (posLuz.z >= lim_max_z || posLuz.z <= lim_min_z) {
            speedz *= -1;
        }

        posLuz.x += speedx;
        posLuz.y += speedy;
        posLuz.z += speedz;

        return posLuz;
    };

    void escena3(int n_luciernagas) {
        vector<Objeto*> objetos;
        Objeto *p1;
        Cilindro *cilindro;

        p1 = new Plano(vec3(0,1,0), 1, vec3(0.93, 0.95, 0.93));
        p1->setConstantes(0.9, 0.1);
        p1->ke = 0.1;
        objetos.emplace_back(p1);

        p1 = new Cilindro(vec3(0,1,0), vec3(0,150,0),52, vec3(0,0,0));
        p1->setConstantes(0.7,0.3,8);
        p1->es_transparente = true;
        p1->ior = 1.5;// indice de reflexion del vidrio
        cilindro = dynamic_cast<Cilindro*>(p1);
        objetos.emplace_back(p1);

        p1 = new Cilindro(vec3(0,4,0), vec3(0,140,0),50, vec3(0,0,0));
        p1->setConstantes(0.7,0.3,8);
        p1->es_transparente = true;
        p1->ior = 1.003; // indice de reflexion aire
        objetos.emplace_back(p1);

        //objetos adicionales
        p1 = new Esfera(vec3(90,0,180), 40, vec3(0.59,0.36,0.62)); //morado
        p1->setConstantes(0.8, 0.2);
        p1->ke = 0.6;
        p1->es_transparente = false;
        p1->ior=1.5;
        objetos.emplace_back(p1);

        p1 = new Esfera(vec3(-140,0,-180), 80, vec3(1,0.1,0.1)); //rojo
        p1->setConstantes(0.8, 0.2);
        p1->ke = 0.9;
        p1->es_transparente = false;
        p1->ior=1.5;
        objetos.emplace_back(p1);

        p1 = new Esfera(vec3(-120,0,140), 16, vec3(0.91,0.87,0.69)); //amarillo
        p1->setConstantes(0.8, 0.2);
        p1->ke = 0.5;
        p1->es_transparente = false;
        p1->ior=1.5;
        objetos.emplace_back(p1);


        //Luciernaga creacion
        vector<Luz*> luces;
        vector<vec3> posLuciernagas;
        vec3 colorLuz(1,0.98,0.38);

        for(int i = 0; i < n_luciernagas; i++) {
            vec3 posLuz((rand() % 50),(rand() % 134)+6,(rand()%40)); //posicion de la luciernaga
            posLuciernagas.push_back(posLuz);
        };

        for (int y = 1, n=1; y < 300; y+=2, n++){
            vector<Objeto*> newpos = objetos;
            for (int i = 0; i < n_luciernagas; i++) {
                posLuciernagas[i] = move(posLuciernagas[i], *cilindro);
                Objeto *p2 = new Esfera(posLuciernagas[i], 2, colorLuz);
                p2->es_luz = true;
                newpos.emplace_back(p2);
                Luz *pLuz = new Luz(posLuciernagas[i], colorLuz);
                luces.emplace_back(pLuz);
            }

            cam.configurar(3,60,600,800,
                           vec3(1,y,500),
                           vec3(0,0,0),
                           vec3(0,1,0));
            cam.renderizar(newpos, luces, n);
        }
    }

};

#endif //CG2023_ESCENA_H
