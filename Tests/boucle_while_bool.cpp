//Test de boucle while
#include <iostream>
using namespace std;


bool test [5] {true,true,true,false,true};
int pos = 0;

int main(void) {
	while(test[pos++]) if(pos==5) cout << "Ca n'a pas marche";

cout << "\nOu ca a marche";
}

