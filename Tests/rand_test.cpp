/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / Démo du potentiel interactif / narratif---================================||///
*/

//-----------------------------------------------------------------|  Explication de la base |--------------------------------------------------------------------------------\\

		//J'explique ici le coeur de ma façon d'écrire des "fictions interactives" (ou "aventures narratives" ou "text adventure", etc.)
			//Chaque histoire (interactive) sera composée de petites unités, qui comprennent à la fois le texte à lire et les conditions dans lequel ce texte sera lu.
			//J'appelle ici ces unités des "motifs".
			//Le principe à la base de cette idée de création "interactive" est que ces motifs pourront s'enchaîner, se croiser, se superposer à leur guise, dans un ordre pas forcément linéaire, dans l'ordre décidé par les actions de la joueuse.

		//Afin d'organiser efficacement cette collection de motifs, je les regroupe en "chapitres".
		
		//J'utilise deux types de "motifs" : les motifs "automatiques" et les motifs "manuels".
			//Les motifs automatiques n'attendent que les conditions propices pour déverser leur texte dans la fenêtre de jeu.
			//Les motifs manuels, quant à eux, sont exécuté quand les conditions propices sont réunies ET seulement si la bonne commande les appelle.
				//C'est par les motifs manuels que la joueuse pourra influencer le cours de l'histoire, en appelant certaines actions plutôt que d'autres, ou plutôt qu'une inaction.

		//Pour conserver l'information relative à la progression du jeu, et à quelle condition est remplie au moment présent, j'utilise la bibliothèque (introduite plus haut).

		//Pour interagir avec le système de jeu (supprimer un dialogue déjà intégré mais devenu caduque, noter la progression, changer la vitesse, etc.), j'utilise seulement le texte à lire.
			//À l'intérieur de ce "texte à lire", je vais donc cacher des "codes spéciaux".
				//Un "code spécial", c'est simplement quelque chose qui n'apparaîtra pas à l'écran, mais dont la "lecture" enclenchera une action quelconque (une interaction avec le système de jeu).
			//Pour marquer un "code spécial", j'utilise le symbole '§' (qui est un caractère que j'ai jugé que je n'utiliserai jamais dans le texte que je veux voir affiché à l'écran).
				//Un code spécial sera donc un bout de texte entouré de '§' (à la manière de parenthèses ou d'accolades)
				//La deuxième lettre du code (la première étant '§') indiquera l'action à effectuer et la façon dont on doit lire le reste du code spécial. 
					//Par exemple, "§p1000§" signifie "prendre une pause de 1000 millisecondes dans la lecture". En gros: attendre une seconde.
					//Un exemple bête : "Je suis due pour une pause.§p2000§ Merci!" sera lu comme : "Je suis due pour une pause." - pause de 2 secondes - " Merci!"
					
			
//-----------------------------------------------------------------|  Préparation technique  |--------------------------------------------------------------------------------\\
 
# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"
		//On a besoin de loader les codes et définitions qui sont dans ce fichier. C'est en quelque chose la ligne la plus importante!
int main(void) {
		//On doit spécifier que la suite sera "[et maintenant,] votre programme principal" (c'est une joke de VHS/dvd). En gros, tout ce qui est à l'intérieur de la fonction "main" sera automatiquement exécuté en tant que programme. 
		//Tout ce qui vient avant ce "main" pourra servir à setter des valeurs ou initialiser des objets, mais jamais à interagir avec la console. Et tout ce qui vient après... ne sert à rien?
		
	//Créer l'objet où tout est initié
			//J'ai créé un classe d'objet (nommée "univers") qui contient tout ce que j'ai besoin pour fonctionner. Ici, je crée un objet ("u") de cette classe ("univers"), qui sera initialisé avec les paramètres du "constructeur par défaut" (défini à l'intérieur de la classe "univers"). Bref. 
	univers u;

	//Ouvrir une fenêtre de bonnes dimensions et initialiser les objets de sauvegarde
			//C'est une version de la fonction "MettreDansLeMain" qui ne prend aucun argument en entrée, et qui utilise les valeurs par défaut qui lui sont programmées.
			//À remarquer: cette fonction, comme toutes les suivantes, est précédée de "u."; cela veut dire que cette fonction est "membre de l'objet 'u' ". 
			//	En bref, c'est le truc que j'ai trouvé pour avoir à fournir le moins de paramètres, et que ce soit le moins long à écrire possible.
	u.MettreDansLeMain();
	
//-----------------------------------------------------------------|      Bibliothèque       |--------------------------------------------------------------------------------\\
		//La bibliothèque est le lieux où la plupart des valeurs (toujours numériques (des nombres entiers, en fait), BTW) utiles à la progression (genre à savoir où on est rendue) sont stockées.
		//Elle est organisé ainsi: chaque nombre est stocké en tant que "livre", et les multiples livres sont regroupés à l'intérieur de "rayons".
		//Cette hiérarchie à deux niveau (niveau le + petit: livre, niveau le + grand: rayon) a été choisie à la fois pour imposer un peu d'ordre dans la création des compteurs, 
		//   et à la fois pour optimiser le temps de recherche (c'est moins long de rechercher un rayon à travers 8 choix, puis un livre à travers 20 choix, qu'un seul livre à travers une pile de 400 choix).

	u.nvrayon("intro");					//Ici, je crée le premier rayon, que j'intitule "intro" (il sert à coordonner tout ce qui se passe avant que le contrôle soit donné à la joueuse - la mise en contexte, en quelque sorte).
		u.nvlivre("desuet");			//Ici, je crée le premier livre du rayon actuel 
		u.nvlivre("je");				//...deuxième livre...
		u.nvlivre("sara");
		u.nvlivre("tuto");
	u.nvrayon("cloture");				//...deuxième rayon...
		u.nvlivre("desuet");			//...premier livre du rayon actuel, donc premier livre du deuxième rayon...
		u.nvlivre("je");
		u.nvlivre("sara");
		u.nvlivre("choix");
		u.nvlivre("continuer");
		u.nvlivre("franchir");
		u.nvlivre("grimper");
		u.nvlivre("courage");	
		
			//Tous ces noms vont avoir plus de sens par la suite...
			//BTW, la valeur numérique attachée à chaque "livre" est de 0. Fait que tous les "livres" commencent avec une valeur de 0.
			
//-----------------------------------------------------------------|       Introduction      |--------------------------------------------------------------------------------\\		

	//Créer un canal
			//Le texte s'affiche principalement via des "canaux". Il s'agit simplement d'objets qui stockent le texte envoyé par les motifs, et l'écrivent dans la console progressivement.
			//Je crée ici deux canaux: un pour la narration ("je"), et un pour les paroles de ta compagne d'aventures, Sara. Sara pourra ainsi parler en même temps que la narration explique quelque chose!
			//Pour chaque canaux, je précise un délai (en millisecondes). Il s'agit du temps à attendre entre chaque lettre (plus c'est petit, plus le texte défile vite!).
	u.nvcanal("je"); u.canaldelai(80); 
			//Je donne un alinéa au canal de Sara (par défaut, il n'y en a pas). Ainsi, tout ce qu'elle dit va être en retrait de 6 espaces du bord gauche de la fenêtre. Ça va permettre de mieux différencier les voix.
			//Je lui fournis aussi une terminaison (y'en a pas par défaut). Il s'agit simplement de c'qu'elle va dire si on lui coupe la parole subitement (si on doit effacer tout ce qu'il lui restait à dire, parce que ça n'a plus rapport).
			//Ici, la terminaison spécifiée (BTW, on pourra la changer par la suite - plus tard) permet de simplement fermer ses guillemets de dialogue, pour faire plus propre.
	u.nvcanal("sara"); u.canaldelai(130); u.canalalinea(6); u.canalterminaison("\"");		
		
		
	//Débuter un chapitre pour l'introduction (où t'as pas de choix à faire, tu fais juste lire la mise en contexte)
			//Comme les rayons de la bibliothèque, les chapitres sont un moyen de mieux organiser les fictions, puis d'optimiser la recherche.
	u.nvchapt();
		u.ccond("intro¶desuet==0");        //Hou, on rentre dans le croquant! Une ligne qui n'est pas du tout évidente! 

			u.nvauto(); u.acanal("je");	    
			u.acond("intro¶je==1");	
			u.atexte("\npileµ\nface");	
			u.aordre("1;2");
			u.adeb("§bintro¶je~>0§§p1200§");
			u.afin("§bintro¶je~>2§");					
					
			u.nvauto(); u.acanal("je");	    
			u.acond("intro¶je==2");	
			u.atexte("\npileµ\nface");	
			u.aordre("1;2");
			u.adeb("§bintro¶je~>0§§p1200§");
			u.afin("§bintro¶je~>1§");
			
			u.nvmanu("stop"); u.mcanal("je");
			u.mcond("intro¶je!=3");	
			u.mcomm("stop");
			u.mcommexact("stop");
			u.mtexte("\n J'arrête de lancer automatiquement. C'est à toi de le faire.");	
			u.mdeb(""); u.mover();
			u.mfin("§bintro¶je~>3§");					
					
			u.nvmanu("lancer"); u.mcanal("je");	    
			u.mcond("intro¶je==3");	
			u.mcomm("lancer|tirer");
			u.mcommexact("lancer|tirer");
			u.mtexte("\npileµ\nface");	
			u.mordre("1;2");
			u.mdeb("");
			u.mfin("");			
	
	//Enclencher le premier motif (oui, j'fais ça manuellement pour garder l'uniformité dans mes enclenchements)
	u.biblio.modif("intro","je",1);
	//Vérifier une toute première fois la disponibilité des motifs automatiques
	u.AutoInterpret();
	//Faire une boucle pour que les canaux s'expriment!
	u.jouer();				
	curspos(u.cons,0,13);			//Mettre le curseur dans un bel endroit à la fin


}		
