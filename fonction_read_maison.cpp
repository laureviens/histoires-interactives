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


				//ATTENTION!!!!!!
						//VOIR https://www.fluentcpp.com/2018/12/28/timer-cpp/
						//POUR UN EXEMPLE DE TIMER AVEC DES THREADS (plutôt qu'avec une checkage constant, comme j'utilise)

			/*
			À la fin, on arrive sur:
			"The drawbacks of the library
				Why shouldn’t we use this library in production? What do you think?

				One issue is the very fact that it uses threads. 
				Indeed, the JavaScript equivalent uses an event loop, and does not create a new thread 
				for each invocation of setTimeout or setInterval."
			
			*/
			
			
			//ATTENTION!!!!!!
					//L'UTILISATION D'OBJETS time_t EST À CHANGER, CAR SA RÉSOLUTION EST EN SECONDES!
					
					//Voir la librairie chrono pour millisecondes?
			/*
			    https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets
			If you have access to the C++ 11 libraries, check out the std::chrono library. 
			You can use it to get the milliseconds since the Unix Epoch like this:

		#include <chrono>
		
		// ...
		
		using namespace std::chrono;
		milliseconds ms = duration_cast< milliseconds >(
		    system_clock::now().time_since_epoch()
		);
			*/
			
			
			
			//BTW:
						//Voir https://www.fluentcpp.com/2019/05/07/output-strings-separated-commas-cpp/,
						//qui fait quelque chose de similaire à ce que je fais, et qui nomme les objets créés pour servir d'interface
						//entre la console et le code (dans mon code, ce seraient les canaux) des "curried objects"

			//BTW:
						//Paraît que ce que je fais, c'est une "event-loop": https://en.wikipedia.org/wiki/Event_loop
						
			//Voir https://www.codeproject.com/Articles/1169105/Cplusplus-std-thread-Event-Loop-with-Message-Queue   ?
						//À propos de event loop + multithreading


			//BTW: Ce qui pourrait me sauver du multithreading: 
						//Voir comment // From : https://www.dreamincode.net/forums/topic/228811-microsoft-using-console-functions-to-achieve-blinking-text/
								// y arrive en utilisant les console handler 
								
								
			//BTW: https://stackoverflow.com/questions/27582493/cin-without-waiting-for-input
			
					//Donc en bref, quand même utiliser le getch() du jeu simple avec le raton laveur, mais
							//mettre son exécution conditionnelle à kbhit(), qui vérifie si une touche du keybord a été frappée?					

								//Conclusion: la structure que j'écris est encore valide.

//------------------------------------------------------------------------------------------------------------------------------------------------------
//0) Inclure les bonnes library et utiliser les raccourcis pour standard
#include <iostream>   //Pour les entrées/sorties
#include <string>     //Pour utiliser les objets strings
using namespace std;           //Pour faciliter l'utilisation de cout, cin, string, etc. (sans spécifier ces fonctions proviennent de quel enviro)

# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/classe_vect_maison.cpp"  //Pour les vecteurs maisons


//------------------------------------------------------------------------------------------------------------------------------------------------------
//1) Définir les objets de base sur lesquels va s'appuyer la suite
	
	//i) Classe : canal ; permet de sauvegarder la position de lecture du canal, le texte restant à lire, la vitesse, etc.
	class canal {
		//Membres
		public:
					//Déclarer les objets de temps; ceux-ci seront manipulés majoritairement avec la fonction time(), pour laquelle la
						//"value returned generally represents the number of seconds since 00:00 hours, Jan 1, 1970 UTC (i.e., the current unix timestamp)".
						//http://www.cplusplus.com/reference/ctime/time/
			time_t nxtt;        //Déclarer le moment où la prochaine entrée sera traitée         
			time_t delay;       //Déclarer le délai de base entre chaque entrée
			int posx, posy;		//Déclarer les coordonnées de la dernière entrée dans la mémoire (la précédente)   
								//les positions de la consoles sont définies en décalant ces dernières
			vect<char> txt;     //Déclarer le texte qui reste à lire  				
			bool actif;			//Déclarer le compteur d'activité
			double vit;         //Déclarer la vitesse actuelle de défilement et de pauses (toujours par rapport à la base, 1)
		//Constructeur
		canal() {nextt = time() ; delay = 0.4 ; posx = 1; posy = 1; actif = F; vit = 1}  //Créer un constructeur par défaut, pour initialiser tous les paramètres
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
						//PEUT-ÊTRE LE TRANSFORMER EN CLASSE POUR POUVOIR OVERRIDER UN OPÉRATEUR POUR AJOUTER DES LIGNES
		//Déclarer l'objet				
		vect <char[base.charx]>	mem;
		//Overrider l'opérateur %= afin de permettre d'ajouter une ligne vide à la position précise (en repoussant le reste vers le bas)			
		/*
		operator %= (int pos) {                 //CECI OVERRIDE L'OPÉRATEUR POUR LA CLASSE VECT UTILISÉE! FAIRE UNE AUTRE VERSION DE VECT POUR L'INSÉRER???
			i) Copier tout ce qu'on veut avant
			ii) Ajouter une ligne vide
			iii) Copier tout ce qui vient après (probablement en utilisant l'opérateur += ?)
		}
		*/

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
				can.nxtt += val * can.vit                    //Ajouter le temps d'attente
				
							//VA PEUT-ÊTRE NÉCESSITER UNE CONVERSION DE DOUBLE À TIME_T
							
									//OUPS??? SELON https://stackoverflow.com/questions/31000399/convert-double-to-time-t,
									//    time_t AURAIT COMME PLUS FINE RÉSOLUTION LA SECONDE????
									
			} else if(can.txt[1]=='v'){      //'v' pour "vitesse" -> changer la vitesse de lecture
				double val = cdspxtr(can.txt,cdsppos);       //Extraire la nouvelle vitesse
				can.vit = val;
			}  //EN AJOUTER UN (code spécial) POUR PLACER LE CURSEUR À LA FIN DE LA CONSOLE
		
		//Effacer le code spécial du canal
		can.txt-=cdsppos;                           //VOIR QUE OPÉRATEUR GARDER POUR CETTE OPÉRATION? REFONTE POSSIBLE DES OPÉRATEURS DE VECT?
																	//GENRE +int pour ajouter une entrée à position; -int pour enlever une entrée à position
		
		
	} else {  //Interpréter le reste des caractères (pas des codes spéciaux)
		//Dealer avec la situation où on a à sauter une ligne (créer les lignes supplémentaires et updater les diverses positions)
			bool jump = false;
			if(can.txt[0]=='\n'|can.posx>=base.charx) jump = true;
			if(jump) {
				
				//BTW, JE NE PEUX PAS INSCRIRE '\N' DANS LA CONSOLE, JE CROIS, PARCE QUE ÇA PREND UN ESPACE??? 
						//ME SEMBLE, QUAND JE FAISAIS LE TEST AVEC LE RATON LAVEUR, SKIPPER UNE LIGNE À LA FIN SKIPPAIT EN FAIT DEUX LIGNES,
						//car la console semblait marcher comme suit: 
							//le curseur est bougé après que quoi que ce soit est écrit.
							//Si c'est à la limite de la console, donc,
							//                                          le curseur, indépendamment de ce qui s'en vient ensuite, sera
							//DÉJÀ sur la ligne suivante. Donc le newline va arriver sur la ligne suivante, "skippant une ligne supplémentaire".
							
						//Ce que je me suis dit, c'est que la posx et posy seraient la PROCHAINE entrée dans la console.
						//Mais ça marche difficilement. J'peux pas créer des nouvelles lignes vides pour rien, automatiquement à chaque fois qu'on
						//arrive à la fin d'une ligne.
						
						//Ce qui marcherait bien, c'est que ces coordonnées représentent LA DERNIÈRE ENTRÉE.
						//Comme ça, si on est rendues à la fin d'une ligne, on peut tout de suite aviser.
						//Pis si on arrive au début d'une ligne, on n'a même pas à se demander si on est arrivé là automatiquement ou par '\n', 
						//on fait juste continuer. Ce sera donc ça.
			
				//J'vais donc dealer avec écrire DANS la console après.    //Also parce que ça peut faire appel à ce qui est écrit dans la mémoire? non?
	
				
				//Sauter une ligne dans la mémoire
				for(int countx = can.posx + 1; countx < base.charx ; countx++) mem [can.posy] [countx] = ' ';     //Effacer le reste de la ligne avec des espaces    
				mem %= can.posy;                         //Cet opérateur introduit une nouvelle ligne à la suite de la dernière position en y			
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
								   //BTW, Y'A CE TRUC BIZARRE OÙ FAUT METTRE < AU LIEU DE <=, PARCE QUE INDEX COMMENCE À [0]
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
				
				
				
							//WAIT. EST-CE QU'IL Y A UN DIVORCE ICI ENTRE LES REQUIREMENTS DE LA CONSOLE ET CEUX DE LA MÉMOIRE?   //réglé: voir la fin.
							
									//PARCE QUE POSY DE LA CONSOLE DÉPENDENT BEAUCOUP DE CE QUI A ÉTÉ BOUGÉ DANS LA CONSOLE.
									//POSY DE LA MÉMOIRE, EUX, RESTENT STABLES.
												//QUOI FAIRE??????
				
						//Ce problème ne se soulève pas quand la console est insaturée, car alors tout bouge vers le bas, en harmonie.
						//Par contre, quand elle est saturée, on repousse l'excédent vers le haut,
						//tandis que la mémoire, elle, obtient une nouvelle entrée qui repousse tout vers le bas.
						//           parce que c'est ainsi que mon système de notation fonctionne (partir de 0, et augmenter).
							//Pour réconcilier l'affichage et la sauvegarde des positions,
							//je propose de conserver pos.y en fonction de la position dans la mémoire.
							//(c'est un peu comme ça qu'il est codé, right now, puisqu'il n'y a pas de conditions à son augmentation).
								//(Mais vraiment juste dans la section "Updater les positions dans le canal actuel", ailleurs faudrait changer)
							//Comme ça, on pourrait vraiment s'appuyer sur ce qui est écrit dans la mémoire pour rendre la console.
							//"memy" deviendrait alors "consy".
							
						//TRUCS À CHANGER: toutes les instances où curspos() apparaît, et toutes où memy apparaît.
								//Je pense que tout est changé, maintenant.
				
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
		can.txt-=0;                           //VOIR QUE OPÉRATEUR GARDER POUR CETTE OPÉRATION? REFONTE POSSIBLE DES OPÉRATEURS DE VECT?
																	//GENRE +int pour ajouter une entrée à position; -int pour enlever une entrée à position
	}
}

	

