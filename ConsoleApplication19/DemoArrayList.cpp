// DemoArrayList.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstring>
#include "Persona.h"
#include "Calificaciones.h"
#include "ArrayList.h"

using namespace std;

ArrayList<CALIFICACIONES*>c;
ArrayList<PERSONA*>p;

bool customSort(char value1, char value2) {
    return value1 < value2;
}

bool customFilter(char value1, char value2) {
    return value1 == value2;
}

bool filtroCurp(PERSONA* p1, PERSONA* p2) {
    return _strcmpi(p1->curp, p2->curp) == 0;
}
bool calificacionPorNombre(CALIFICACIONES* c1, CALIFICACIONES* c2) {
    PERSONA* curp1 = PERSONA::newPersona("", c1->curp, 0, 0);
    ArrayList<PERSONA*> *p1 = p.filter(curp1, filtroCurp);
    delete curp1;
    if (p1 == NULL)
        return false;
    PERSONA* curp2 = PERSONA::newPersona("", c2->curp, 0, 0);
    ArrayList<PERSONA*>* p2 = p.filter(curp2, filtroCurp);
    delete curp2;
    if (p2 == NULL){
        p1->clear();
        delete p1;
        return false;
    }
    bool result = (*p1)[0]->curp[0] < (*p2)[0]->curp[0];
    p1->clear();
    delete p1;
    p2->clear();
    delete p2;
    return result;
}

int main(int argc, char** argv) {
    try {
        p.add(PERSONA::newPersona("Gilberto", "GILB941104HNLRRR04", 20, 65));
        p.add(PERSONA::newPersona("Beatriz", "BEAT941104HNLRRR04", 20, 65));
        p.add(PERSONA::newPersona("Ana", "ANAA941104HNLRRR04", 20, 65));
        c.add(CALIFICACIONES::newCalificaciones("GILB941104HNLRRR04"));
        c.add(CALIFICACIONES::newCalificaciones("BEAT941104HNLRRR04"));
        c.add(CALIFICACIONES::newCalificaciones("ANAA941104HNLRRR04"));
        ArrayList<CALIFICACIONES*>* c1 = c.clone();
        for (int i = 0; i < c.getSize(); i++)
            cout << c[i]->getCurp() << ", ";
        cout << endl;
        c.heapsort(calificacionPorNombre);
        for (int i = 0; i < c.getSize(); i++)
            cout << c[i]->getCurp() << ", ";
        cout << endl;
        c.clear();
        for (int i = 0; i < c1->getSize(); i++)
            cout << (*c1)[i]->getCurp() << ", ";
        cout << endl;
        c1->quicksort(calificacionPorNombre);
        for (int i = 0; i < c1->getSize(); i++)
            cout << (*c1)[i]->getCurp() << ", ";
        cout << endl;
        cout << c1->getSize() << endl;
        c1->clear();
        delete c1;
        ArrayList<PERSONA*>::ArrayListI *org = p.getOrigin();
        ArrayList<char> v;
        char test[] = { 'B', 'D', 'C', 'A', 'E', 'F', 'G', 'H' };
        v.toList(test, 8);
        ArrayList<char>* n = v.filter('A', customFilter);
        if (n != NULL) {
            cout << n->getSize() << endl;
            for (int i = 0; i < n->getSize(); i++)
                cout << "Filter: " << (*n)[i] << endl;
            n->clear();
            delete n;
        } else cout << "NO RESULTS" << endl;
        for (int i = 0; i < v.getSize(); i++)
            cout << v[i] << ", ";
        cout << endl;
        //      v.erase(4);
        v.heapsort(customSort);
        //      v.quicksort(customSort);
        for (int i = 0; i < v.getSize(); i++)
            cout << v[i] << ", ";
        cout << endl;
        v.clear();
    }
    catch (...) {
        cout << "\nError...\n";
    }
    return 0;
}
