/*
			///||================================---2018/06/10---================================||\\\
\\\||================================---Fonction read() pour créer des outputs à partir des canaux de lecture---================================||///
*/


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
#include <chrono>     //Pour avoir un meilleur contrôle du temps (en millisecondes)
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons

//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Définir les objets de base sur lesquels va s'appuyer la suite
	
		//ix) Fonction : timems ; avoir le temps actuel en millisecondes (depuis l'epoch, soit 1er janvier 1970)
	int timems {
		return(std::chrono::duration_cast< std::chrono::milliseconds >(
	    std::chrono::system_clock::now().time_since_epoch()
	).count())
	}	
	
	//i) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant à lire, la vitesse, etc.
	class canal {
		//Membres
		public:
			int nxtt;           //Déclarer le moment où la prochaine entrée sera traitée         
			int delay;          //Déclarer le délai de base entre chaque entrée
			int posx, posy;		//Déclarer les coordonnées de la dernière entrée dans la mémoire (la précédente)   
								//les positions de la consoles sont définies en décalant ces dernières
			vect<char> txt;     //Déclarer le texte qui reste à lire  				
			bool actif;			//Déclarer le compteur d'activité
			double vit;         //Déclarer la vitesse actuelle de défilement et de pauses (toujours par rapport à la base, 1)
		//Constructeur
		canal() {nextt = timems() ; delay = 400 ; posx = 1; posy = 1; actif = F; vit = 1}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
	};

	//ii) Classe : cons ; permet de sauvegarder les paramètres relatifs aux caractéristiques de la fenêtre de sortie (console)
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
		fen base;

	//iii) Objet : mem ; permet de sauvegarder la "mémoire" de la console, c'est-à-dire tous le texte s'y étant déjà inscrit
		vect <char[base.charx]>	mem;  		//Déclarer l'objet				

	//iv) Fonction : cdsppos ; retourne la position des caractères du code spécial
	vect<int> cdsppos(vect<char> str){
		vect<int> pos = 0;              //Initier l'objet à retourner
		int a = 1;                      //Commencer à la position [1], le [0] étant occupé par '§' (et déjà comptabilisé)
		while(str[a]!='§'&a<str.nb) pos += a;
		return(pos);		
	}

	//v) Fonction : cdspxtr ; extrait une valeur double d'une suite de caractères encadrés par '§' (pour extraire les codes spéciaux)
	double cdspxtr(vect<char> str, vect<int> pos){
		string nbonly;                  //Initier un string, dans lequel insérer seulement les chiffres
		int a = 2;                      //Commencer à la position [2], le [0] étant occupé par '§' et le [1] par le type de valeur à extraire
		while(a<pos.nb) {nbonly += str[a];}
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
		SetConsoleCursorPosition(constxt,CursorPosition);            //WINDOWS ONLY
	}	
	


//------------------------------------------------------------------------------------------------------------------------------------------------------
//2) Écrire la fonction read()
read(canal can) {
	//Interpréter les "codes spéciaux" (§...§)
	if(can.txt[0]=='§'){		
		//Déterminer la position du code spécial
		vect<int> pos = cdsppos(can.txt);	
		//Lire le code spécial		
			if(can.txt[1]=='p'){      //'p' pour "pause" -> ajouter une pause à la lecture
				double val = cdspxtr(can.txt,cdsppos);       //Extraire le temps que durera la pause
				can.nxtt += round(val * can.vit)                    //Ajouter le temps d'attente        //round() est nécessaire pour arrondir correctement					
			} else if(can.txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = cdspxtr(can.txt,cdsppos);       //Extraire la nouvelle vitesse
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
				for(int countx = can.posx + 1; countx < base.charx ; countx++) mem [can.posy] [countx] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem + can.posy;                         //Cet opérateur introduit une nouvelle ligne à la suite de la position qui lui est fournie			
				//Updater le correctif de décalage de la console par rapport à la mémoire
					if(base.refoule) base.consy++; else if(mem.nb>base.chary) {base.refoule = true; base.consy++;} 					
				//Sauter une ligne dans la console
					if(!base.refoule) {          //La console n'est pas encore saturée: on pousse vers le bas!
						if(can.posy==mem.nb-1) {               //Si le canal gère la dernière ligne de la console, c'est plus simple    //-1 : à cause de [0]
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
						} else {                             //S'il y a d'autres lignes à repousser vers le bas
							if(can.posx<base.charx-1) out('\n');     //Forcer le saut de page; sinon, il se fait par lui-même!   //-1 : à cause de [0]
							//Ré-écrire tout ce qu'il y avait en-dessous de la position actuelle, mais une ligne plus basse
								curspos(0,can.posy-base.consy + 2);  //Mettre le curseur au début de la reconstruction
								for(int county = can.posy + 2 ; county < mem.nb ; county++) {    // + 2, parce que la mémoire a déjà été updatée
									for(int countx = 0 ; countx < base.charx ; countx++) out(mem[county][countx]);
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
								for(int countx = 0 ; countx < base.charx ; countx++) out(mem[county][countx]);
							}				                 
					}
				//Updater les positions dans les autres canaux    //Parce que leur position dans la mémoire a bougé //la position dans la console est quant à elle gérée par base.consy
				for(int countcan = 0 ; countcan < canaux.nb ; countcan++) {        
					if(canaux[countcan].posy > can.posy) canaux[countcan].posy++;         //la mémoire refoule toujours vers le bas!
				}
				//Updater les positions dans le canal actuel
				if(can.txt[0]=='\n') {can.posx = -1;} else can.posx = 0;			       //en x    
									//Position "impossible", pour signifier qu'on a changé de ligne, mais écrire le prochain à la bonne place
	////////										//FLAG POUR POSITION IMPOSSIBLE; PEUT-ÊTRE QUE ÇA VA EMMENER UN BUG ÉVENTUELLEMENT?
				can.posy++;																   //en y 
			} else can.posx++;        //Updater seulement posx s'il n'y a pas de mouvement vertical
		//Inscrire le caractère       //À partir d'ici, les posx et posy sont la position du charactère actuel (dans la mémoire)!
		if(can.txt[0]!='\n') {
			curspos(can.posx,can.posy-base.consy) ; ~can.txt[0];     //Inscrire dans la console
									//ATTENTION: ~ CORRESPOND À UNE FCT DE STYLE COUT(); OPÉRATEUR QUI VA PEUT-ÊTRE CHANGER.
			mem[can.posy][can.posx] = can.txt[0];   //Inscrire dans la mémoire
		}	
		//Effacer le caractère du canal
		can.txt-0;                          
	}
}

	
//Et maintenant... Tester?
						//Avec les dimensions du jeu graphique simple!
						
int main {



}						
