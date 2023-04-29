//
// Created by carlo on 29/04/2023.
//

#ifndef CG2023_ESCENA_H
#define CG2023_ESCENA_H

#include "Objeto.h"
#include "Camara.h"

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

    void escena3() {
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

        //Luciernaga creacion
        int n_luciernagas = 5;
        vector<Objeto*> luciernagas;
        vector<Luz*> luces;

        vec3 colorLuz(1,1,0);
        for(int i = 0; i < n_luciernagas; i++){
            vec3 posLuz((rand() % 10) - 1,(rand() % 30) - 1,0);
            Objeto *p2 = new Esfera(posLuz, 3, colorLuz);
            p2->es_luz = true;
            luciernagas.emplace_back(p2);
            Luz *pLuz = new Luz(posLuz, colorLuz);
            luces.emplace_back(pLuz);
        }




//        vec3 posLuz1(5,30,0);
//        vec3 colorLuz1(1,1,0);
//        p1 = new Esfera(posLuz1, 3, colorLuz1);
//        p1->es_luz = true;
//        objetos.emplace_back(p1);

//        vector<Luz*> luces;
//        Luz luz(vec3(30,30,30), vec3(1,1,1));
//        //luces.emplace_back(&luz);
//        Luz *pLuz = new Luz(posLuz1, colorLuz1);
//        luces.emplace_back(pLuz);

        for (int y = 1, n=1; y < 100; y+=4, n++){
            cam.configurar(3,60,600,800,
                           vec3(1,y,500),
                           vec3(0,0,0),
                           vec3(0,1,0));
            cam.renderizar(objetos, luces, n);
        }
    }

};

#endif //CG2023_ESCENA_H
