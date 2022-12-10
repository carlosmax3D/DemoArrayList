#include <iostream>
#include <string>
#include <cstring>
#pragma once

using namespace std;

struct CALIFICACIONES {
    float calificaciones[10] = { 0 };
    char curp[255] = { '\0' };
    void setCurp(string c) {
        strcpy_s(curp, 255, c.c_str());
    }
    string getCurp() {
        string s(curp);
        return s;
    }
    static CALIFICACIONES* newCalificaciones(string curp) {
        CALIFICACIONES* nuevo = new CALIFICACIONES;
        if (nuevo == NULL)
            return NULL;
        nuevo->setCurp(curp);
        return nuevo;
    }
};