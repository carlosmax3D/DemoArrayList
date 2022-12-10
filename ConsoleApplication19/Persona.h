#include <iostream>
#include <string>
#include <cstring>
#pragma once

using namespace std;

struct PERSONA {
    char nombre[255] = { '\0' };
    char curp[255] = { '\0' };
    int edad = 0;
    float peso = 0;
    string getNombre() {
        string s(nombre);
        return s;
    }
    void setNombre(string n) {
        strcpy_s(nombre, 255, n.c_str());
    }
    string getCurp() {
        string s(curp);
        return s;
    }
    void setCurp(string c) {
        strcpy_s(curp, 255, c.c_str());
    }
    static PERSONA* newPersona(string nombre, string curp, int edad, int peso) {
        PERSONA* nuevo = new PERSONA;
        if (nuevo == NULL)
            return NULL;
        nuevo->setCurp(curp);
        nuevo->setNombre(nombre);
        nuevo->edad = edad;
        nuevo->peso = peso;
        return nuevo;
    }
};