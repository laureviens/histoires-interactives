//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round() et abs()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#include <fcntl.h>    //Librairie comprenant la magie permettant d'afficher les unicodes dans la console 
//#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent (??? Optionnel?)
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
#include <windef.h>            //Nécessaire pour savoir la position du curseur sur Windows
#include <winuser.h>		   //Nécessaire pour savoir la position du curseur sur Windows
#include <conio.h>             //Nécessaire pour enregistrer les inputs du clavier
#include <io.h>				   //Nécessaire pour changer l'encodage-out pour l'unicode
#include <fcntl.h>			   //Nécessaire pour décrypter les accents en unicode
#include <stdlib.h>     	   //Nécessaire pour jouer avec des nombres aléatoires  /* srand, rand */



using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)




	//xi Fonction : strintervalle ; retourne un string
	string strintervalle(string str, int deb, int fin) {
		string nwstr;
		for(int pos=deb;pos<=fin;pos++) nwstr+=str[pos];          
		return(nwstr);
	}
	
	
	//Main:
	int main(void){
		
		string objet = "Blaireau|Canard";
		int pos = 0; bool found = false;
		while(!found){
			if(objet[pos]=='|') found = true;
			pos++;
		}
		cout << strintervalle(objet,0,pos) << '\n' << strintervalle(objet,0,pos-2); 
		
	}				//La morale de cette histoire: Faut checker comme faut si:
								//a) On update "pos" APRÈS avoir commencé la boucle
								//b) "pos" représente bien la dernière lettre du string que l'on veut obtenir
	
