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
		u.nvlivre("estucorrecte");	
		u.nvlivre("abandon");
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
			//Ici, la terminaison sp�cifi�e (BTW, on pourra la changer par la suite - plus tard) permet de simplement fermer ses guillemets de dialogue, apr�s une pt'ite pause, pour faire plus propre.
	u.nvcanal("sara"); u.canaldelai(130); u.canalalinea(6); u.canalterminaison("�p400�\"");		
		
		
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
			u.atexte("�p2200�Pou�f1�r quitter le programme,�p400� appuie sur �p210�[ESC�p110�].�p1200�"
			"\nPour modifier la vitesse de d�filement,�p600� appuie sur les touches �p90�[HAUT�p100�] et �p140�[BAS�p90�] (possiblement plusieurs fois).");
				
			//La harangue de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�sara==1");	
			u.adeb("�bintro�sara~>0��s�");
					//Nouveau code sp�cial!
						//�s� ('s' pour skip) sert � placer le canal dans le bas du texte qui s'affiche (skipper la file!) : �a permet de le mettre � l'avant-sc�ne, drette sous les projecteurs. 
			u.afin("�bintro�je~>2�\"");
					//Nouveau "code sp�cial standard"
						//    \"     , �a l� (j'peux pas l'entourer de guillemets en gardant �a clair), �a fait qu'un guillemet (") s'affiche � l'�cran.
						//C'est parce que sinon, un guillement tout seul signifie "d�but/fin de la zone de texte". Fait que pour rester dans la zone de texte pis afficher un guillement � l'�cran, on utilise \" .			
			u.atexte("�p1800�\n\"Come on,�p1100�"
			"\n�d0�          �d130�on est presqu�"			//Segment #1
			"e rendues!�"									//Segment #2
			"'arriv�es!");									//Segment #3
					//Nouveau m�canisme!
						//Pour introduire de la vari�t� dans les phrases qui s'affichent, j'ai d�cid� que diff�rentes combinaisons de phrases semblables pourraient �tre s�lectionn�es.
						//Ici, je s�pare mon texte en plusieurs segments. Le s�parateur utilis� est '�' (comme '�', c'est un caract�re que j'suis s�re de ne pas utiliser sinon).			
			u.aordre("1-2;1-3");			//Par d�faut, chaque combinaison a une probabilit� �gale de se produire; mais �a peut �tre chang� si on veut autrement.
					//Ici, je d�cide quelles seront les "combinaisons gagnantes" : celles qui pourront �tre s�lectionn�es pour �tre ajout� au canal "je".
					//Par exemple, ici, les segments #1 et #2 sont � peu pr�s synonymes, de m�me que les #3 et #4. Donc j'mets juste toutes les combinaisons diff�rentes.

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro�je==2");	
			u.adeb("�bintro�je~>0��s�");
			u.afin("�bintro�sara~>2�");
			u.atexte("�p400�\n\n         T'acc�l�res le pas,�p600� moins pour la rejoindre�p100� que pour r�chauffer tes jambes.�p1200��d110� Le vent,�p500� gode.�p700� Le vent transperce.�p1600�"
			"\n�d90�Tu l�ves les yeux�p100� juste � la limite de ton capuchon�p300� pis Sara est quand m�me loin en avant.�p1400��d80� Tu te presses un peu plus.�p2800�"
			"\n\nTraverses une rue,�p400� t'es au coin de la cath�drale�p300� pis le vent charge de plus belle depuis ta droite.�p2400� Caliss.�p3000��d90�"	//Segment #1
			"\nSara est d�j� rendue plus bas,�p500� 'a longe la grosse chapelle.�p2300��"	//Segment #2
			"\nTon amie est maintenant pas mal plus bas,�p500� aux pieds de l'imposante �glise.�p2000��"	//Segment #3			
			"\n�d0�                       �d80�Tu descends au jogging�p120�, �p400�"
			"\n�d0�                                                �d80�rejoindre au plus vite l'�norme pare-vent de pierre.�p1800��"			//Segment #4
			"\n\nTu t'actives pluss, question d'la rejoindre rapidement � l'abri du vent.�p1100��"												//Segment #5
			"\nTa jupe virevolte sur tes genoux,�p200� expose tes cuisses aux rafales;�p2300� Pas l'meilleur choix de v�tements.�p4300�"
			"\n\n     La cath�drale coupe le vent�p150� pour vrai.�3100� "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.�p2200�");													//Segment #6
			u.aordre("1-2-4-6;1-2-5-6;1-3-4-6;1-3-5-6");

			//La r�ponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro�sara==2");	
			u.adeb("�bintro�sara~>0��s��p130��d110�\n\"");
			u.afin("\"�bintro�je~>3�");
			u.atexte("J'te l'dis,�p260� t'as vraiment trop h�te d'�tre rendue su'l'to�t du Granada!�"		//Segment #1
			"L'acc�s aux to�ts est� "			//Segment #2
			"�d50�"								//Segment #3
			"juste�"							//Segment #4
			"-juste�"							//Segment #5
			"-juste�"							//Segment #6
			" � c�t�.�d100��"					//Segment #7
			"T'auras jamais vu une vue d'm�me, jur�!�"			//Segment #8
			"Tu tough encore genre trois m�tres pis on devient les roines du centro!");		//Segment #9
			u.aordre("1;2-3-4-5-7;2-3-4-5-6-7;2-3-4-5-7-8;2-3-4-5-7-9;2-4-7-9");

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
			u.atexte("�d80�\n\nElle se redresse et pose la main � plat sur le grillage en losanges�p540� avant de pointer l'extr�mit� en haut � droite,�p420� avance d'un pas en bougeant de haut en bas avec ses deux bras,�p2800� te regarde dans les yeux,�p1200� fait un tour sur elle-m�me en crispant les dents avec ses doigts solidement accroch�s � son imagination,�p100��d90� et fait semblant d'atterir sur ses deux pieds,�d110� finalement.�p4500��"		//#1
			"�d100�\n\n\nElle te sourit,�300� l'air fi�re de son explication.�p2000�"
			"�d110�\nTu clignes des paupi�res�p800� une fois.�p2900�"		
			"�d100�\n\n\nLa t�te te soupire�p110� et t'avances pour constater le chemin toi-m�me.�p2100��"		//#2
			"�d100�\n\n\nA' s'retourne,�400� prunelles p�tillantes d'encouragement.�p2000��"		
			"\nTu lui donne un sourire indulgent,�p900� et vas toi-m�me voir de quoi elle parlait.�p2100��"		//#3			
			"\n\nAu devant, la grande barri�re de grillage en losanges�p90� a son top en barbel�s,�p390� dress�s en angle contre votre direction.�p900� �d120�Fait que d�finitivement pas par l�.�p2300�"	//#4
			"\n\nOui,�p370� le devant du parking est flanqu� d'un haute cl�ture termin�e en barbel�e.�p1100� Gentil.�p1200��"	//#5
			"�d150�\n\n� droite,�p500��d130� par contre,�p430��d110� le grillage finit juste avant la falaise,�p290� et une esp�ce de grille � gros barreaux verticaux prolonge la cl�ture au-dessus du pr�cipice�"	//#6
			",�p600��d100� probablement pour nous emp�cher de juste tourner le coin.�p1800��"		//#7
			"�p200� :�p600��d140� veulent vraiment pas qu'on y aille,�p600� sur les to�ts.�p2000��"		//#8
			"�d100�\n\n\nSara �merge dans ton champs de vision,�p500� comme une araign�e qui commence � monter le grillage vers la droite�p150�-�p500�;�p800�"
			"�d80�\nE' veut passer par la grosse grille suspendue,�p300� la seule place qu'y'a pas d'barbel�s.�p600� Pis q'est fucking lisse pis ac' une chute de 8 m�tres en-d'sous d'elle.�p2500��"	//#9
			"�d120�\n\nMais la grille,�p180� qui fait juste chiller au-ds'us du vide,�p440� elle,�p580� elle a pas de barbel�s.�p400�.�p320�.�p3200�"
			"�d160� Fait que par l�.�p1500�.�p1100�.�p3000�");		//#10
			u.aordre("1-2-4-6-7-9;1-2-4-6-7-10;1-2-4-6-8-9;1-2-4-6-8-10;1-2-5-6-7-9;1-2-5-6-7-10;1-2-5-6-8-9;1-2-5-6-8-10;"
			"1-3-4-6-7-9;1-3-4-6-7-10;1-3-4-6-8-9;1-3-4-6-8-10;1-3-5-6-7-9;1-3-5-6-7-10;1-3-5-6-8-9;1-3-5-6-8-10");
	
			//Tu doutes de tes capacit�s, pour avoir une excuse pour commencer � int�grer les commandes manuelles
			u.nvauto(); u.acanal("je");		
			u.acond("intro�je==5");	
			u.adeb("�bintro�je~>0�");
			u.afin("�bintro�tuto~>1�");			
			u.atexte("�d90�\n\n\n\nTes yeux se ferment bri�vement,�p430� une seconde fois.�p1500�"
			"�d300�\n\n\n�d0�                  �d200�DANGEREUX.�p1600�"
			"�d100�\n\n\nT'ouvres l'oeil sur tes pieds,�p300� au sol,�p430��d120� l'autre oeil,�p520�"
			"\n�d0�                �d100�t'es debout sur l'asphalte,�p460� les orteils � peine sur la ligne jaune du devant du parking,�320� juste avant le bump de b�ton.�p1300�"
			"�d90�\n\nSara est�"																													//#1
			" rendue l'autre bord de la cl�ture�p130�,�p220� d�j� pass�e par-dessus la grille,�p180� agripp�e�p110� l�g�re encore dans le haut de la barri�re,�p330� accroch�e.�p2600��"	//#2
			" les deux pieds 'dans 'cl�ture,�p360��d120� d�j� grimp�e pas mal haut,�390��d140� d�j� pas mal proche du coin.�p200�.�p160�.�p3000��"					//#3
			"\n\n\n�d180�Tu ...�p820�,�p1240��d120�        ...tu penses pas�p210��d130� �tre capable�d140� de faire�p140��d160� �a�p300�?�p2600��"					//#4
			"�d90�\n\n\n\n\n\nTon pouls s'acc�l�re alors que t'imagine �d100�ton corps �d110�fr�le �d130�glisser,�p350� perdre�d150� pri�d170�se,�p460��d200� tomber�p600� .�p600�"		
			"\n�d0�      .�p700�"
			"\n�d0�           .�p600�"
			"\n�d0�              .�p500�"
			"\n�d0�                   .�p400�"
			"\n�d0�                    .�p300�"
			"\n�d0�                     .�p200�"
			"\n�d0�                      .�p100�"
			"\n�d0�                      .�d90� Tu -�p220�"
			"\n\n\nTu ressaisis ton corps�p420�, pis avances d'un coup pour bredouiller � Sara que t'es pas down finalement�p620�;"
			"\n�d110�     'est�"																										//#5
			"\n\n\n�d0�                          �d90� Fuck, a'�p260� -�p470�;�d0�     �d80�Fuck!�p2100�"
			"\n\n�p100�Tu restes plant�e o� tu es,�p750� au devant du parking,�p680� m�me pas encore pass� la ligne jaune � terre.�p1800�");	//6
			u.aordre("1-2-4;1-3-4;5-2-6;5-3-6");

			//La voix du tutoriel qui te parle
			u.nvauto(); u.acanal("msn");		
			u.acond("intro�tuto==1");	
			u.adeb("�bintro�tuto~>0�");
			u.afin("�f0��bintro�tuto~>2�");			
			u.atexte("                           C'est main�f1�tenant � toi de �"		//#1
			"guider�"		//#2
			"diriger�"		//3
			"commander�"	//#4
			" [t]es actes�"			//#5
			" [t]es actions�"			//#6
			".�p1000� �cris la �"		//#7
			"commande�"			//#8
			"directive�"			//#9
			" que tu souhaites [t]e donner,�p610� puis appuie sur �p120�[ENTER�p90�].�p2200�");		//#10
			u.aordre("1-2-5-7-8-10;1-3-5-7-8-10;1-2-6-7-8-10;1-3-6-7-8-10;1-2-5-7-9-10;1-3-5-7-9-10;1-4-5-7-9-10;1-2-6-7-9-10;1-3-6-7-9-10;1-4-6-7-9-10");

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
			u.adeb("�bcloture�sara~>0��s��p4000�\"");
			u.afin("�mabandonner�\""); 		//Le code sp�cial �m� est pour forcer l'ex�cution d'un motif manuel dont le nom correspond
			u.atexte("�d100�\n\n\n\n\nTu vois�r��p3400��r� c'est vraiment simple�r��p1400��r�,�p1800��r��p2120��r� c'est juste la partie o� tu changes de bord �r��2300�qui�p2000� est un peu tricky�r�,�p6130��r� mais sinon y'a vraiment pas � s'inqui�ter�r�,�p4700��r� tu vas voir �a va full bien s'passer�r��p3100��r�,�p4810��r� pis j'suis l� si y'a d'quoi.\"�r��p5600��r�"	
			"�p4000��r�\n\n\"�d110�Ok�r�,�p2430��r� fais juste avancer lentement�r�,�p4020��r� une fois que t'es dedans�p1400� �a se fait tu seul.�r��p5850��r� S�rieux.�r��p4570��r��p3000��r��p3300��r��"		//#1
			"�p3100��r��d200�\nCommmmmmme ooon�r�nnnnnnnnnnn�r��p600�.�r��2200��r��d100� Come on!�p1400��r� T'avais dit qu'�a t'tentait!�r��p2700��r��p3000��r��"		//#2
			"�p2200��r��d160��bcloture�estucorrecte~>1��\nOohh nooon,�p900��r� t'as l'air un peu cass�e -�r��p400��d90��r�"
			"�d0�                 �d90�Ben non pas cass�e j'voulais pas dire �a �p110�mais genre�r��p600��d140��r� absent�p200�e?�r��p1800��d110��r� Genre t'as pas l'air�r��p670��r� l�?�r��2200��r�"
			"�d90�Ok j'ai une id�e�p300��r� :�p500��r��d110� viens mettre tes deux mains�r� contre la cl�ture�r� pis fais juste te soulever�r� tu vas voir � quel point y'a rien l�r� pis �a va full te grounder�r�.�p2000� Right�p300�?�r��p1800��r� Right.�r��p3200��bcloture�estucorrecte~>0��"		//#3			
			"\n�d0�          �d90�ok fais juste bouger,�p1830� au moins�r�,�p4650��r� avance jusqu'�' clot�re�r��p7560��r�,�p2630��r��p2000��r� envoyes�r�,�1470��r��p2000��r� y fait frette!�r��p2100��r��p2000��r�");		//#4
									
			//Sara constate que t'es correcte parce que tu bouges
			u.nvauto(); u.acanal("sara");
			u.acond("cloture�estucorrecte==1&cloture�continuer==1|cloture�estucorrecte==1&cloture�grimper==1|cloture�estucorrecte==1&cloture�grimper==1|cloture�estucorrecte==1&cloture�courage==1");	
			u.adeb("�dcloture�estucorrecte~>0��p700��d90�");		//Dans la condition, '|' signifie "ou".
			u.afin("\"");
			u.atexte(" - �"		//#1
			"\n�d0�           �d90��"	//#2
			"Ah nice,�p400� t�"		//#3
			"Cool,�p300� t�"		//#4
			"Y�,�p450� t�"			//#5
			"Yipip �p300�bravo!�p810� T�"		//#6
			"u commen�ais � m'inqui�ter!�p800��"	//#7
			"'es encore l�!�p900��"			//#8
			"'as r'commenc� � bouger!�p1000��"		//#9
			"'as surmont� l'inertie!�p700�");		//#10
			u.aordre("1-3-7;1-3-8;1-3-9;1-3-10;1-4-7;1-4-8;1-4-9;1-4-10;1-5-7;1-5-8;1-5-9;1-5-10;1-6-7;1-6-8;1-6-9;1-6-10;"
			"2-3-7;2-3-8;2-3-9;2-3-10;2-4-7;2-4-8;2-4-9;2-4-10;2-5-7;2-5-8;2-5-9;2-5-10;2-6-7;2-6-8;2-6-9;2-6-10");

			//Sara chiale parce que t'abandonne
			u.nvauto(); u.acanal("sara");
			u.acond("cloture�abandon==1&cloture�sara==2");
			u.adeb("�dcloture�sara~>0��c��p2200��d110�\"");
			u.afin("\""); u.aover();
			u.atexte("\n\nAh bin.�p700�  Ah bin nice.�p1200�     Bon.�2000� Fait que�p700� bonne soir�e,�p500� l�.�p1000��"
			"Come on,�p700� pars pas!�p1500� Come�p400�-�p500�on�p200�!�p1800� Heille!�p2000�");
			u.aordre("1;2");
			
			//Choix: "abandonner"    (Premier motif manuel! Wouhou!)
			u.nvmanu("abandonner"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(reculer|retourner|aller|marcher|se diriger&vers|en direction d|pour atteindre|jusqu'&ailleurs|chapelle|�glise|cath�drale|rue|maison|chez soi|chez toi)"
			"(abandonner|quitter|s'en aller|partir)");		// ()() = deux fa�ons diff�rentes d'appeler cette commande
					//Un motif manuel a besoin de commandes pour �tre appel�!
						//Cette fonction d�finit quel mots-cl�s auront besoin d'�tre pr�sents (ou absent!) dans la commande entr�e par la joueuse pour que le motif manuel s'active.
						//Elle permet d'utiliser plusieurs fa�on de dire la commande (s�par�es par des parenth�ses) : ici, genre "avancer vers la cl�ture" ou genre "rejoindre Sara".
						//� l'int�rieur de chaque fa�on de dire la commande (donc � l'int�rieur de la parenth�se), on retrouve:
							//Des groupes de mots (s�par�s par '&'), qui doivent chacun �tre pr�sent pour que la commande soit valid�e : ici, "avancer|continuer", "vers|en direction d|pour atteindre|jusqu'" et "cl�ture|grillage|barri�re|to�t" sont des groupes de mots diff�rents
							//� l'int�rieur des groupes de mots, il y a:
								//Des synonymes (s�par�s par '|')! En gros, on a besoin d'avoir soit "Sara", soit "amie", soit "complice", soit "partenaire" ou soit "compagne" pour que le groupe de mot soit reconnu comme pr�sent.
							//Ils n'apparaissent pas ici, mais chaque fa�on de dire la commande peut aussi contenir des mots � �viter (mis entre crochets, et s�par�s par '|')!
					//Ici, autant "avancer en direction des to�ts", "continuer jusqu'au grillage" et "aller rejoindre ton amie" seront reconnues commes des commandes valides pour ce motif.
			u.mdeb("�bcloture�choix~>0��bcloture�abandon~>1��bcloture�sara~>2��s��d120�"); 	
					//Nouveau code sp�cial:
						//"�o�" ('o' pour overwrite) sert � effacer le texte du canal sp�cifi� (ici, "sara") pour arr�ter son affichage. En gros, on "coupe � parole" � Sara.
						//Pour �tre s�re de bien fermer �a propret, on place la terminaison du canal juste apr�s avoir tout effac�. Ici, �a permet de fermer son dialogue avec de derniers guillements (voir "u.canalterminaison()")
			u.mreserve();		//Lorsque ce motif sera appel� par une commande, il ne sera pas int�gr� tout de suite; il faudra attendre qu'un code sp�cial "�r�" soit atteint.
			u.mfin("\n\n\nC'EST LA FINNNNNNNNNN");
			u.mtexte("\nNon,�p300� non;�p1000� non.�p2600� Tu vas pas faire �a.�p1300� C'est trop glissant pis �a vaut pas la peine.�p2300�");
																				
			//Choix: "continuer", "avancer"	et autres formulations vagues
			u.nvmanu("aller de l'avant"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(marcher|se diriger|avancer|continuer|aller&vers|en direction d|pour atteindre|jusqu'&cl�ture|grillage|barri�re|to�t)(rejoindre|aller � la rencontre de|atteindre|rattraper&Sara|amie|complice|partenaire|compagne)");		// ()() = deux fa�ons diff�rentes d'appeler cette commande
			u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
					//On peut �galement d�finir des commandes qui doivent �tre �crites mots pour mots pour �tre reconnues
						//�a permet, par exemple, d'�viter de valider des commandes "contraires" avec des mots-cl�s trop flous:
						//Par exemple, "avancer" va te faire avancer vers la cl�ture, mais pas "avancer vers la cath�drale" (si on avait mis ces synonymes comme autre fa�on de dire la commande, tout ce qui aurait contenu "avancer" aurait pass� comme bon).
			u.mdeb("�osara��bcloture�choix~>0��bcloture�continuer~>1��s��d120�"); 		//D�s que le motif est lu, on efface ce que Sarah avait � dire
			u.mreserve();		//Lorsque ce motif sera appel� par une commande, il ne sera pas int�gr� tout de suite: il sera mis en r�serve. Il faudra attendre qu'un code sp�cial "�r�" soit lu par n'importe quel canal (ici, �a va arriver dans le dialogue de Sara).
			u.mfin("�bcloture�continuer~>2�");
			u.mtexte("�d120�\n\nOuin,�p800� tant qu'� d�j� �tre rendue�p140�...�p1600��"				//Segment #1
			"�d140�\n\n\nNon,�p300� tu vas pas chocker ici.�p1130��d110� T'es meilleure que �a.�p1800���"		//Segment #2
			"\n\n\nTu tires ton capuchon vers l'arri�re en levant le menton,�p350�"		//Segment #3
			"\ny'est plus dans tes yeux maintenant.�p1420��"							//Segment #3 (encore)
			"\n\nUn grand respire,�p570� tu soul�ves tes yeux�p430� � hauteur de Sara.�1170� 'A te sourit,�p440� puis marmonne qu'ses mains sont gel�es.�p620��"		//Segment #4
			"�d90� Tu lances ta jambes en avant dans un grand pas,�230� par-dessus l'obstacle de b�ton pis tu mets tes mains sur la grille.�p1000�");			//Segment #5
			u.mordre("1-3-5;1-4-5;2-3-5;2-4-5");		//Par d�faut, chaque combinaison a une chance �gale de se produire
	
				//Suite de "continuer" : faut demander explicitement de grimper (bout automatique qui l'explicite)
				u.nvauto(); u.acanal("je");
				u.acond("cloture�continuer==2");
				u.adeb("�bcloture�choix~>2�"); 
				u.afin("�mgrimper continuer�"); 		//Le code sp�cial �m� est pour forcer l'ex�cution d'un motif manuel dont le nom correspond
				u.atexte("�d80�\nOuin�r�,�p400� tu sais pas trop comment prendre �a�r�,�p510� finalement.�r��p820�    �r�Tu�p500�.�p420�..�r��p370� tu guess qu'il faut que t'escalades?�r��p1500��r��d130� T'ins�res tes doigts � l'int�rieur des fils losang�s.�r��p3520��r� Ben,�p410� d'ins trous d'la cl�ture,�p300� dans l'fond.�r��p4200��r�"
				"\n�a devrait �tre simple.�r��p3600��r� T'as juster � te hisser.�r��p4200��r� Te monter�p400��r�,�p520� avec un peu de force dans les bras�p300�.�r��p3500��r��p3600��r��p4020��r� Bon.�p760�");
			
				//Suite de "continuer" : faut demander explicitement de grimper (mais il se passe automatiquement si on attend assez longtemps)
				u.nvmanu("grimper continuer"); u.mcanal("je");
				u.mcond("cloture�continuer==2");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&cl�ture|grillage|barri�re|grille|to�t)(grimper|monter|escalader|se hisser)");
				u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
				u.mdeb("�bcloture�choix~>0�"); 
				u.mreserve(); u.mover();
				u.mfin("�bcloture�grimper~>2�");
				u.mtexte("�d80� Tu places tes mains plus haut,�p220� s�cures tes doigts�p100� pis tires�p200��d100� comme "
				"\n�d0�                     �d70�tes bottes glissent contre la cl�ture�p210�;�p330� tu r�ussis � avoir une pogne pour tes pieds.�p1100�"
				"�bcloture�grimper~>1�"
				"�d90�\n\nNice,�p140� t'es d'ins airs.�p2300�");

			//Choix: "Franchir la ligne" ou autres formulation dramatiques/litt�rales (parce qu'il faut d'abord que t'enjambe la ligne de peinture jaune)
			u.nvmanu("franchir la ligne jaune"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(franchir|traverser|outrepasser|pi�tiner|fouler|marcher sur|passer|continuer outre&ligne|limite|trait|d�limitation|fronti�re)");
			u.mdeb("�osara��bcloture�choix~>0��bcloture�franchir~>1��s��d110�"); 
			u.mfin("�bcloture�franchir~>2�");
			u.mreserve();		//Lorsque ce motif sera appel� par une commande, il ne sera pas int�gr� tout de suite; il faudra attendre qu'un code sp�cial "�r�" soit atteint.
			u.mtexte("\n\n\nFuck it.�p800��"		//Segment #1
			"\nTu regardes la ligne jaune � terre.�p500� La peinture �caill�e te fixe en retour.�p800��"		//Segment #2
			"\n\nLes bornes administratives d'un parking de presbyt�re ne peuvent plus te contenir.�1500��"		//Segment #3
			"\nTu choisis ton camp pour ce soir.�p800�"		//Segment #4
			" Tu l�ves solonellement ta botte,�p400� et passe outre la limite du parking.�p1300�"
			"\nT'as la jambe droite accot�e sur le butoir de b�ton et tu es pr�te � affronter n'importe quoi.�p1100��"			//Segment #5
			"\nT'enjambes ce qui te s�parait encore de la cl�ture : un trait peintur� � terre pis un rectangle de ciment bas.�p1400��"			//Segment #6
			"\n\nTu foules la d�limitation stationnaire d'un bref bond;�p1000� conquis le petit bump de b�ton en deux temps.�p1600�"
			"\nLa cl�ture n'a qu'� bien se tenir.�p2600�");			//Segment #7
			u.mordre("1-5;1-6;1-7;2-5;2-6;2-7;3-5;3-6;3-7;4-5;4-6;4-7");

				//Suite de "franchir" : faut demander explicitement de grimper (bout automatique qui l'explicite)
				u.nvauto(); u.acanal("je");
				u.acond("cloture�franchir==2");
				u.adeb("�bcloture�choix~>2�"); 
				u.afin("�mgrimper franchir�"); 		//Le code sp�cial �m� est pour forcer l'ex�cution d'un motif manuel dont le nom correspond
				u.atexte("�d80�");
			
				//Suite de "franchir" : faut demander explicitement de grimper (mais il se passe automatiquement si on attend assez longtemps)
				u.nvmanu("grimper franchir"); u.mcanal("je");
				u.mcond("cloture�franchir==2");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir|vaincre|conqu�rir|braver|soumettre&cl�ture|grillage|barri�re|grille|to�t)(grimper|monter|escalader|se hisser)");
				u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
				u.mdeb("�bcloture�choix~>0�"); 
				u.mreserve(); u.mover();
				u.mfin("�bcloture�grimper~>2�");
				u.mtexte("");
			
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
						
			//Choix: "Grimper" ou autres
			u.nvmanu("grimper la cl�ture"); u.mcanal("je");
			u.mcond("cloture�choix==1");
			u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&cl�ture|grillage|barri�re|grille|to�t[�tre capable d|pouvoir|�tre en posture de|se forcer �|se motiver �])"		// [] = on ne les veut pas!
			"(poser|passer|mettre|accoter|reposer|d�poser&main|gant|doigt&contre|sur|le long|au travers d&cl�ture|grillage|barri�re|grille)");
			u.mcommexact("grimper|escalader|se hisser");
			u.mdeb("�osara��bcloture�choix~>0��bcloture�grimper~>0��s��d120�"); 
			u.mfin("�bcloture�grimper~>2�");
			u.mreserve();		
			u.mtexte("\n\n\n\nTu l�ves un bon pas franc et tu te ramasses � trois pouces du grillage.�p1400� T'�tends ton bras droit,�p540� fermes tes doigts contre les fils froids.�p700��d130� Positionnes ton autre main,�p670��d150� baisse ton bassin pour un �p320��d180��lan�d230�..."
			"�d0�\n\n               �d80�t'pousses tes rotules en d'scendant dans les vides en losanges�p130� parc'qu'tes bottes ont gliss�p200� pis t'doigts tirent�p100� pis tu patines encore p'tu lances ton gant plus haut encore pis �a clenche �p140�- ton pied pogne' le trou ton pied s'appuie!�p2200�"
			"�bcloture�grimper~1�"
			"�d120�\nGode.�r��p1000��d100��r� Fait que t'es s'a cl�ture.�r��p1900��r� Le vent souffle une�d150� bourrasque.�r��d90��p2600��r�");
					
				//Suite de "grimper" (point commun de toutes les avenues) : t'es dans les airs, pis faut bouger sur la cl�ture, sinon tes bras fatiguent pis tu retombes
				u.nvauto(); u.acanal("je");
				u.acond("cloture�grimper==2");
				u.adeb("�d90�");
				u.afin("�bcloture�grimper~>3�");
				u.atexte(" Fait que t'imagines que tu dois te tra�ner � droite,�p800��r� dans le haut de la grosse grille verticale.�p2400��r��p1100� ");
							//Reste � avancer ce texte plus!
						
						
				//Choix: "Grimper encore" (si t'es tomb�e)
				u.nvmanu("grimper encore"); u.mcanal("je");
				u.mcond("cloture�grimper==3");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&cl�ture|grillage|barri�re|grille|to�t[�tre capable d|pouvoir|�tre en posture de|se forcer �|se motiver �])"		// [] = on ne les veut pas!
				"(poser|passer|mettre|accoter|reposer|d�poser&main|gant|doigt&contre|sur|le long|au travers d&cl�ture|grillage|barri�re|grille)");
				u.mcommexact("grimper|escalader|se hisser");
				u.mdeb("�bcloture�grimper~>0��s��d120�");
				u.mreserve();		
				u.mtexte(""); 									
										
				//Choix: "Se d�placer sur la cl�ture"						
										
//-----------------------------------------------------------------|     Menu principal      |--------------------------------------------------------------------------------\\

//Dessin de la sc�ne "enti�re" � mettre comme arri�re-plan du menu principal:

/*

"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"												|��������������������|��|                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"              �       {)                       |                    |  |                                          "
"     ________/|\/k__/\|)_______                | � � � � � � � � �  |��|                                          "
"    /         ��     �        /|               |                    |  |                                          " 
"   /                         /_|_______        | � � � � � � � � �  |��|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | � � � � � � � � �  |��|                                          "
"|                     _____|/       /  |_/\____|__________          |  |                                          "
"|  |���|    |���|    /             /  /  ||              /|� � � �  |��|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |� � � �  |��|                                          "	//115 colonnes
"|__________________|__��__��__��__|/__________________/___|_________|__|_______                                   "	//43 lignes
"��������\�����������\\�����������\�����������\�����������\�����������\��������\\                                  "
"���������\�����������\\�����������\�����������\�����������\�����������\��������\\                                 "
"���������������������||���������������������������������������������������������||_____________________________   "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "
"/\/\/\/\/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\||   ||   ||   ||   ||   ||   ||  "
"\/\/\/\/\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/||   ||   ||   ||   ||   ||   ||  "

*/

		//La sc�ne id�ale (en utiliser les dimensions pour d�finir la taille de la fen�tre par d�faut)

/*

"                                                                       " 
"                                                                       "		//Espace vertical requis pour le titre  
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		//
"                                                                       "		
"                                                                       "		
"                                                                       "
"                                                                       "
"                                                                       "                                                                                                              "
"                                                                       "
"                                       |��������������������|��|       "
"                                       | � � � � � � � � �  |��|       "
"                                       |                    |  |       "		//71 colonnes
"                                       | � � � � � � � � �  |��|       "		//37 lignes
"                                   x   |                    |  |       "
"                                       | � � � � � � � � �  |��|       "			x = milieu
"      �       {)                       |                    |  |       "
"_____/|\/k__/\|)_______                | � � � � � � � � �  |��|       "
"      ��     �        /|               |                    |  |       " 
"                     /_|_______        | � � � � � � � � �  |��|       "			//Version alternative du titre (plus longue)
"                    / /       /|       |                    |  |       "
"___________________/ /       / |       | � � � � � � � � �  |��|       "		"          /\                  |                  "
"              _____|/       /  |_/\____|__________          |  |       "		"          \                   |   _   /\         "
"    |���|    /             /  /  ||              /|� � � �  |��|       "		"           \   | |   |/       |  /_\  \          "
"    |   |   /_____________/  /                  / |         |  |       "		"          \/   \_|\  |        |  \_  \/          "		//9 lignes de haut
"    |___|  |              | /               ~  /  |� � � �  |��|       "		"                                                 "
"___________|__��__��__��__|/__________________/___|_________|__|_____  "		"               |            |                    "
"\�����������\\�����������\�����������\�����������\�����������\��������\"		"              ���       *  ���   /\              "
"�\�����������\\�����������\�����������\�����������\�����������\��������"		"               |   /\   |   |    \               "
"�������������||��������������������������������������������������������"		"               |   \/   |   |   \/               "
"/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"		"                                                 "
"\/\/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\"
"/\/\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"

*/
	//D�finir la taille par d�faut de la fen�tre de jeu
	u.setfenetredefaut(71,37);
	
		//La sc�ne "minimale", avec titre et menu (la plus petite version que je juge possible - tout en restant belle et compl�te)
/*
		
"           /\                 |   _              "		//7 lignes de haut, le titre abr�g�
"           \   | |   |/       |  /_\  /\         "
"          \/   \_|\  |        |  \_  \/          "
"                                                 "
"               |        *   |                    "
"              ���  /\   |  ���   /\              "
"               |   \/   |   |   \/               "
"                                                 "							//49 colonnes
"                                    |������������"							//31 lignes
"               |�����������������|  | � � � � � �"
"               |     D�buter     |  |            "
"               |_________________|  | � � � � � �"
"                                    |            "
"                                    | � � � � � �"
"   �       {)  |�����������������|  |            "
"__/|\/k__/\|)__|     Options     |  | � � � � � �"					//Le bouton central est compl�tement centr�.
"   ��     �    |_________________|  |            " 
"                  /_|_______        | � � � � � �"
"                 / /        |       |            "
"_______________|�����������������|  | � � � � � �"
"           ____|     Quitter     |_____________  "
" |���|    /    |_________________|            /|�"
" |   |   /_____________/  /                  / | "
" |___|  |              | /               ~  /  |�"
"________|__��__��__��__|/__________________/___|_"
"���������\\�����������\�����������\�����������\��"
"����������\\�����������\�����������\�����������\�"
"����������||�������������������������������������"
"\/\/\/\/\/||\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\"
"/\/\/\/\/\||/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/"

*/
	//D�finir la taille minimale possible de la fen�tre � l'aide de ce que je juge �tre la plus petite fen�tre acceptable possible
	u.setfenetremin(49,31);

	//Cr�er le menu principal
	u.nvmenu("principal");
	
		//D�finir l'arri�re-plan du menu
			//Attention! Ici, les caract�res '\' doivent �tre doubl�s ("\\") pour que le code se lise bien. �a d�cale le dessin, mais il s'affichera correctement � l'�cran!
		u.menubg("                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                                                                                                  "
"                                               |��������������������|��|                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"                                               |                    |  |                                          "
"                                               | � � � � � � � � �  |��|                                          "
"              �       {)                       |                    |  |                                          "
"     ________/|\\/k__/\\|)_______                | � � � � � � � � �  |��|                                          "
"    /         ��     �        /|               |                    |  |                                          "
"   /                         /_|_______        | � � � � � � � � �  |��|                                          "
"  /                         / /       /|       |                    |  |                                          "
" /_________________________/ /       / |       | � � � � � � � � �  |��|                                          "
"|                     _____|/       /  |_/\\____|__________          |  |                                          "
"|  |���|    |���|    /             /  /  ||              /|� � � �  |��|                                          "
"|  |   |    |   |   /_____________/  /                  / |         |  |                                          "
"|  |___|    |___|  |              | /               ~  /  |� � � �  |��|                                          "
"|__________________|__��__��__��__|/__________________/___|_________|__|_______                                   "
"��������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                  "
"���������\\�����������\\\\�����������\\�����������\\�����������\\�����������\\��������\\\\                                 "
"���������������������||���������������������������������������������������������||_____________________________   "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  "
"/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||   ||   ||   ||   ||   ||   ||  "
"\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\||/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/||   ||   ||   ||   ||   ||   ||  ",43);		//Indiquer le nombre de lignes du dessin comme second argument

		//D�finir les rebords du dessin qui ne doivent pas �tre remplac�s par des espaces (si la fen�tre est plus grande que le dessin, des espaces viendront remplir le c�t� oppos�)
		u.menubglock("left"); u.menubglock("bottom");
		
		//D�finir le point d'int�r�t du dessin
			//C'est l'outil dont je me suis dot� pour pouvoir minimalement positionner le dessin correctement, peu importe la taille de la fen�tre.
			//Il faut d�finir une cellule du dessin (l'origine (0,0) est le coin en haut � gauche) qui va servir de point d'int�r�t.
			//Il faut ensuite d�finir une position pr�cise � laquelle on souhaite voir ce point d'int�r�t. Cette position sera exprim�e en fractions de la largeur et de la hauteur de la fen�tre.
			//Ici, je souhaite que les personnages soient situ�s dans le coin en bas � gauche de l'image:
		u.menubgpointinteret(18,21,0.2,0.7);
		
		//D�finir le titre � afficher � l'�cran
		u.menutitredessin("          /\\                  |                  "
"          \\                   |   _   /\\         "
"           \\   | |   |/       |  /_\\  \\          "
"          \\/   \\_|\\  |        |  \\_  \\/          "		//9 lignes de haut
"                                                 "
"               |            |                    "
"              ���       *  ���   /\\              "
"               |   /\\   |   |    \\               "
"               |   \\/   |   |   \\/               ",9);
		
		//D�finir sa hauteur par rapport � la fen�tre totale (0 = dans le haut compl�tement)
		u.menutitrehauteur(0.0285714286);		// = 1/35; mais �a ne marche pas quand on l'�crit en tant que fraction...
		
		//D�finir le premier bouton de mon menu principal, ainsi que son effet
		u.menunvbouton("Lancer le jeu","�bintro�je~>1��j�");
			//Ce bouton aura pour effet de modifier un rayon de la biblioth�que, puis de lancer la boucle "jouer" (�j�, 'j' pour "jouer"), qui lance le programme. 
	
		//D�finir le deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Quitter","�a�");	
			//Ce bouton aura pour effet de terminer le programme (�a�, 'a' pour "abort()").

//-----------------------------------------------------------------|      Menu de pause      |--------------------------------------------------------------------------------\\

	//Cr�er le menu de pause
	u.nvmenu("pause");				//Par d�faut, si on ne sp�cifie pas d'arri�re-plan, le contenu des m�moires sera utilis�

		//D�finir le titre � afficher � l'�cran
		u.menutitredessin("/---------\\"
"|  PAUSE  |"
"\\---------/",3);
		
		//D�finir sa hauteur par rapport � la fen�tre totale (0 = dans le haut compl�tement)
		u.menutitrehauteur(0.05);
		
		//D�finir le premier bouton du menu, ainsi que son effet
		u.menunvbouton("Retour au jeu","�u�");			
			//Ce bouton aura pour effet de remettre le jeu en action (�u�, 'u' pour "unpause").

		//D�finir le deuxi�me bouton, ainsi que son effet
		u.menunvbouton("Revenir au \nmenu principal","�zprincipal�");	
			//Ce bouton aura pour effet d'appeler le menu principal (�z�, 'z' pour... rien en fait. 'm' �tait d�j� pris dans les codes sp�ciaux de canaux, alors j'ai pris z. Que je r�-utilise ici).			

			//Comme le deuxi�me bouton a deux lignes, je vais agrandir tous les boutons � une hauteur de 4 (� la place de 3):
			u.menuhauteurbouton(4);

		//D�finir le troisi�me bouton, ainsi que son effet
		u.menunvbouton("Quitter le jeu","�a�");	
			//Ce bouton aura pour effet de terminer le programme (�a�, 'a' pour "abort()").		

		//D�finir l'action de la touche [ESCAPE]
			//Par d�faut, cette touche a pour cons�quence la fermeture du programme.
		u.menuescape("�u�");		//R�gler [ESCAPE] pour revenir au jeu

//-----------------------------------------------------------------|        Ex�cuter         |--------------------------------------------------------------------------------\\		
		
	//Commencer proprement
	u.debuter();

}		
