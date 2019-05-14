//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <typeinfo>   //Pour savoir à quelle classe appartient un objet

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

int a;

class bob {};

bob b;

string c;

//Test: retourner la classe d'un objet:            //Ok, la fonction est weird. Je ne sais pas comment elle fait.
int main() {
	cout << "\n\n" << typeid(a).name();
	cout << "\n\n" << typeid(b).name();	
	cout << "\n\n" << typeid(c).name();	
}

