
//Doodles d'objets graphiques:
/*______________________________________________________________________________________________________________________________---
	Herbe: \/  \|/   /    \
	
	Oiseau:   -\~_  -_~_  -/~_  -�~_  ou   -/~_  -\~_
	
	Chat:                           |
			\_-~�^^    __-~�^^      \-~�^^    ou    \_���^^
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


//Code pour g�n�rer le jeu:
//_________________________________________________________________________________________________________________________________---

//D�finition de l'environnement

#include <iostream>   //Pour les entr�es/sorties

#define _WIN32_WINNT 0x0500    //N�cessaire pour la taille de la fen�tre: informe qu'on est sur Windows 2000 ou plus r�cent
#include <windows.h>           //N�cessaire pour toute modification de la console sur Windows (utilie "Windows API")

using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans sp�cifier ces fonctions proviennent de quel enviro)

//Cr�ation des dessins
	
	//Cr�ation du paysage
														// Les symboles \ et " sont pr�c�d�s de \, pour les compter comme des characters
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

	//Cr�ation du chat:
	string c1a = ""          ;   string c1b = ""          ;   string c1c = "|";           
	string c2a = "__-~�^^"   ;   string c2b = "\\_-~�^^"   ;   string c2c = "\\-~�^^";   
	string c3a =    "\\\\\\\\";  string c3b =    "/\\/\\"   ; string c3c =   "///\\";       //pour une d�marche a-b-c-b-a-b-c-b-a... 

		//Mise en array du chat:
		//string c[3][3]; c[1] = {c1a,c1b,c1c} ; c[2] = {c2a,c2b,c2c} ; c[3] = {c3a,c3b,c3c;          //ne marche pas...
		string c1[3] = {c1a,c1b,c1c} ; string c2[3] = {c2a,c2b,c2c} ; string c3[3] = {c3a,c3b,c3c};   //version alternative?


//D�finition des param�tres de la console (Windows uniquement)
	
	//Cr�ation des objets de console
	HWND consdim = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
	HANDLE constxt = GetStdHandle(STD_OUTPUT_HANDLE);         //Objet permettant de modifier le texte affich� dans la console


//D�finition des fonctions utilis�es:
	
	//Fonction pour d�placer le curseur sur la console
	COORD CursorPosition;                                     //Objet permettant de se situer sur la console
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(constxt,CursorPosition); 
	}	

	//Fonction pour changer de couleur facilement
	/*                                                   //Version qui ne marche pas, probablement d� � des probl�me de conversion de int � WORD (code)
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

		//D�finir les dimensions de l'image
		int nlin = 13;
		int ncol = 27;

		//Cr�er les objets de limites horizontales � l'image
		int limpays = 66;                                         //Derni�re position accept�e (juste avant l'espace-buffer) (92-26 = 66)
		int limfen = 0;                                           //Commencer � l'extr�mit� gauche de l'image  
                            //Pour obtenir la limite droite de l'image, simplement faire limfen + 26
		
		void affpays(void) {
			//Revenir au coin en haut � gauche de l'image
			curspos(1,1);
			//Dessiner tout le paysage
			for(int j=0; j<nlin ; j++) {
				if(j<4) {                              //Background de nuages
					chgcol("blanc");   SetConsoleTextAttribute(constxt, 15);
					for(int i=0; i<ncol-1 ; i++) cout << (paysage[j]) [i];              //ncol-1 : laisser la derni�re colonne vide
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
						else chgcol("vert fonc�");                                                //grandes herbes
						cout << symbole;
						
						*/
					}	
																						Sleep(100);											
				}	
				if(j<12) cout << " ";             //Ne pas descendre � la derni�re ligne, pour ne pas faire bouger l'image        
			}
		}
//Main
int main() {
	
	//D�finition des param�tres de la console (Windows uniquement)
		
		
		/*
		
		//Cr�ation des objets de console
		HWND consdim = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
		HANDLE constxt = GetStdHandle(STD_OUTPUT_HANDLE);         //Objet permettant de modifier le texte affich� dans la console
	
		*/       //Faut le d�finir avant le main pour que �a marche!

		//Changement de taille et de place de la console
			//MoveWindow(window_handle, x, y, width, height, redraw_window);
			MoveWindow(consdim, 500, 250, 200, 200, TRUE);                   //Les unit�s sont en pixels!
                                                                             //200x200 pixels = 13 lignes; 27 colonnes
	   
	//Mettre le background gris fonc�
	SetConsoleTextAttribute(constxt, 0x8F);  
   
    //TEST: on peut probablement changer la couleur.. avant?   -> oui. qu'est-ce qui fuck???
    SetConsoleTextAttribute(constxt, 12);
    //TEST: afficher le paysage une fois
	//affpays();            
	//TEST: CHANGER LA COULEUR � LA FIN
	 SetConsoleTextAttribute(constxt, 11);            //�a �a marche. C'est donc ma fonction de paysage qui le fait pas comme il faut...?

	//Mettre le background noir et le texte blanc
	SetConsoleTextAttribute(constxt, 0x0F);  
   

		//C'est comme si... la couleur ne pouvait �tre chang�e que dans le main(), et pas � l'int�rieur d'une fonction???
		
					//Revenir au coin en haut � gauche de l'image
		curspos(1,1);
		//Dessiner tout le paysage
		for(int j=0; j<nlin ; j++) {
			if(j<4) {                              //Background de nuages
				SetConsoleTextAttribute(constxt, 0x0F);
				for(int i=0; i<ncol-1 ; i++) cout << (paysage[j]) [i];              //ncol-1 : laisser la derni�re colonne vide
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
			if(j<12) cout << " ";             //Ne pas descendre � la derni�re ligne, pour ne pas faire bouger l'image        
		}
		
					//ouin. C'est exactement �a.

	//Et si apr�s tout cela, on refait affpays()? techniquement, la fonction est cens�e remettre le curseur en haut � gauche.
			//si �a ne le fait pas, c'est que l,ensemble du Windows API a de la mis�re � l'int�rieur d'une fonction.
	affpays();
	
								//Pronostic: C'est exactement �a. On ne peut pas acc�der � ces commandes par une fonction???
	
	curspos(1,1);
	cout << "ESt-ce que je suis au sommet?";                   //curspos(), logiquement, ne fonctionne pas non plus. Mais alors...
		
		//Mais �a fonctionnait avant!	Sur l'autre script de test!
			
				//Serait-ce... parce que j'ai d�fini la version de windows au d�but, pour modifier la taille de l'�cran?
							//-> Non, �a ne semble rien changer...
							
							
							//R�sultat: faut d�finir les param�tres de console AVANT d'�tre dans le main.
}


//Biblioth�que:

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
		                                 //   0x : sert � annoncer le type (hexad�cimale, deux donn�es)
		                                 //   1er symbole apr�s: sert pour le background.
		                                 //   2e symbole apr�s: sert pour le texte (foreground)

	// ex: 0xF0 : blanc sur fond noir
