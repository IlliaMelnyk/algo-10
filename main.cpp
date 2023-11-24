#include <iostream>
#include <fstream>
using namespace std;
struct Zak{
    string jmeno;
    string prijmeni;
    string trida;
    char pohlavi;
    float prumer;
    Zak* dalsi;
};

void nactiZaka(Zak &z){
    cout<< "jmeno: ";
    cin>>z.jmeno;
    cout<< "prijmeni: ";
    cin>>z.prijmeni;
    cout<< "trida: ";
    cin>>z.trida;
    cout<< "pohlavi (m/z): ";
    cin>>z.pohlavi;
    while(z.pohlavi !='m' and z.pohlavi !='z'){
        cout<< "pohlavi (m/z): ";
        cin>>z.pohlavi;
    }
    cout<< "prumer: ";
    cin>>z.prumer;
    z.dalsi=NULL;
}
/*VypiĹˇ ĹľĂˇka*/
void vypisZaka(Zak &z){
    cout<< "jmeno: "<<z.jmeno<<endl;
    cout<< "prijmeni: "<<z.prijmeni<<endl;
    cout<< "trida: "<<z.trida<<endl;
    cout<< "pohlavi (m/z): "<<z.pohlavi<<endl;
    cout<< "prumer: "<<z.prumer<<endl;
}

void pridejNaZacatek(Zak* &z, Zak* novy){
    novy->dalsi = z;
    z = novy;
}

void nactiNaZacatek(Zak* &z){
    Zak* pom;
    pom = new Zak;
    nactiZaka(*pom);
    pridejNaZacatek(z,pom);
}

void pridejNaKonec(Zak* &z, Zak* novy){
    if (z == nullptr){
        z = novy;
    }
    else{
        Zak* pom = z;
        while (pom->dalsi!=nullptr){
            pom=pom->dalsi;
        }
        pom->dalsi = novy;
    }
}

void nactiNaKonec(Zak* &z){
    Zak* pom;
    pom = new Zak;
    nactiZaka(*pom);
    pridejNaKonec(z,pom);
}


void odeberZeZacatku(Zak* &z){
    if(z != nullptr){
        Zak* pom = z;
        z=z->dalsi;
        delete(pom);
    }
}

void odeberZkonce(Zak* &z){
    if(z!=nullptr){
        Zak* pom = z;
        if(z->dalsi==nullptr){
            z = nullptr;
            delete pom;
        }
        else{
            while(pom->dalsi->dalsi!=nullptr){
                pom = pom->dalsi;
            }
            delete pom->dalsi;
            pom->dalsi =nullptr;
        }
    }
}

void vypisTridu(Zak* z){
    cout<<"-------Vypis tirdy-------"<<endl;
    while(z!=nullptr){
        vypisZaka(*z);
        cout<<"--------------------"<<endl;
        z=z->dalsi;
    }
}

int pocetZaku(Zak* z){
    int pocet=0;
    while(z!=nullptr){
        z=z->dalsi;
        pocet++;
    }
    return pocet;
}

void nactiSoubor(Zak* &z, string soubor){
    ifstream vstup(soubor);
    if(vstup.is_open()){
        Zak* pom = new Zak;
        while(vstup>>pom->jmeno>>pom->prijmeni>>pom->trida>>pom->pohlavi>>pom->prumer){
            pridejNaKonec(z,pom);
            pom = new Zak;
        }
        delete pom;
        vstup.close();
    }
}
void zapisDoSouboru(Zak* &z, string soubor) {
    ofstream vystup(soubor);
    if (vystup.is_open()) {
        while (z != nullptr) {
            vystup << z->jmeno << " " << z->prijmeni << " " << z->trida << " " << z->pohlavi << " " << z->prumer
                   << endl;
            z = z->dalsi;
        }
        vystup.close();
    }
}
void odeberSeZacetku(Zak* &z){
    if(z!= nullptr){
        Zak* pom = z;
        z=z->dalsi;
        delete(pom);
    }
}
void odeberVse(Zak* &z){
    while(z!= nullptr){
        odeberSeZacetku(z);
    }
}
void nactiSouborABC(Zak* &z, string soubor){
    ifstream vstup(soubor);
    if(vstup.is_open()){
        Zak* pom = new Zak;
        while(vstup>>pom->jmeno>>pom->prijmeni>>pom->trida>>pom->pohlavi>>pom->prumer){
           pom->dalsi = nullptr;
            if(z == nullptr){
                z=pom;
            }else if(z->prijmeni>pom->prijmeni){
                pridejNaZacatek(z,pom);
            }else if(z->dalsi = nullptr){
                z->dalsi = pom;
            }else{
                Zak* kam=z;
                while(kam->dalsi->prijmeni<pom->prijmeni and kam->dalsi!= nullptr){
                    if(kam->dalsi == nullptr){
                        kam->dalsi=pom;
                    }else{
                        pom->dalsi=kam->dalsi;
                        kam->dalsi=pom;
                    }
                }
            }
            pom = new Zak;
        }
        delete pom;
        vstup.close();
    }
}
int main() {
   // ifstream vstup("zaci.txt");
    Zak* zacek= nullptr;

       // nactiSoubor(zacek,"zaci.txt");
   // nactiNaZacatek(zacek);
        //pocetZaku(zacek);
      // vypisTridu(zacek);
    zapisDoSouboru(zacek,"novy.txt");
    nactiNaZacatek(zacek);
return 0;
}