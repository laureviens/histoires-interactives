
//Doodles d'objets graphiques:
/*______________________________________________________________________________________________________________________________---
	Herbe: \/  \|/   /    \
	
	Oiseau:   -\~_  -_~_  -/~_  -¯~_  ou   -/~_  -\~_
	
	Chat:                           |
			\_-~­^^    __-~­^^      \-~­^^    ou    \_»»»^^
			  /\/\       /\/\        /\/\
			  
	Nuage:  _        __      __        __     _
	       (_)     	(__)    (__B	  S__)   {_}
			  
	Paysage:
	                             ___                                                              |
	      __                    /   \                              __                             |
	    _/  \     ___          /     \____       _____            /  \___                         |
	   /     \___/   |        /           \     /     \__________/       \                        |
	__/	              \______/             \___/                          \______________________ |      
	                                                                                              |     //94 colonnes de longueur
	     "  " "    \/            .             .     \/        '           ' \/   \/      '       |     //(les lignes horizontales sont exclues
	\/    '  "  '      '    \/         \|/                   "     '          \|/  \/    .  \|/   |
	        \|/' '                                                   \|/         \/               |
	   \/      " '        .     \/          .    \|/          \/              '                   |
*/                                                               


//Code pour générer le jeu:
//_________________________________________________________________________________________________________________________________---

//Définition de l'environnement

#include <iostream>   //Pour les entrées/sorties

#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

//Création des dessins
	
	//Création du paysage
														// Les symboles \ et " sont précédés de \, pour les compter comme des characters
	 string p0 = "                            _                         _____          (__)           ____      ";
	 string p1 = "                           (_)            __         (     )                      _(    )     ";
	 string p2 = "             __                          (__)         (____)                    _(     )      ";
	 string p3 = "            (__)             ___                                               (_______)      ";
	 string p4 = "      __                    /   \\                              __                             ";
	 string p5 = "    _/  \\     ___          /     \\____       _____            /  \\___                         ";
	 string p6 = "   /     \\___/   |        /           \\     /     \\__________/       \\                        ";
	 string p7 = "__/               \\______/             \\___/                          \\______________________ ";
	 string p8 = "                                                                                              ";
	 string p9 = "     \"  \" \"    \\/            .             .     \\/        '           ' \\/   \\/      '       ";
	string p10 = "\\/    '  \"  '      '    \\/         \\|/                   \"     '          \\|/  \\/    .  \\|/   ";
	string p11 = "        \\|/' '                                                   \\|/         \\/               ";
	string p12 = "   \\/      \" '        .     \\/          .    \\|/          \\/              '                   ";

					//13 lignes de hauteur, 
					//94 colonnes de longueur (sans les '\' en surplus)

		//Mise en array du paysage:
		string paysage[13] = {p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12}; 

	//Création du chat:
	string c1a = ""          ;   string c1b = ""          ;   string c1c = "|";           
	string c2a = "__-~­^^"   ;   string c2b = "\\_-~­^^"   ;   string c2c = "\\-~­^^";   
	string c3a =    "\\\\\\\\";  string c3b =    "/\\/\\"   ; string c3c =   "///\\";       //pour une démarche a-b-c-b-a-b-c-b-a... 

		//Mise en array du chat:
		//string c[3][3]; c[1] = {c1a,c1b,c1c} ; c[2] = {c2a,c2b,c2c} ; c[3] = {c3a,c3b,c3c;          //ne marche pas...
		string c1[3] = {c1a,c1b,c1c} ; string c2[3] = {c2a,c2b,c2c} ; string c3[3] = {c3a,c3b,c3c};   //version alternative?


//Définition des paramètres de la console (Windows uniquement)
	
	//Création des objets de console
	HWND consdim = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
	HANDLE constxt = GetStdHandle(STD_OUTPUT_HANDLE);         //Objet permettant de modifier le texte affiché dans la console


//Définition des fonctions utilisées:
	
	//Fonction pour déplacer le curseur sur la console
	COORD CursorPosition;                                     //Objet permettant de se situer sur la console
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(constxt,CursorPosition); 
	}	

	//Fonction pour changer de couleur facilement
	/*                                                   //Version qui ne marche pas, probablement dû à des problème de conversion de int à WORD (code)
	void chgcol(string color) {
		int code;
		if(color=="vert sombre") code = 2;         
			else if(color=="rouge sombre") code = 4;
			else if(color=="brun") code = 6;
			else if(color=="gris") code = 7;
			else if(color=="gris sombre") code = 8;
			else if(color=="vert") code = 10;
			else if(color=="cyan") code = 11;
			else if(color=="rouge") code =12;
			else if(color=="blanc") code =15;
		SetConsoleTextAttribute(constxt, code);}
	*/ 
	void chgcol(string color) {
		int code;
		if(color=="vert sombre") SetConsoleTextAttribute(constxt, 2);         
			else if(color=="rouge sombre") SetConsoleTextAttribute(constxt, 4);   
			else if(color=="brun") SetConsoleTextAttribute(constxt, 6);   
			else if(color=="gris") SetConsoleTextAttribute(constxt, 7);   
			else if(color=="gris sombre") SetConsoleTextAttribute(constxt, 8);   
			else if(color=="vert") SetConsoleTextAttribute(constxt, 10);   
			else if(color=="cyan") SetConsoleTextAttribute(constxt, 11);   
			else if(color=="rouge") SetConsoleTextAttribute(constxt, 12);   
			else if(color=="blanc") SetConsoleTextAttribute(constxt, 15);   
		}
		
	//Fonction pour afficher le paysage                

		//Définir les dimensions de l'image
		int nlin = 13;
		int ncol = 27;

		//Créer les objets de limites horizontales à l'image
		int limpays = 66;                                         //Dernière position acceptée (juste avant l'espace-buffer) (92-26 = 66)
		int limfen = 0;                                           //Commencer à l'extrémité gauche de l'image  
                            //Pour obtenir la limite droite de l'image, simplement faire limfen + 26
		
		void affpays(void) {
			//Revenir au coin en haut à gauche de l'image
			curspos(1,1);
			//Dessiner tout le paysage
			for(int j=0; j<nlin ; j++) {
				if(j<4) {                              //Background de nuages
					chgcol("blanc");   SetConsoleTextAttribute(constxt, 15);
					for(int i=0; i<ncol-1 ; i++) cout << (paysage[j]) [i];              //ncol-1 : laisser la dernière colonne vide
																						Sleep(100);
				}
				else if(j<8) {                         //Background de montagnes
					chgcol("brun");   SetConsoleTextAttribute(constxt, 6);                      
					for(int i=0; i<ncol-1 ; i++) cout << (paysage[j]) [i];
																						Sleep(100);
					}
				else {                                 //Herbes et cailloux
					for(int i=0; i<ncol-1 ; i++) {
						
						cout << (paysage[j]) [i];
						//cette section me sort: ISO C++ forbids comparison between pointer and integer [0-fpermissive],
								//pour les lignes 134 et 135. Genre les comparaisons
						
						/*
						char symbole = (paysage[j]) [i]; 
						if(symbole == "'" | symbole == "\"" ) chgcol("vert");   //petites herbes
						else if(symbole == ".") chgcol("gris");                          //cailloux
						else chgcol("vert foncé");                                                //grandes herbes
						cout << symbole;
						
						*/
					}	
																						Sleep(100);											
				}	
				if(j<12) cout << " ";             //Ne pas descendre à la dernière ligne, pour ne pas faire bouger l'image        
			}
		}
//Main
int main() {
	
	//Définition des paramètres de la console (Windows uniquement)
		
		
		/*
		
		//Création des objets de console
		HWND consdim = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
		HANDLE constxt = GetStdHandle(STD_OUTPUT_HANDLE);         //Objet permettant de modifier le texte affiché dans la console
	
		*/       //Faut le définir avant le main pour que ça marche!

		//Changement de taille et de place de la console
			//MoveWindow(window_handle, x, y, width, height, redraw_window);
			MoveWindow(consdim, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
                                                                             //200x200 pixels = 13 lignes; 27 colonnes
	   
	//Mettre le background gris foncé
	SetConsoleTextAttribute(constxt, 0x8F);  
   
    //TEST: on peut probablement changer la couleur.. avant?   -> oui. qu'est-ce qui fuck???
    SetConsoleTextAttribute(constxt, 12);
    //TEST: afficher le paysage une fois
	//affpays();            
	//TEST: CHANGER LA COULEUR À LA FIN
	 SetConsoleTextAttribute(constxt, 11);            //Ça ça marche. C'est donc ma fonction de paysage qui le fait pas comme il faut...?

	//Mettre le background noir et le texte blanc
	SetConsoleTextAttribute(constxt, 0x0F);  
   

		//C'est comme si... la couleur ne pouvait être changée que dans le main(), et pas à l'intérieur d'une fonction???
		
					//Revenir au coin en haut à gauche de l'image
		curspos(1,1);
		//Dessiner tout le paysage
		for(int j=0; j<nlin ; j++) {
			if(j<4) {                              //Background de nuages
				SetConsoleTextAttribute(constxt, 0x0F);
				for(int i=0; i<ncol-1 ; i++) cout << (paysage[j]) [i];              //ncol-1 : laisser la dernière colonne vide
																					Sleep(100);
			}
			else if(j<8) {                         //Background de montagnes
				 SetConsoleTextAttribute(constxt, 0x06);                      
				for(int i=0; i<ncol-1 ; i++) cout << (paysage[j]) [i];
																					Sleep(100);
				}
			else {                                 //Herbes et cailloux
				for(int i=0; i<ncol-1 ; i++) {
	
					char symbole = (paysage[j]) [i]; 
					if(symbole == '\'' | symbole == '\"' )  SetConsoleTextAttribute(constxt, 0x0A);          //petites herbes   
					else if(symbole == '.')    SetConsoleTextAttribute(constxt, 0x07);                            //cailloux
					else      SetConsoleTextAttribute(constxt, 0x02);                                      //grandes herbes
					cout << symbole;
					
					
				}	
																					Sleep(100);											
			}	
			if(j<12) cout << " ";             //Ne pas descendre à la dernière ligne, pour ne pas faire bouger l'image        
		}
		
					//ouin. C'est exactement ça.

	//Et si après tout cela, on refait affpays()? techniquement, la fonction est censée remettre le curseur en haut à gauche.
			//si ça ne le fait pas, c'est que l,ensemble du Windows API a de la misère à l'intérieur d'une fonction.
	affpays();
	
								//Pronostic: C'est exactement ça. On ne peut pas accéder à ces commandes par une fonction???
	
	curspos(1,1);
	cout << "ESt-ce que je suis au sommet?";                   //curspos(), logiquement, ne fonctionne pas non plus. Mais alors...
		
		//Mais ça fonctionnait avant!	Sur l'autre script de test!
			
				//Serait-ce... parce que j'ai défini la version de windows au début, pour modifier la taille de l'écran?
							//-> Non, ça ne semble rien changer...
							
							
							//Résultat: faut définir les paramètres de console AVANT d'être dans le main.
}


//Bibliothèque:

	//Pour le changement de couleur:   
		/*
		0   BLACK
		1   BLUE
		2   GREEN
		3   CYAN
		4   RED
		5   MAGENTA
		6   BROWN
		7   LIGHTGRAY
		8   DARKGRAY
		9   LIGHTBLUE
		A  LIGHTGREEN         (10)
		B  LIGHTCYAN          (11)
		C  LIGHTRED           (12)
		D  LIGHTMAGENTA       (13)
		E  YELLOW             (14)
		F  WHITE              (15)
		*/
		                                 //   0x : sert à annoncer le type (hexadécimale, deux données)
		                                 //   1er symbole après: sert pour le background.
		                                 //   2e symbole après: sert pour le texte (foreground)

	// ex: 0xF0 : blanc sur fond noir
