/*
			///||================================---2018/06/10---================================||\\\
\\\||================================---Fonction read() pour créer des outputs à partir des canaux de lecture---================================||///
*/

//Debbugg: pour avoir l'option de "sleep"
#include <unistd.h>

		//ATTENTION!!!!!		
				//Je viens de me rendre compte que, de la manière dont je calcule les lignes, ça ressemble à:
				/*
				 0 1 2 3 4 5 6 7 8 
				0
				1
				2
				3
				4
				5
				6
						ce qui peut être mélangeant pour l'axe des y. Just bear with me, though, j'pense que c'est la méthode la plus simple.
				*/

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
#include <cmath>      //Pour utiliser la fonction round()
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
#define _WIN32_WINNT 0x0500    //Nécessaire pour la taille de la fenêtre: informe qu'on est sur Windows 2000 ou plus récent
#include <windows.h>           //Nécessaire pour toute modification de la console sur Windows (utilie "Windows API")
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Définir les objets de base sur lesquels va s'appuyer la suite
	
		//ix) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems (void) {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    std::chrono::system_clock::now().time_since_epoch()
	).count());
	}	
	
	//i) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant à lire, la vitesse, etc.
	class canal {
		//Membres
		public:
			int nxtt;           //Déclarer le moment où la prochaine entrée sera traitée         
			int delay;          //Déclarer le délai de base entre chaque entrée
			int posx, posy;		//Déclarer les coordonnées de la dernière entrée dans la mémoire (la précédente)   
								//les positions de la consoles sont définies en décalant ces dernières
			StringAsVect txt;   //Déclarer le texte qui reste à lire  				
			bool actif;			//Déclarer le compteur d'activité
			double vit;         //Déclarer la vitesse actuelle de défilement et de pauses (toujours par rapport à la base, 1)
		//Constructeur
		canal() {nxtt = timems() ; delay = 400 ; posx = 1; posy = 1; actif = false; vit = 1;}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
	};

	//ii) Classe : fen ; permet de sauvegarder les paramètres relatifs aux caractéristiques de la fenêtre de sortie (console)
	class fen {
		//Membres
		public:
			int charx, chary;     //Déclarer les dimensions de la fenêtre en terme de nombre de caractères pouvant y être contenus
			int consy;             //Déclarer le facteur de décalement de la console où apparaît le texte avec la mémoire, où il est stocké
			bool refoule;          //Déclarer le flag pour voir si le facteur de décalement entre en compte
		//Constructeurs
		fen() {charx = 1; chary = 1; consy = 0; refoule = false;}      //Créer un constructeur par défaut, pour initialiser tous les paramètres
					//À RETRAVAILLER POUR Y METTRE UNE FONCTION PERMETTANT DE DEVINER AUTOMATIQUEMENT LES DIMENSIONS DE LA FENÊTRE!
		fen(int x, int y) {charx = x; chary = y; consy = 0; refoule = false;}      //Créer un constructeur permettant d'assigner manuellement les dimensions de la fenêtre	
	};
		//Créer l'objet base, qui contiendra les information sur la fenêtre de base
		fen base(27,13);     //EN CE MOMENT, A LES DIMENSIONS DE 27 COLONNES ET 13 LIGNES (VOIR JEU GRAPHIQUE SIMPLE)

	//iii) classe : memoire ; permet de sauvegarder la "mémoire" de la console, c'est-à-dire tous le texte s'y étant déjà inscrit
		class memoire{
			//Membres
			public: 
				int nbligne;
				char** souvenir;            //L'objet contient, en façades, des pointeurs pointant à d'autres pointeurs
			//Constructeur par défaut
			memoire() {
				nbligne = 1;                         //Ce qui suit semble être la seule manière de créer des arrays dynamiques
				souvenir = new char* [base.charx];   //Créer un premier array contenant des pointers
				for(int col=0; col<base.charx ; col++) {souvenir[col] = new char [nbligne];}    //Créer les lignes pour chaque colonne
			}
			//Destructeur
			~memoire() {
				for(int col=0; col<base.charx ; col++) delete[] souvenir[col] ; delete[] souvenir;   //Bien déconstruire tout proprement
			}
			//Fonction d'accès : retourner certaines positions
			char acces (int posx, int posy) { //Créer une fonction permettant d'aller chercher une valeur de l'array (une seule position)
				return(souvenir[posx][posy]);
			}
			//Fonction de modification : ajouter une ligne à la suite de la position spécifiée (Opérateur +) 
			void operator + (int pos) {
				int emptypos = pos + 1;   //Calculer la position qui sera vide
				char** nwsouv = new char* [base.charx] ; for(int xpos = 0; xpos<base.charx ; xpos++) {nwsouv [xpos] = new char [nbligne+1];}  //Déclarer le nouvel array (transitoire)
				int oldpos = 0;  //Déclarer un compteur pour les vieilles positions				
				for(int nwpos=0; nwpos < nbligne; nwpos++) {  //Remplir, en laissant une position vide
					if(nwpos==emptypos) {continue;} 
					for(int xpos = 0; xpos<base.charx ; xpos++) {nwsouv[xpos][nwpos] = souvenir[xpos][oldpos];}
					oldpos++;
				}
				nbligne++;   //Noter qu'on ajoute une ligne
				for(int col=0; col<base.charx ; col++) delete[] souvenir[col] ; delete[] souvenir;  //Éliminer le vieil array   
				souvenir = nwsouv;  //Assigner le pointeur à l'array actuel
				for(int col=0; col<base.charx ; col++) delete[] nwsouv[col] ; delete[] nwsouv;  //Éliminer l'array transitoire
			}
		};
		memoire mem;

	//iv) Fonction : cdsppos ; retourne la position des caractères du code spécial      //DEBUGGING: CE TYPE RESSORT PAS COMME UN VECT<INT>?????
	vect<int> cdspposition(StringAsVect str){
		vect<int> pos = 0;              //Initier l'objet à retourner
		int a = 1;                      //Commencer à la position [1], le [0] étant occupé par '§' (et déjà comptabilisé)
		while(str[a]!='§'&a<str.nb) pos += a;
		return(pos);		
	}

	//v) Fonction : cdspxtr ; extrait une valeur double d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
	double cdspxtr(StringAsVect str, int cdspnb){
		string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres
		int a = 2;                      //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire
		while(a<cdspnb) {nbonly += str[a];}
		return(stod(nbonly));           //La fonction stod convertit les strings en doubles (https://stackoverflow.com/questions/4754011/c-string-to-double-conversion)
	}				

				//BTW: POURRAIT FACILEMENT DEVENIR UN TEMPLATE! (ex: pour retourner des int, à la place)
				
	//vi) Objet : canaux ; assemblage de tous les canaux utilisés
	vect<canal> canaux;

	//vii) Objets : TxtConsole et CursorPosition ; permet de modifier le texte affiché dans la console   		//WINDOWS ONLY
	HANDLE TxtConsole = GetStdHandle(STD_OUTPUT_HANDLE);        //Objet permettant de modifier le texte affiché dans la console 
	COORD CursorPosition;                                     	//Objet permettant de se situer sur la console

	//viii) Fonction: curspos ; déplacer le curseur sur la console
	void curspos(int x, int y) { 
		CursorPosition.X = x; CursorPosition.Y = y; 
		SetConsoleCursorPosition(TxtConsole,CursorPosition);            //WINDOWS ONLY
	}	
	
	//x) Fonction : out ; affiche le caractère dans la console
	void out(char lettre){
		if(lettre=='À') std::wcout << L"\u00C0";
		else if(lettre=='à') std::wcout << L"\u00E0";
		else if(lettre=='Ç') std::wcout << L"\u00C7";		
		else if(lettre=='ç') std::wcout << L"\u00E7";
		else if(lettre=='É') std::wcout << L"\u00C9";		
		else if(lettre=='é') std::wcout << L"\u00E9";
		else if(lettre=='È') std::wcout << L"\u00C8";
		else if(lettre=='è') std::wcout << L"\u00E8";
		else if(lettre=='Î') std::wcout << L"\u00CE";
		else if(lettre=='î') std::wcout << L"\u00EE";
		else if(lettre=='Ï') std::wcout << L"\u00CF";
		else if(lettre=='ï') std::wcout << L"\u00EF";						
		else if(lettre=='Ô') std::wcout << L"\u00D4";
		else if(lettre=='ô') std::wcout << L"\u00F4";
		else if(lettre=='Ù') std::wcout << L"\u00D9";
		else if(lettre=='ù') std::wcout << L"\u00F9";	
		else if(lettre=='Û') std::wcout << L"\u00DB";
		else if(lettre=='û') std::wcout << L"\u00FB";	
		else {std::wcout << lettre;}
	}

//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Écrire la fonction read()
read(canal& can) {
	//Updater le "next time"
	can.nxtt += can.delay;
	//Interpréter les "codes spéciaux" (§...§)
	if(can.txt[0]=='§'){		
		//Déterminer la position du code spécial
		vect<int> cdsppos = cdspposition(can.txt);	
		//Lire le code spécial		
			if(can.txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture
				double val = cdspxtr(can.txt,cdsppos.nb);       //Extraire le temps que durera la pause
				can.nxtt += round(val * can.vit);                    //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
			} else if(can.txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = cdspxtr(can.txt,cdsppos.nb);       //Extraire la nouvelle vitesse
				can.vit = val;
			}  //EN AJOUTER UN (code spécial) POUR PLACER LE CURSEUR À LA FIN DE LA CONSOLE		
		//Effacer le code spécial du canal
		can.txt-cdsppos;                       
	} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
		//Dealer avec la situation où on a à sauter une ligne (créer les lignes supplémentaires et updater les diverses positions)
			bool jump = false;
			if(can.txt[0]=='\n'|can.posx>=base.charx) jump = true;
			if(jump) {
				//Sauter une ligne dans la mémoire
				for(int countx = can.posx + 1; countx < base.charx ; countx++) mem.souvenir[countx][can.posy] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem + can.posy;                         //Cet opérateur introduit une nouvelle ligne à la suite de la position qui lui est fournie			
				//Updater le correctif de décalage de la console par rapport à la mémoire
					if(base.refoule) base.consy++; else if(mem.nbligne>base.chary) {base.refoule = true; base.consy++;} 					
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore saturée: on pousse vers le bas!
						if(can.posy==mem.nbligne-1) {               //Si le canal gère la dernière ligne de la console, c'est plus simple    //-1 : à cause de [0]
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
						} else {                             //S'il y a d'autres lignes à repousser vers le bas
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
							//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,can.posy-base.consy + 2);  //Mettre le curseur au début de la reconstruction
								for(int county = can.posy + 2 ; county < mem.nbligne ; county++) {    // + 2, parce que la mémoire a déjà été updatée
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
								}
						}
					} else {                         //La console est saturée: on pousse le texte vers le haut!
						//Effacer toute la ligne avec des espaces (en "reléguant ce qui y était déjà vers le haut")
							curspos(can.posy-base.consy,0); for(int countx = 0; countx < base.charx ; countx++) out(' '); 					
						//Tout ré-écrire, mais une ligne plus haut
	    					curspos(0,0);   //Commencer en haut, puis descendre naturellement
							for(int county = base.consy; county < can.posy; county++){             //base.consy : facteur de décalage de la console
										//VÉRIFIER L'INITIATION DE COUNTY: ÇA SEMBLE UN BEL ADON QUE base.consy, UN "count" EN INTEGER SIMPLE,
										//S'EMBOÎTE PARFAITEMENT AVEC L'INDEXATION QUI COMMENCE À 0!
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem.souvenir[countx][county]);
							}				                 
					}
/*				//Updater les positions dans les autres canaux    //Parce que leur position dans la mémoire a bougé //la position dans la console est quant à elle gérée par base.consy
				for(int countcan = 0 ; countcan < canaux.nb ; countcan++) {        
					if(canaux[countcan].posy > can.posy) canaux[countcan].posy++;         //la mémoire refoule toujours vers le bas!
				}
*/                                                            //FAUDRA Y RETOURNER POUR DÉBUGUER!				
				//Updater les positions dans le canal actuel
				if(can.txt[0]=='\n') {can.posx = -1;} else can.posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
	////////										//FLAG POUR POSITION IMPOSSIBLE; PEUT-ÊTRE QUE ÇA VA EMMENER UN BUG ÉVENTUELLEMENT?
				can.posy++;																   //en y 
			} else can.posx++;        //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du charactère actuel (dans la mémoire)!		
		if(can.txt[0]!='\n') {
			curspos(can.posx,can.posy-base.consy) ; out(can.txt[0]);     //Inscrire dans la console
			mem.souvenir[can.posx][can.posy] = can.txt[0];   //Inscrire dans la mémoire
		}	
		//Effacer le caractère du canal
		can.txt-0;                          
	}
}

	
//Et maintenant... Tester?
						//Avec les dimensions du jeu graphique simple!


					
HWND DimConsole = GetConsoleWindow();                        //Objet permettant de modifier les dimensions + la position de la console
						
					
							
int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	out('H'); out('e'); out('l'); out('l'); out('o'); out('?');	out('\n');  //Fonctionne!

	//cout<< "\nbase.charx:" << base.charx << "  base.chary:" << base.chary;

	//Créer les canaux utilisés
	canal can1;
	string txt0 = "Ceci est du texte! Je dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	can1.txt = txt0;
	can1.txt.out();
	int currentt = timems();

	while(true){
		currentt = timems();
			if(can1.nxtt<currentt) {read(can1);}
		}	                                         //Pis ça crashe après pas trop longtemps.
					//Probablement une erreur d'allocation de mémoire?
							//Probablement que je ne nettois pas assez bien ma mémoire?
							
								//Pour cela, Stack Overflow me propose de simplement ajouter à chaque destructeur et constructeur
								//un update de l'utilisation totale de mémoire.
								
								//Pour cela, faudrait d'abord que je comprenne exactement qu'est-ce qui a besoin de constructeur/destructeur dans mes vecteurs.
						//BLargh, j'ai tenté de nettoyer la mémoire, mais ça crash encore plus.
	
	}
			
			/*				
int main(void) {

	//Changement de taille et de place de la console                     //Doit être défini à l'intérieur du main() pour fonctionner!
		//MoveWindow(window_handle, x, y, width, height, redraw_window);
		MoveWindow(DimConsole, 500, 250, 200, 200, TRUE);                   //Les unités sont en pixels!
                                                                         //200x200 pixels = 13 lignes; 27 colonnes

	//Créer les canaux utilisés
	canal can1;
	canal can2;
	
	//Test: changer les délais manuellement
	can1.delay = 240;
	can2.delay = 430;
	
	//Les ajouter à l'objet canaux
	canaux += can1; canaux +=can2;
	
	//Ajouter du texte aux canaux
	string txt0 = "Ceci est du texte! Je dis du texte, maintenant! \n Wouhouuuu! Je suis le canal 1!";
	string txt1 = "Le canal 1 est sooooo boring. Ark. §p10000§\n Je suis le canal 2.";
	canaux[0].txt = txt0;
	//canaux[0].delay = 200;              //Error: using temporary as lvalue [-fpermissive]
	
	canaux[1].txt = txt1;
	//canaux[1].delay = 400;

	//Faire une boucle pour que les canaux s'expriment!
	while(true){
		int currentt = timems();
		for(int canpos = 1; canpos<canaux.nb; canpos++){
			if(canaux[canpos].nxtt>currentt) read(canaux[canpos]);
			}
		}
}					
*/
