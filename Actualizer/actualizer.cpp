#include <windows.h>
#include <iostream>

int main(){
    std::cout << "Aktualizacja w trakcie, zaczekaj...."<<std::endl;
    system("git pull https://github.com/Marcel129/SmallBA_Deployment");
    std::cout << "Aktualizacja zakończona"<<std::endl;
}