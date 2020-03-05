/*
			///||================================---2020/01/18---================================||\\\
\\\||================================---Tutoriel / D�mo du potentiel interactif / narratif---================================||///
*/

//-----------------------------------------------------------------|  Explication de la base |--------------------------------------------------------------------------------\\

		//J'explique ici le coeur de ma fa�on d'�crire des "fictions interactives" (ou "aventures narratives" ou "text adventure", etc.)
			//Chaque histoire (interactive) sera compos�e de petites unit�s, qui comprennent � la fois le texte � lire et les conditions dans lequel ce texte sera lu.
			//J'appelle ici ces unit�s des "motifs".
			//Le principe � la base de cette id�e de cr�ation "interactive" est que ces motifs pourront s'encha�ner, se croiser, se superposer � leur guise, dans un ordre pas forc�ment lin�aire, dans l'ordre d�cid� par les actions de la joueuse.

		//Afin d'organiser efficacement cette collection de motifs, je les regroupe en "chapitres".
		
		//J'utilise deux types de "motifs" : les motifs "automatiques" et les motifs "manuels".
			//Les motifs automatiques n'attendent que les conditions propices pour d�verser leur texte dans la fen�tre de jeu.
			//Les motifs manuels, quant � eux, sont ex�cut� quand les conditions propices sont r�unies ET seulement si la bonne commande les appelle.
				//C'est par les motifs manuels que la joueuse pourra influencer le cours de l'histoire, en appelant certaines actions plut�t que d'autres, ou plut�t qu'une inaction.

		//Pour conserver l'information relative � la progression du jeu, et � quelle condition est remplie au moment pr�sent, j'utilise la biblioth�que (introduite plus haut).

		//Pour interagir avec le syst�me de jeu (supprimer un dialogue d�j� int�gr� mais devenu caduque, noter la progression, changer la vitesse, etc.), j'utilise seulement le texte � lire.
			//� l'int�rieur de ce "texte � lire", je vais donc cacher des "codes sp�ciaux".
				//Un "code sp�cial", c'est simplement quelque chose qui n'appara�tra pas � l'�cran, mais dont la "lecture" enclenchera une action quelconque (une interaction avec le syst�me de jeu).
			//Pour marquer un "code sp�cial", j'utilise le symbole '�' (qui est un caract�re que j'ai jug� que je n'utiliserai jamais dans le texte que je veux voir affich� � l'�cran).
				//Un code sp�cial sera donc un bout de texte entour� de '�' (� la mani�re de parenth�ses ou d'accolades)
				//La deuxi�me lettre du code (la premi�re �tant '�') indiquera l'action � effectuer et la fa�on dont on doit lire le reste du code sp�cial. 
					//Par exemple, "�p1000�" signifie "prendre une pause de 1000 millisecondes dans la lecture". En gros: attendre une seconde.
					//Un exemple b�te : "Je suis due pour une pause.�p2000� Merci!" sera lu comme : "Je suis due pour une pause." - pause de 2 secondes - " Merci!"
					
			
//-----------------------------------------------------------------|  Pr�paration technique  |--------------------------------------------------------------------------------\\
 
# include "C:/Users/Cyrille/Desktop/fictions_interactives_cplusplus/cadre_fonctionnel_global.cpp"
		//On a besoin de loader les codes et d�finitions qui sont dans ce fichier. C'est en quelque chose la ligne la plus importante!
int main(void) {
		//On doit sp�cifier que la suite sera "[et maintenant,] votre programme principal" (c'est une joke de VHS/dvd). En gros, tout ce qui est � l'int�rieur de la fonction "main" sera automatiquement ex�cut� en tant que programme. 
		//Tout ce qui vient avant ce "main" pourra servir � setter des valeurs ou initialiser des objets, mais jamais � interagir avec la console. Et tout ce qui vient apr�s... ne sert � rien?
		
	//Cr�er l'objet o� tout est initi�
			//J'ai cr�� un classe d'objet (nomm�e "univers") qui contient tout ce que j'ai besoin pour fonctionner. Ici, je cr�e un objet ("u") de cette classe ("univers"), qui sera initialis� avec les param�tres du "constructeur par d�faut" (d�fini � l'int�rieur de la classe "univers"). Bref. 
	univers u;

	//Ouvrir une fen�tre de bonnes dimensions et initialiser les objets de sauvegarde
			//C'est une version de la fonction "MettreDansLeMain" qui ne prend aucun argument en entr�e, et qui utilise les valeurs par d�faut qui lui sont programm�es.
			//� remarquer: cette fonction, comme toutes les suivantes, est pr�c�d�e de "u."; cela veut dire que cette fonction est "membre de l'objet 'u' ". 
			//	En bref, c'est le truc que j'ai trouv� pour avoir � fournir le moins de param�tres, et que ce soit le moins long � �crire possible.
	u.MettreDansLeMain();
	
//-----------------------------------------------------------------|      Biblioth�que       |--------------------------------------------------------------------------------\\
		//La biblioth�que est le lieux o� la plupart des valeurs (toujours num�riques (des nombres entiers, en fait), BTW) utiles � la progression (genre � savoir o� on est rendue) sont stock�es.
		//Elle est organis� ainsi: chaque nombre est stock� en tant que "livre", et les multiples livres sont regroup�s � l'int�rieur de "rayons".
		//Cette hi�rarchie � deux niveau (niveau le + petit: livre, niveau le + grand: rayon) a �t� choisie � la fois pour imposer un peu d'ordre dans la cr�ation des compteurs, 
		//   et � la fois pour optimiser le temps de recherche (c'est moins long de rechercher un rayon � travers 8 choix, puis un livre � travers 20 choix, qu'un seul livre � travers une pile de 400 choix).

	u.nvrayon("intro");					//Ici, je cr�e le premier rayon, que j'intitule "intro" (il sert � coordonner tout ce qui se passe avant que le contr�le soit donn� � la joueuse - la mise en contexte, en quelque sorte).
		u.nvlivre("desuet");			//Ici, je cr�e le premier livre du rayon actuel 
		u.nvlivre("je");				//...deuxi�me livre...
		u.nvlivre("sara");
		u.nvlivre("tuto");
	u.nvrayon("cloture");				//...deuxi�me rayon...
		u.nvlivre("desuet");			//...premier livre du rayon actuel, donc premier livre du deuxi�me rayon...
		u.nvlivre("je");
		u.nvlivre("sara");
		u.nvlivre("choix");
		u.nvlivre("continuer");
		u.nvlivre("franchir");
		u.nvlivre("grimper");
		u.nvlivre("courage");	
		
			//Tous ces noms vont avoir plus de sens par la suite...
			//BTW, la valeur num�rique attach�e � chaque "livre" est de 0. Fait que tous les "livres" commencent avec une valeur de 0.
			
//-----------------------------------------------------------------|       Introduction      |--------------------------------------------------------------------------------\\		

	//Cr�er un canal
			//Le texte s'affiche principalement via des "canaux". Il s'agit simplement d'objets qui stockent le texte envoy� par les motifs, et l'�crivent dans la console progressivement.
			//Je cr�e ici deux canaux: un pour la narration ("je"), et un pour les paroles de ta compagne d'aventures, Sara. Sara pourra ainsi parler en m�me temps que la narration explique quelque chose!
			//Pour chaque canaux, je pr�cise un d�lai (en millisecondes). Il s'agit du temps � attendre entre chaque lettre (plus c'est petit, plus le texte d�file vite!).
	u.nvcanal("je"); u.canaldelai(80); 
			//Je donne un alin�a au canal de Sara (par d�faut, il n'y en a pas). Ainsi, tout ce qu'elle dit va �tre en retrait de 6 espaces du bord gauche de la fen�tre. �a va permettre de mieux diff�rencier les voix.
			//Je lui fournis aussi une terminaison (y'en a pas par d�faut). Il s'agit simplement de c'qu'elle va dire si on lui coupe la parole subitement (si on doit effacer tout ce qu'il lui restait � dire, parce que �a n'a plus rapport).
			//Ici, la terminaison sp�cifi�e (BTW, on pourra la changer par la suite - plus tard) permet de simplement fermer ses guillemets de dialogue, pour faire plus propre.
	u.nvcanal("sara"); u.canaldelai(130); u.canalalinea(6); u.canalterminaison("\"");		
		
		
	//D�buter un chapitre pour l'introduction (o� t'as pas de choix � faire, tu fais juste lire la mise en contexte)
			//Comme les rayons de la biblioth�que, les chapitres sont un moyen de mieux organiser les fictions, puis d'optimiser la recherche.
	u.nvchapt();
		u.ccond("intro�desuet==0");        //Hou, on rentre dans le croquant! Une ligne qui n'est pas du tout �vidente! 

			u.nvauto(); u.acanal("je");	    
			u.acond("intro�je==1");	
			u.atexte("\npile�\nface");	
			u.aordre("1;2");
			u.adeb("�bintro�je~>0��p1200�");
			u.afin("�bintro�je~>2�");					
					
			u.nvauto(); u.acanal("je");	    
			u.acond("intro�je==2");	
			u.atexte("\npile�\nface");	
			u.aordre("1;2");
			u.adeb("�bintro�je~>0��p1200�");
			u.afin("�bintro�je~>1�");
			
			u.nvmanu("stop"); u.mcanal("je");
			u.mcond("intro�je!=3");	
			u.mcomm("stop");
			u.mcommexact("stop");
			u.mtexte("\n J'arr�te de lancer automatiquement. C'est � toi de le faire.");	
			u.mdeb(""); u.mover();
			u.mfin("�bintro�je~>3�");					
					
			u.nvmanu("lancer"); u.mcanal("je");	    
			u.mcond("intro�je==3");	
			u.mcomm("lancer|tirer");
			u.mcommexact("lancer|tirer");
			u.mtexte("\npile�\nface");	
			u.mordre("1;2");
			u.mdeb("");
			u.mfin("");			
	
	//Enclencher le premier motif (oui, j'fais �a manuellement pour garder l'uniformit� dans mes enclenchements)
	u.biblio.modif("intro","je",1);
	//V�rifier une toute premi�re fois la disponibilit� des motifs automatiques
	u.AutoInterpret();
	//Faire une boucle pour que les canaux s'expriment!
	u.jouer();				
	curspos(u.cons,0,13);			//Mettre le curseur dans un bel endroit � la fin


}		
