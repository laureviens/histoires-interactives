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
				//Cette ligne sert � d�finir les conditions sous lesquelles ce chapitre sera valide (les moments dans lesquels on pourra en puiser du texte).
				//Pour faire �a, on utilise les livres de la biblioth�que!
				//On peut reconna�tre qu'on recherche le rayon "intro", et qu'� l'int�rieur de ce rayon, on veut le livre "desuet". 
				//COMME POUR TOUTE R�F�RENCE � LA BIBLIO, le rayon est s�par� du livre par le symbole '�' (BTW, garde en t�te de ne pas mettre d'espaces de chaque c�t�. C'est pas "intro � desuet", c'est "intro�desuet").
				//Ici, la condition veut simplement que ce livre ("desuet", situ� dans le rayon "intro") soit �gal � 0 (qui est la valeur par d�faut de tous les livres).
				//Si l'on remplit cette condition, on pourra p�cher du texte des motifs pr�sents dans ce premier chapitre.
				
				
			//Introduire notre premier motif
					//Houuu!! L� �a devient s�rieux!
					//Il s'agit d'un motif automatique (pour bien le diff�rencier, on voit que toutes les fonctions qui le modifie commencent par un 'a'), qui lancera le texte qu'il contient dans la console d�s que sa condition d'activation sera remplie.
			u.nvauto(); u.acanal("je");	    
					//On cr�e le nouveau "motif" (c'est l� o� on conserve le texte qu'on va ajouter progressivement aux canaux). Et puis on l'assigne � un canal: ici, ce sera "je", qui correspond � la narration.    	
			u.acond("intro�je==1");	
					//Comme pour le chapitre, chaque motif doit avoir une condition d'activation. Ici, le "je", situ� � l'int�rieur de "intro", doit �tre �gal � 1 (et il le sera au d�but du programme). 
			u.atexte("\n\nT'as froid aux joues.�p1400�"
			"\n�d0�                     �d80�Pis aux cuisses.");	
					//Beaucoup de nouvelles choses ici!!!
					//First, "\n". Il s'agit du "code sp�cial" standard (standard � la plupart des langages de programmation) pour dire qu'on change de ligne.
						//Fait qu'� chaque fois qu'on inclut "\n" dans notre texte, on va sauter une ligne � l'�cran rendue l�.
						//Ici, "\n\n" fait qu'on va sauter deux lignes avant de commencer � d�clamer le texte.
					//Deuxi�mement: Un code sp�cial! 
						//Un code sp�cial est : n'importe quoi qui est entour� de '�', et qui effectue une action pr�cise sur le syst�me de jeu.
						//La deuxi�me lettre du code (apr�s le premier '�') va servir � dire de quel type le code sp�cial est (en gros: qu'est-ce qu'il fait).
						//Ici, on en a deux types: "�p�"  et  "�d�".
							//"�p�" ('p' pour pause) sert � prendre une pause dans la lecture, une pause dont la longueur est transmise en millisecondes.
								//En lisant "�p1400�", le canal "je" va arr�ter d'afficher son texte pendant 1,4 secondes, pui recommencer.
							//"�d�" ('d' pour d�lai) sert � modifier le d�lai (le temps � attendre) entre chaque lettre.
								//En d�finissant le canal "je", on lui avait donn� un d�lai de 80 millisecondes : le canal va sortir une nouvelle lettre � toutes les 0.08 secondes.
								//Ici, j'utilise simplement un p'tit truc pour tasser le texte � gauche:
									//a) changer de ligne; b) mettre un d�lai de 0 seconde (lire le texte � la vitesse de l'�clair); c) remettre le d�lai normal quand on a assez inscrit d'espace (quand le texte est assez tass�).
			u.adeb("�bintro�je~>0��p1200�");
					//Pour faciliter la lecture des codes importants, je s�pare le d�but et la fin du texte du reste.
					//Mais �a va faire partie du texte du motif, au final. Le voir comme     { deb + texte + fin } = le texte du motif au complet
								
					//Nouveau code sp�cial qui s'introduit!
						//"�b�" ('b' pour biblioth�que) sert � modifier les valeurs stock�es dans la biblioth�que (donc, agir sur quel motif pr�sente les conditions n�cessaires pour s'activer)
						//Apr�s le 'b', on va avoir "le nom du rayon de la biblioth�que o� on veut modifier un livre" ("intro"), '�', "le nom du livre qu'on veut modifier" ("sara"), "le symbole de modification" ("~>"), puis "la valeur qu'on veut donner au livre" ("1").
						//Ici, ce code sp�cial va permettre de d�sactiver le motif actuel (sa condition �tait "intro�je==0") (et oui, un m�me motif peut �tre activ� plus d'une fois!).
			u.afin("�bintro�sara~>1�");
					//Ici, � la fin du texte, on met en place la valeur qui va permettre au prochain motif de s'activer (le prochain motif, �a va �tre Sara qui parle)!
					

			//Deuxi�me motif: Message de directives du d�but (temporaire?)
			u.nvauto(); u.acanal("msn");
					//Nouveau concept: un msn
						//En gros, j'voulais avoir la possibilit� d'inscrire un message temporaire, qui s'inscrit puis qui s'efface (avec un visuel cool).
						//Fait que j'ai cr�� une nouvelle classe de "canaux", que j'ai nomm� "msn".
						//Puisque les "msn" sont temporaires, il ne faut pas les cr�er au d�but : on en cr�e un nouveau � chaque fois qu'un motif ayant comme canal "msn" s'active.
			u.acond("intro�je==1");
			u.afin("�p2600��f0�");
					//Nouveau code sp�cial!
						//"�f�" ('f' pour FREEZE) sert � mettre en pause tous les autres canaux (et messageries), pour n'avoir que celui qui l'a inscrit qui est actif.
							//"�f1�" (qui est pr�sent au milieu du mot "quitter", dans le texte du motif) sert � "freezer", tandis que "�f0�" sert � "d�-freezer".
			u.atexte("�p4000�Pour qui�f1�tter le programme,�p400� appuie sur �p210�[ESC�p110�].�p1200�"
			"\nPour modifier la vitesse de d�filement,�p600� appuie sur les touches �p90�[HAUT�p100�] et �p140�[BAS�p90�] (possiblement plusieurs fois).");
				
				
				
				
						//C'est weird, y'a encore la premi�re lettre qui appara�t toute seule avant le reste?
								//Si je voulais r�gler ce probl�me de mani�re absolument pas correcte, je pourrais mettre ' ' comme premi�re lettre...
									
							//Non, s�rieux, faudrait que j'investigue ce probl�me.
				
				
				
				
			//La harangue de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�sara==1");	
			u.adeb("�bintro�sara~>0��s�");
					//Nouveau code sp�cial!
						//�s� ('s' pour skip) sert � placer le canal dans le bas du texte qui s'affiche (skipper la file!) : �a permet de le mettre � l'avant-sc�ne, drette sous les projecteurs. 
			u.afin("�bintro�je~>2�");
			u.atexte("�p1800�\n\"Come on,�p1100�"
			"\n�d0�          �d130�on est presqu'arriv�es!\"");
					//Nouveau "code sp�cial standard"
						//    \"     , �a l� (j'peux pas l'entourer de guillemets en gardant �a clair), �a fait qu'un guillemet (") s'affiche � l'�cran.
						//C'est parce que sinon, un guillement tout seul signifie "d�but/fin de la zone de texte". Fait que pour rester dans la zone de texte pis afficher un guillement � l'�cran, on utilise \" .

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro�je==2");	
			u.adeb("�bintro�je~>0��s�");
			u.afin("�bintro�sara~>2�");
			u.atexte("�p400�\n\n         T'acc�l�res le pas,�p600� moins pour la rejoindre�p100� que pour r�chauffer tes jambes.�p1200��d110� Le vent,�p500� criss.�p700� Le vent.�p1600�"
			"\n�d90�Tu l�ves les yeux�p100� juste � la limite de ton capuchon�p300� pis Sara est quand m�me loin en avant.�p1400��d80� Tu te presses un peu plus.�p2800�"
			"\n\nTraverses une rue,�p400� t'es au coin de la cath�drale�p300� pis le vent charge de plus belle depuis ta droite.�p2400� Caliss.�p3000��d90� Sara est d�j� rendue plus bas,�p500� a'longe la grosse chapelle.�p2300�"
			"\n�d0�                       �d80�Tu descends au jogging�p120�, �p400�"
			"\n�d0�                                                �d80�rejoindre au plus vite l'�norme pare-vent de pierre.�p1800�"
			"\nTa jupe virevolte sur tes genoux,�p200� expose tes cuisses aux rafales;�p2300� Pas l'meilleur choix de v�tements.�p4300�"
			"\n\n     La cath�drale coupe le vent�p150� pour vrai.�3100� "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.�p2200�");

			//La r�ponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�sara==2");	
			u.adeb("�bintro�sara~>0��s�");
			u.afin("�bintro�je~>3�");
			u.atexte("�p130��d110�\n\"J'te l'dis,�p260� t'as vraiment h�te d'�tre rendue su'l'to�t du Granada!\"");			//FAUDRAIT CHANGER CETTE PHRASE POUR QUELQUE CHOSE DE PLUS CR�DIBLE

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro�je==3");	
			u.adeb("�bintro�je~>0��s�");
			u.afin("�bintro�sara~>3�");
			u.atexte("�p3100�Tu peux pas emp�cher tes commissures engourdies de remonter un peu.�p2600�"
			"\n\n�d90�Encore quelques pas ensemble et vous �tes � l'arri�re d'la maison de Dieu�p140� pis l'vent reprend.�p560��100� Vraiment une belle soir�e pour �tre sur l'top d'une colline.�2600�"
			"\n\n�d90�Sara te tra�ne encore plus derri�re l'�glise,�p220� dans une all�e s�par�e de la rue par un p'tit muret.�p1800� � ta gauche,�p160� tu peux voir le frimas sur les toits plats des buildings adjacents,�p240� pis les lumi�res de la ville,�p130� de l'autre c�t� d'la rivi�re.�p2000� Vous �tes pas mal haut,�p180� finalement.�p3000�"
			"\nTu continues et un long b�timent de briques s'�rige entre le bord de la falaise et vous,�p110� coupe le paysage.�p900� �a donne moins le vertige.�p2500�"
			"\n�d0�               �d90�Tu te demandes si c'est ill�gal de grimper sur les toits des b�timents la nuit.�p1200�"  
			"�d100�\n\nApr�s la b�tisse,�p300� votre all�e remonte � gauche vers un l�ger promontoir asphalt�.�p1100�"
			"\nUltime place de parking avant le pr�cipice.�p2300�"
			"\nLe stationnement garde le b�timent de briques � sa gauche;�p330� et une ligne jaune comme limite � droite,�p540� m�me si le bord du pr�cipice donne aussi une d�limitation pas mal claire.�p2000� Y'a des \"�p120�butoirs\"�p70� en b�ton � droite et au devant de l'emplacement,�p140� tout le long de la peinture jaune.�p2600� � l'avant, c'est boucl� par une cl�ture haute de 3 ou 4 m�tres,�p230� qui emp�che fermement l'acc�s aux toits adjacents,�p400� barbel�s et tout.�p2400�"
			"�d85�\nCl�ture sur laquelle les �paules de Sara sont accot�es,�p140� ses deux pieds repouss�s contre le bump en b�ton.�p1500� Les bras crois�s,�p400� un sourire qui sussure"
			"\n�d0�                          �d100�\"C'est par l� qu'on passe\".�p3000�");

			//L'explication de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�sara==3");	
			u.adeb("�bintro�sara~>0��s�");
			u.afin("");
			u.atexte("�p1600��d100�\n\"Fait qu'on a juste � monter la cl�ture,�bintro�je~>4��p300� l�,�p2900�"
			"\npis apr�s on va vraiment jusqu'au coin,�p400� jusqu'� l'autre cl�ture bizarre,�p200� la genre de grille qui pend.�p1200� Pis elle,�p90� on la monte�p270� - tu vas voir c'est pas tough - �p5200� pis 'y reste juste � r'descendre pis on est sur les to�ts.\"");
					//BTW: ici, on dit � un motif de l'autre canal (le prochain) de commencer � s'activer PENDANT que le texte de celui-ci d�file. �a fait que tout le monde parle en m�me temps. Effet int�ressant.
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la tienne
			u.nvauto(); u.acanal("je");		
			u.acond("intro�je==4");	
			u.adeb("�bintro�je~>0��s�");
			u.afin("�bintro�je~>5�");
			u.atexte("�d80�\n\nElle se redresse et pose la main � plat sur le grillage en losanges�p540� avant de pointer l'extr�mit� en haut � droite,�p420� avance d'un pas en bougeant de haut en bas avec ses deux bras,�p2800� te regarde dans les yeux,�p1200� fait un tour sur elle-m�me en crispant les dents avec ses doigts solidement accroch�s � son imagination,�p100��d90� et fait semblant d'atterir sur ses deux pieds,�d110� finalement.�p4500�"
			"�d100�\n\n\nElle te sourit,�300� l'air fi�re de son explication.�p2000�"
			"�d110�\nTu clignes des paupi�res�p800� une fois.�p2900�"
			"�d100�\n\n\nLa t�te te soupire�p110� et t'avances pour constater le chemin toi-m�me.�p2100�"
			"\n\nAu devant, la grande barri�re de grillage en losanges�p90� a son top en barbel�s,�p390� dress�s en angle contre votre direction.�p900� �d120�Fait que d�finitivement pas par l�.�p2300�"
			"�d150�\n\n� droite,�p500��d130� par contre,�p430��d110� le grillage finit juste avant la falaise,�p290� et une esp�ce de grille � gros barreaux verticaux prolonge la cl�ture au-dessus du pr�cipice,�p600��d100� probablement pour nous emp�cher de juste tourner le coin.�p1800�"
			"�d120�\n\nMais la grille,�p180� qui fait juste chiller au-ds'us du vide,�p440� elle,�p580� elle a pas de barbel�s.�p400�.�p320�.�p3200�"
			"�d160� Fait que par l�.�p3800�");
	
			//Tu doutes de tes capacit�s, pour avoir une excuse pour commencer � int�grer les commandes manuelles
			u.nvauto(); u.acanal("je");		
			u.acond("intro�je==5");	
			u.adeb("�bintro�je~>0�");
			u.afin("�bintro�tuto~>1�");			
			u.atexte("�d90�\n\n\n\nTes yeux se ferment bri�vement,�p430� une seconde fois.�p1500�"
			"�d300�\n\n\n�d0�                  �d200�DANGEREUX.�p1600�"
			"�d100�\n\n\nT'ouvres l'oeil sur tes pieds,�p300� au sol,�p430��d120� l'autre oeil,�p520�"
			"\n�d0�                �d100�t'es debout sur l'asphalte,�p460� les orteils � peine sur la ligne jaune du devant du parking,�320� juste avant le bump de b�ton.�p1300�"
			"�d90�\n\nSara est rendue l'autre bord de la cl�ture�p130�,�p220� d�j� pass�e par-dessus la grille,�p180� agripp�e�p110� l�g�re encore dans le haut de la barri�re,�p330� accroch�e.�p2600�"
			"\n\n\n�d180�Tu ...�p820�,�p1240��d120�        ...tu penses pas�p210��d130� �tre capable�d140� de faire�p140��d160� �a�p300�?�p2600�");

			//La voix du tutoriel qui te parle
			u.nvauto(); u.acanal("msn");		
			u.acond("intro�tuto==1");	
			u.adeb("�bintro�tuto~>0�");
			u.afin("�f0��bintro�tuto~>2�");			
			u.atexte("                           C'est main�f1�tenant � toi de guider [t]es actes.�p1000� �cris la commande que tu souhaites effectuer,�p610� puis appuie sur �p120�[ENTER�p90�].�p2200�");

			//Les mille et une suggestions d'actions � faire
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin("�bintro�desuet~>1��bcloture�choix~>1�"); u.atexte("�p7130�Avancer�p1100�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p8840�Franchir la ligne�p2000�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p9270�Continuer�p800�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p11600�Monter dans le grillage�p1400�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p12310��tre capable de grimper�p1800�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p13530�Poursuivre�p2300�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p16020�Aller de l'avant�p1600�");			
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p16250�Rassembler son courage�p1800�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p18510�Monter sur les toits�p3800�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p19750�Surmonter sa peur�p2200�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p22670�Franchir la ligne jaune�p3000�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin(""); u.atexte("�p25830�Rejoindre Sara�p1800�");
			u.nvauto(); u.acanal("msn"); u.acond("intro�tuto==2"); u.afin("�bcloture�sara~>1�"); u.atexte("�p26930�Avancer jusqu'� la cl�ture�p2100�");


				//Pis... je crois que le code bug quand y'a plus de msn qui veulent s'inscrire que la limite impos�e???
							//Faudrait v�rifier �a!!!
							
//-----------------------------------------------------------------|   Traverser la cl�ture  |--------------------------------------------------------------------------------\\
							
	//D�buter un chapitre dont le but sera de passer par-dessus la cl�ture
	u.nvchapt();
		u.ccond("intro�desuet&!cloture�desuet");        //Rendre le premier chapitre accessible seulement quand t'as pas encore travers� + quand ce n'est plus l'intro													
						//Premi�re condition compos�e!
							//Le symbole '&' signifie que les deux conditions doivent �tre � LA FOIS remplie pour que le motif soit activ�. �a veut dire "ET".
							//Si on voit '|', au contraire, �a signifie qu'une ou l'autre des conditions doivent �tre remplies, ou encore les deux � la fois. '|' signifie "OU".
						//J'utilise aussi de b�tes raccourcis d'expression logique: 
							//"intro�desuet" tout seul signifie que "intro�desuet" est �gal � n'importe quoi sauf 0.  
								//J'aurais aussi pu l'�crire "intro�desuet!=0", car l'op�rateur "!=" signifie "pas �gal �".
							//et "!cloture�desuet" signifie que "cloture�desuet" n'est pas �gal � "n'importe quoi sauf 0". Donc est �gal � 0. Donc "cloture�desuet==0", dans le fond.
					
			//Sara te rassures
			u.nvauto(); u.acanal("sara");					//Le texte est parsem� de "�r�". Ce code sp�cial permet d'int�grer le motif manuel qui �tait en r�serve au bon moment.						
			u.acond("cloture�sara==1");						//Cette m�canique est utilis�e afin de ne pas interrompre une phrase n'importe quand par la r�ception d'une commande.
			u.adeb("�bcloture�sara~>0��s��p4000�");
			u.afin("\n\n\nC'EST LA FINNNNNN");			
			u.atexte("�d100�\n\n\n\n\n\"Tu vois�r��p3400��r� c'est vraiment simple�r��p1400��r�,�p4120��r� c'est juste la partie o� tu changes de bord �r��2300�qui�p2000� est un peu tricky�r�,�p6130��r� mais sinon y'a vraiment pas � s'inqui�ter�r�,�p4700��r� tu vas voir �a va full bien s'passer�r��p3100��r�,�p4810��r� pis j'suis l� si y'a d'quoi.\"�r��p5600��r�"	
			"�p4000��r�\n\n\"�d110�Ok�r�,�p2430��r� fais juste avancer lentement�r�,�p4020��r� une fois que t'es dedans�p1400� �a se fait tu seul.�r��p5850��r� S�rieux.�r��p4570��r��p3000��r��p3300��r�"
					//Y'a vraiment un changement de ton, ici... Est-ce que j'veux garder �a?
			"\n�d0�          �d90�ok fais juste bouger,�p1830� au moins�r�,�p4650��r� avance jusqu'�' clot�re�r��p7560��r�,�p4630��r� envoyes�r�,�4470��r� y fait frette!�r��p4100��r�");
					//Continuer dans cette veine jusqu'� une d�cision finale de "tu", qui est de chocker pour de bon.
									
															
			//Choix: "continuer", "avancer"	et autres formulations vagues  (Premier motif manuel! Wouhou!)
			u.nvmanu("aller de l'avant"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(avancer|continuer&vers|en direction d|pour atteindre|jusqu'&cl�ture|grillage|barri�re|to�t)(rejoindre|aller � la rencontre de|atteindre|rattraper&Sara|amie|complice|partenaire|compagne)");		// ()() = deux fa�ons diff�rentes d'appeler cette commande
					//Un motif manuel a besoin de commandes pour �tre appel�!
						//Cette fonction d�finit quel mots-cl�s auront besoin d'�tre pr�sents (ou absent!) dans la commande entr�e par la joueuse pour que le motif manuel s'active.
						//Elle permet d'utiliser plusieurs fa�on de dire la commande (s�par�es par des parenth�ses) : ici, genre "avancer vers la cl�ture" ou genre "rejoindre Sara".
						//� l'int�rieur de chaque fa�on de dire la commande (donc � l'int�rieur de la parenth�se), on retrouve:
							//Des groupes de mots (s�par�s par '&'), qui doivent chacun �tre pr�sent pour que la commande soit valid�e : ici, "avancer|continuer", "vers|en direction d|pour atteindre|jusqu'" et "cl�ture|grillage|barri�re|to�t" sont des groupes de mots diff�rents
							//� l'int�rieur des groupes de mots, il y a:
								//Des synonymes (s�par�s par '|')! En gros, on a besoin d'avoir soit "Sara", soit "amie", soit "complice", soit "partenaire" ou soit "compagne" pour que le groupe de mot soit reconnu comme pr�sent.
							//Ils n'apparaissent pas ici, mais chaque fa�on de dire la commande peut aussi contenir des mots � �viter (mis entre crochets, et s�par�s par '|')!
					//Ici, autant "avancer en direction des to�ts", "continuer jusqu'au grillage" et "aller rejoindre ton amie" seront reconnues commes des commandes valides pour ce motif.
			u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
					//On peut �galement d�finir des commandes qui doivent �tre �crites mots pour mots pour �tre reconnues
						//�a permet, par exemple, d'�viter de valider des commandes "contraires" avec des mots-cl�s trop flous:
						//Par exemple, "avancer" va te faire avancer vers la cl�ture, mais pas "avancer vers la cath�drale" (si on avait mis ces synonymes comme autre fa�on de dire la commande, tout ce qui aurait contenu "avancer" aurait pass� comme bon).
			u.mdeb("�osara��bcloture�choix~>0��bcloture�continuer~>1��s��d120�"); 		//D�s que le motif est lu, on efface ce que Sarah avait � dire
					//Nouveau code sp�cial:
						//"�o�" ('o' pour overwrite) sert � effacer le texte du canal sp�cifi� (ici, "sara") pour arr�ter son affichage. En gros, on "coupe � parole" � Sara.
						//Pour �tre s�re de bien fermer �a propret, on place la terminaison du canal juste apr�s avoir tout effac�. Ici, �a permet de fermer son dialogue avec de derniers guillements (voir "u.canalterminaison()")
			u.mreserve();		//Lorsque ce motif sera appel� par une commande, il ne sera pas int�gr� tout de suite: il sera mis en r�serve. Il faudra attendre qu'un code sp�cial "�r�" soit lu par n'importe quel canal (ici, �a va arriver dans le dialogue de Sara).
			u.mfin("�bcloture�choix~>2�");
			u.mtexte("�d120�\n\nOuin,�p800� tant qu'� d�j� �tre rendue�p140�...�p1600��"				//Segment #1
			"�d140�\n\n\nNon,�p300� tu vas pas chocker ici.�p1130��d110� T'es meilleure que �a.�p1800���"		//Segment #2
			"\n\n\nTu tires ton capuchon vers l'arri�re en levant le menton,�p350�"		//Segment #3
			"\ny'est plus dans tes yeux maintenant.�p1420��"							//Segment #3 (encore)
			"\n\nUn grand respire,�p570� tu soul�ves tes yeux�p430� � hauteur de Sara.�1170� 'A te sourit,�p440� puis marmonne qu'ses mains sont gel�es.�p620��"		//Segment #4
			"�d90� Tu lances ta jambes en avant dans un grand pas,�230� par-dessus l'obstacle de b�ton pis tu mets tes mains sur la grille.�p1000�");			//Segment #5
					//Nouveau m�canisme!
						//Pour introduire de la vari�t� dans les phrases qui s'affichent, j'ai d�cid� que diff�rentes combinaisons de phrases semblables pourraient �tre s�lectionn�es.
						//Ici, je s�pare mon texte en plusieurs segments. Le s�parateur utilis� est '�' (comme '�', c'est un caract�re que j'suis s�re de ne pas utiliser sinon).
			u.mordre("1-3-5;1-4-5;2-3-5;2-4-5");		//Par d�faut, chaque combinaison a une chance �gale de se produire
					//Ici, je d�cide quelles seront les "combinaisons gagnantes" : celles qui pourront �tre s�lectionn�es pour �tre ajout� au canal "je".
					//Par exemple, ici, les segments #1 et #2 sont � peu pr�s synonymes, de m�me que les #3 et #4. Donc j'mets juste toutes les combinaisons diff�rentes.
	
				//Suite de "continuer" : faut demander explicitement de grimper (bout automatique qui l'explicite)
				u.nvauto(); u.acanal("je");
				u.acond("cloture�choix==2&cloture�continuer==1");
				u.adeb("�bcloture�choix~>2�"); 
				u.afin("�mgrimper maintenant�");
				u.atexte("�d80�\nOuin�r�,�p400� tu sais pas trop comment prendre �a�r�,�p510� finalement.�r��p820�    �r�Tu�p500�.�p420�..�r��p370� tu guess qu'il faut que t'escalades?�r��p1500��r��d130� T'ins�res tes doigts � l'int�rieur des fils losang�s.�r��p3520��r� Ben,�p410� d'ins trous d'la cl�ture,�p300� dans l'fond.�r��p4200��r�"
				"\n�a devrait �tre simple.�r��p3600��r� T'as juster � te hisser.�r��p4200��r� Te monter�p400��r�,�p520� avec un peu de force dans les bras�p300�.�r��p3500��r��p3600��r��p4020��r� Bon.�p760�");		//Le code sp�cial �m� est pour forcer l'ex�cution d'un motif manuel dont le nom correspond
			
				//Suite de "continuer" : faut demander explicitement de grimper (mais il se passe automatiquement si on attend assez longtemps)
				u.nvmanu("grimper maintenant"); u.mcanal("je");
				u.mcond("cloture�choix==2&cloture�continuer==1");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&cl�ture|grillage|barri�re|grille|to�t)(grimper|monter|escalader|se hisser)");
				u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
				u.mdeb(""); 
				u.mreserve(); u.mover();
				u.mfin("\n\n\nC'EST LA FINNNNNN");
				u.mtexte("�d80� Tu places tes mains plus haut,�p220� s�cures tes doigts�p100� pis tires�p200��d100� comme "
				"\n�d0�                     �d70�tes bottes glissent contre la cl�ture�p210�;�p330� tu r�ussis � avoir une pogne pour tes pieds.�p1100�"
				"�d90�\n\nNice,�p140� t'es d'ins airs.�p2300�");



			//Choix: "Franchir la ligne" ou autres formulation dramatiques/litt�rales (parce qu'il faut d'abord que t'enjambe la ligne de peinture jaune)
			u.nvmanu("franchir la ligne jaune"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(franchir|traverser|outrepasser|pi�tiner|fouler|marcher sur|passer|continuer outre&ligne|limite|trait|d�limitation|fronti�re)");
			u.mdeb("�osara��bcloture�choix~>0��bcloture�franchir~>1��s��d120�"); 
			u.mfin("\n\n\nC'EST LA FINNNNNN");
			u.mreserve();		//Lorsque ce motif sera appel� par une commande, il ne sera pas int�gr� tout de suite; il faudra attendre qu'un code sp�cial "�r�" soit atteint.
			u.mtexte("\n\n\nTU D�PASSES TES LIMITES JAUNES MAIS QUELLE M�TAPHORE");
						
			//Choix: "Grimper" ou autres
			u.nvmanu("grimper la cl�ture"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&cl�ture|grillage|barri�re|grille|to�t[�tre capable d|pouvoir|�tre en posture de|se forcer �|se motiver �])");		// [] = on ne les veut pas!
			u.mcommexact("grimper|escalader|se hisser");
			u.mdeb("�osara��bcloture�choix~>0��bcloture�grimper~>1��s��d120�"); 
			u.mfin("\n\n\nC'EST LA FINNNNNN");
			u.mreserve();		//Lorsque ce motif sera appel� par une commande, il ne sera pas int�gr� tout de suite; il faudra attendre qu'un code sp�cial "�r�" soit atteint.
			u.mtexte("\n\n\nTU GRIMPES LA CL�TURE BRAVO POUR TOI");
						
			//Choix: "Surmonter sa peur" / "Rassembler son courage" / "Prendre son courage � deux mains", etc.
			u.nvmanu("surmonter sa peur"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(�tre capable d|pouvoir|�tre en posture de|se forcer �|se motiver �&grimper|monter|escalader|agripper|se hisser|franchir&cl�ture|grillage|barri�re|grille|to�t)"
			"(�tre capable d|pouvoir|�tre en posture de|se forcer �|se motiver �&grimper|escalader|se hisser)");
			u.mcommexact("surmonter sa peur|prendre son courage � deux mains|se prendre en mains|rassembler son courage|�tre courageuse");
			u.mdeb("�osara��bcloture�choix~>0��bcloture�courage~>1��s��d120�"); 
			u.mreserve();		//Lorsque ce motif sera appel� par une commande, il ne sera pas int�gr� tout de suite; il faudra attendre qu'un code sp�cial "�r�" soit atteint.
			u.mfin("\n\n\nC'EST LA FINNNNNN");
			u.mtexte("\n\n\nTU RASSEMBLES TON COURAGE C'EST BEAU CHAMPIONNE");
						
													
			
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la biblioth�que pour suit my needs
		//u.biblio.modif("cloture","choix",1); u.biblio.modif("intro","desuet",1); u.biblio.modif("cloture","sara",1);
	
	
	//Enclencher le premier motif (oui, j'fais �a manuellement pour garder l'uniformit� dans mes enclenchements)
	u.biblio.modif("intro","je",1);
	//V�rifier une toute premi�re fois la disponibilit� des motifs automatiques
	u.AutoInterpret();
	//Faire une boucle pour que les canaux s'expriment!
	u.jouer();				
	curspos(u.cons,0,13);			//Mettre le curseur dans un bel endroit � la fin


}		
