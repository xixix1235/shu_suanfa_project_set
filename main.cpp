#include "MySet.h"
using namespace MySet;
int main() {
    try {
        Controleur::GetInstance()->jouer();
    }catch (SetException& e){
        std::cout<<e.getInfo()<<"\n";
    }
    return 0;
}