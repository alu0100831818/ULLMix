#include <vector>
#include <iostream>
#include <cmath>


using namespace std;
vector <int> M {200,100,50,20,10,5,2}; // cantidad de elementos igual en S
vector <int> S;

int convert_to(long double a){ //ten mucho cuidado con esto.. escapas una vez , no siempre!!
    long double n=a*10000;
    int b=static_cast <int>(n);
    b/=100;
    return b;
}


int devolver(int & aux){
    int solu=0,h=M.size(),i=0;
    
    while((aux!=0)&&(i<h)){
        if(aux >= M[i]){
            aux= aux-M[i];
            S[i]=S[i]+1;
        }
        else{
            i++;
        }
    }
    if(aux>0){
        solu=1;
    }
    return solu;
}

int main (void){
    S.resize(M.size());
    cout << "Cambio de monedas\n"
    << "Introduzca la cantidad a cambiar: "
    << endl;
    long double cantidad;
    int k=0,aux;
    cin >> cantidad;
    aux=convert_to(cantidad);
    k=devolver(aux);
    if(k==0){
        cout <<"Solucion: "<< "{ ";
        for (int i=0;i<M.size();i++){
            if (S[i]!=0){
                if(M[i]>=100){
                     cout << S[i]<<"x"<< M[i]/100<< "€ ";
                }
                else{
                    cout << S[i]<<"x"<< "0,"<<M[i]<< "¢ ";
                }
                
            }
        }
        cout <<"}"<< endl;
    }
    else{
        cout << "No existe cambio posible..!" << endl;
    }
    
    return 0;
}



