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
				//Cette ligne sert à définir les conditions sous lesquelles ce chapitre sera valide (les moments dans lesquels on pourra en puiser du texte).
				//Pour faire ça, on utilise les livres de la bibliothèque!
				//On peut reconnaître qu'on recherche le rayon "intro", et qu'à l'intérieur de ce rayon, on veut le livre "desuet". 
				//COMME POUR TOUTE RÉFÉRENCE À LA BIBLIO, le rayon est séparé du livre par le symbole '¶' (BTW, garde en tête de ne pas mettre d'espaces de chaque côté. C'est pas "intro ¶ desuet", c'est "intro¶desuet").
				//Ici, la condition veut simplement que ce livre ("desuet", situé dans le rayon "intro") soit égal à 0 (qui est la valeur par défaut de tous les livres).
				//Si l'on remplit cette condition, on pourra pêcher du texte des motifs présents dans ce premier chapitre.
				
				
			//Introduire notre premier motif
					//Houuu!! Là ça devient sérieux!
					//Il s'agit d'un motif automatique (pour bien le différencier, on voit que toutes les fonctions qui le modifie commencent par un 'a'), qui lancera le texte qu'il contient dans la console dès que sa condition d'activation sera remplie.
			u.nvauto(); u.acanal("je");	    
					//On crée le nouveau "motif" (c'est là où on conserve le texte qu'on va ajouter progressivement aux canaux). Et puis on l'assigne à un canal: ici, ce sera "je", qui correspond à la narration.    	
			u.acond("intro¶je==1");	
					//Comme pour le chapitre, chaque motif doit avoir une condition d'activation. Ici, le "je", situé à l'intérieur de "intro", doit être égal à 1 (et il le sera au début du programme). 
			u.atexte("\n\nT'as froid aux joues.§p1400§"
			"\n§d0§                     §d80§Pis aux cuisses.");	
					//Beaucoup de nouvelles choses ici!!!
					//First, "\n". Il s'agit du "code spécial" standard (standard à la plupart des langages de programmation) pour dire qu'on change de ligne.
						//Fait qu'à chaque fois qu'on inclut "\n" dans notre texte, on va sauter une ligne à l'écran rendue là.
						//Ici, "\n\n" fait qu'on va sauter deux lignes avant de commencer à déclamer le texte.
					//Deuxièmement: Un code spécial! 
						//Un code spécial est : n'importe quoi qui est entouré de '§', et qui effectue une action précise sur le système de jeu.
						//La deuxième lettre du code (après le premier '§') va servir à dire de quel type le code spécial est (en gros: qu'est-ce qu'il fait).
						//Ici, on en a deux types: "§p§"  et  "§d§".
							//"§p§" ('p' pour pause) sert à prendre une pause dans la lecture, une pause dont la longueur est transmise en millisecondes.
								//En lisant "§p1400§", le canal "je" va arrêter d'afficher son texte pendant 1,4 secondes, pui recommencer.
							//"§d§" ('d' pour délai) sert à modifier le délai (le temps à attendre) entre chaque lettre.
								//En définissant le canal "je", on lui avait donné un délai de 80 millisecondes : le canal va sortir une nouvelle lettre à toutes les 0.08 secondes.
								//Ici, j'utilise simplement un p'tit truc pour tasser le texte à gauche:
									//a) changer de ligne; b) mettre un délai de 0 seconde (lire le texte à la vitesse de l'éclair); c) remettre le délai normal quand on a assez inscrit d'espace (quand le texte est assez tassé).
			u.adeb("§bintro¶je~>0§§p1200§");
					//Pour faciliter la lecture des codes importants, je sépare le début et la fin du texte du reste.
					//Mais ça va faire partie du texte du motif, au final. Le voir comme     { deb + texte + fin } = le texte du motif au complet
								
					//Nouveau code spécial qui s'introduit!
						//"§b§" ('b' pour bibliothèque) sert à modifier les valeurs stockées dans la bibliothèque (donc, agir sur quel motif présente les conditions nécessaires pour s'activer)
						//Après le 'b', on va avoir "le nom du rayon de la bibliothèque où on veut modifier un livre" ("intro"), '¶', "le nom du livre qu'on veut modifier" ("sara"), "le symbole de modification" ("~>"), puis "la valeur qu'on veut donner au livre" ("1").
						//Ici, ce code spécial va permettre de désactiver le motif actuel (sa condition était "intro¶je==0") (et oui, un même motif peut être activé plus d'une fois!).
			u.afin("§bintro¶sara~>1§");
					//Ici, à la fin du texte, on met en place la valeur qui va permettre au prochain motif de s'activer (le prochain motif, ça va être Sara qui parle)!
					

			//Deuxième motif: Message de directives du début (temporaire?)
			u.nvauto(); u.acanal("msn");
					//Nouveau concept: un msn
						//En gros, j'voulais avoir la possibilité d'inscrire un message temporaire, qui s'inscrit puis qui s'efface (avec un visuel cool).
						//Fait que j'ai créé une nouvelle classe de "canaux", que j'ai nommé "msn".
						//Puisque les "msn" sont temporaires, il ne faut pas les créer au début : on en crée un nouveau à chaque fois qu'un motif ayant comme canal "msn" s'active.
			u.acond("intro¶je==1");
			u.afin("§p2600§§f0§");
					//Nouveau code spécial!
						//"§f§" ('f' pour FREEZE) sert à mettre en pause tous les autres canaux (et messageries), pour n'avoir que celui qui l'a inscrit qui est actif.
							//"§f1§" (qui est présent au milieu du mot "quitter", dans le texte du motif) sert à "freezer", tandis que "§f0§" sert à "dé-freezer".
			u.atexte("§p4000§Pour qui§f1§tter le programme,§p400§ appuie sur §p210§[ESC§p110§].§p1200§"
			"\nPour modifier la vitesse de défilement,§p600§ appuie sur les touches §p90§[HAUT§p100§] et §p140§[BAS§p90§] (possiblement plusieurs fois).");
				
				
				
				
						//C'est weird, y'a encore la première lettre qui apparaît toute seule avant le reste?
								//Si je voulais régler ce problème de manière absolument pas correcte, je pourrais mettre ' ' comme première lettre...
									
							//Non, sérieux, faudrait que j'investigue ce problème.
				
				
				
				
			//La harangue de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==1");	
			u.adeb("§bintro¶sara~>0§§s§");
					//Nouveau code spécial!
						//§s§ ('s' pour skip) sert à placer le canal dans le bas du texte qui s'affiche (skipper la file!) : ça permet de le mettre à l'avant-scène, drette sous les projecteurs. 
			u.afin("§bintro¶je~>2§");
			u.atexte("§p1800§\n\"Come on,§p1100§"
			"\n§d0§          §d130§on est presqu'arrivées!\"");
					//Nouveau "code spécial standard"
						//    \"     , ça là (j'peux pas l'entourer de guillemets en gardant ça clair), ça fait qu'un guillemet (") s'affiche à l'écran.
						//C'est parce que sinon, un guillement tout seul signifie "début/fin de la zone de texte". Fait que pour rester dans la zone de texte pis afficher un guillement à l'écran, on utilise \" .

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==2");	
			u.adeb("§bintro¶je~>0§§s§");
			u.afin("§bintro¶sara~>2§");
			u.atexte("§p400§\n\n         T'accélères le pas,§p600§ moins pour la rejoindre§p100§ que pour réchauffer tes jambes.§p1200§§d110§ Le vent,§p500§ criss.§p700§ Le vent.§p1600§"
			"\n§d90§Tu lèves les yeux§p100§ juste à la limite de ton capuchon§p300§ pis Sara est quand même loin en avant.§p1400§§d80§ Tu te presses un peu plus.§p2800§"
			"\n\nTraverses une rue,§p400§ t'es au coin de la cathédrale§p300§ pis le vent charge de plus belle depuis ta droite.§p2400§ Caliss.§p3000§§d90§ Sara est déjà rendue plus bas,§p500§ a'longe la grosse chapelle.§p2300§"
			"\n§d0§                       §d80§Tu descends au jogging§p120§, §p400§"
			"\n§d0§                                                §d80§rejoindre au plus vite l'énorme pare-vent de pierre.§p1800§"
			"\nTa jupe virevolte sur tes genoux,§p200§ expose tes cuisses aux rafales;§p2300§ Pas l'meilleur choix de vêtements.§p4300§"
			"\n\n     La cathédrale coupe le vent§p150§ pour vrai.§3100§ "
			"\n\n\nSara t'as un peu attendue et te sourit avec son trop d'excitation.§p2200§");

			//La réponse de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==2");	
			u.adeb("§bintro¶sara~>0§§s§");
			u.afin("§bintro¶je~>3§");
			u.atexte("§p130§§d110§\n\"J'te l'dis,§p260§ t'as vraiment hâte d'être rendue su'l'toît du Granada!\"");			//FAUDRAIT CHANGER CETTE PHRASE POUR QUELQUE CHOSE DE PLUS CRÉDIBLE

			//La suite
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==3");	
			u.adeb("§bintro¶je~>0§§s§");
			u.afin("§bintro¶sara~>3§");
			u.atexte("§p3100§Tu peux pas empêcher tes commissures engourdies de remonter un peu.§p2600§"
			"\n\n§d90§Encore quelques pas ensemble et vous êtes à l'arrière d'la maison de Dieu§p140§ pis l'vent reprend.§p560§§100§ Vraiment une belle soirée pour être sur l'top d'une colline.§2600§"
			"\n\n§d90§Sara te traîne encore plus derrière l'église,§p220§ dans une allée séparée de la rue par un p'tit muret.§p1800§ À ta gauche,§p160§ tu peux voir le frimas sur les toits plats des buildings adjacents,§p240§ pis les lumières de la ville,§p130§ de l'autre côté d'la rivière.§p2000§ Vous êtes pas mal haut,§p180§ finalement.§p3000§"
			"\nTu continues et un long bâtiment de briques s'érige entre le bord de la falaise et vous,§p110§ coupe le paysage.§p900§ Ça donne moins le vertige.§p2500§"
			"\n§d0§               §d90§Tu te demandes si c'est illégal de grimper sur les toits des bâtiments la nuit.§p1200§"  
			"§d100§\n\nAprès la bâtisse,§p300§ votre allée remonte à gauche vers un léger promontoir asphalté.§p1100§"
			"\nUltime place de parking avant le précipice.§p2300§"
			"\nLe stationnement garde le bâtiment de briques à sa gauche;§p330§ et une ligne jaune comme limite à droite,§p540§ même si le bord du précipice donne aussi une délimitation pas mal claire.§p2000§ Y'a des \"§p120§butoirs\"§p70§ en béton à droite et au devant de l'emplacement,§p140§ tout le long de la peinture jaune.§p2600§ À l'avant, c'est bouclé par une clôture haute de 3 ou 4 mètres,§p230§ qui empêche fermement l'accès aux toits adjacents,§p400§ barbelés et tout.§p2400§"
			"§d85§\nClôture sur laquelle les épaules de Sara sont accotées,§p140§ ses deux pieds repoussés contre le bump en béton.§p1500§ Les bras croisés,§p400§ un sourire qui sussure"
			"\n§d0§                          §d100§\"C'est par là qu'on passe\".§p3000§");

			//L'explication de Sara
			u.nvauto(); u.acanal("sara");		
			u.acond("intro¶sara==3");	
			u.adeb("§bintro¶sara~>0§§s§");
			u.afin("");
			u.atexte("§p1600§§d100§\n\"Fait qu'on a juste à monter la clôture,§bintro¶je~>4§§p300§ là,§p2900§"
			"\npis après on va vraiment jusqu'au coin,§p400§ jusqu'à l'autre clôture bizarre,§p200§ la genre de grille qui pend.§p1200§ Pis elle,§p90§ on la monte§p270§ - tu vas voir c'est pas tough - §p5200§ pis 'y reste juste à r'descendre pis on est sur les toîts.\"");
					//BTW: ici, on dit à un motif de l'autre canal (le prochain) de commencer à s'activer PENDANT que le texte de celui-ci défile. Ça fait que tout le monde parle en même temps. Effet intéressant.
			
			//Encore l'explication de Sara, mais en gestes (narration)	/ puis la tienne
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==4");	
			u.adeb("§bintro¶je~>0§§s§");
			u.afin("§bintro¶je~>5§");
			u.atexte("§d80§\n\nElle se redresse et pose la main à plat sur le grillage en losanges§p540§ avant de pointer l'extrémité en haut à droite,§p420§ avance d'un pas en bougeant de haut en bas avec ses deux bras,§p2800§ te regarde dans les yeux,§p1200§ fait un tour sur elle-même en crispant les dents avec ses doigts solidement accrochés à son imagination,§p100§§d90§ et fait semblant d'atterir sur ses deux pieds,§d110§ finalement.§p4500§"
			"§d100§\n\n\nElle te sourit,§300§ l'air fière de son explication.§p2000§"
			"§d110§\nTu clignes des paupières§p800§ une fois.§p2900§"
			"§d100§\n\n\nLa tête te soupire§p110§ et t'avances pour constater le chemin toi-même.§p2100§"
			"\n\nAu devant, la grande barrière de grillage en losanges§p90§ a son top en barbelés,§p390§ dressés en angle contre votre direction.§p900§ §d120§Fait que définitivement pas par là.§p2300§"
			"§d150§\n\nÀ droite,§p500§§d130§ par contre,§p430§§d110§ le grillage finit juste avant la falaise,§p290§ et une espèce de grille à gros barreaux verticaux prolonge la clôture au-dessus du précipice,§p600§§d100§ probablement pour nous empêcher de juste tourner le coin.§p1800§"
			"§d120§\n\nMais la grille,§p180§ qui fait juste chiller au-ds'us du vide,§p440§ elle,§p580§ elle a pas de barbelés.§p400§.§p320§.§p3200§"
			"§d160§ Fait que par là.§p3800§");
	
			//Tu doutes de tes capacités, pour avoir une excuse pour commencer à intégrer les commandes manuelles
			u.nvauto(); u.acanal("je");		
			u.acond("intro¶je==5");	
			u.adeb("§bintro¶je~>0§");
			u.afin("§bintro¶tuto~>1§");			
			u.atexte("§d90§\n\n\n\nTes yeux se ferment brièvement,§p430§ une seconde fois.§p1500§"
			"§d300§\n\n\n§d0§                  §d200§DANGEREUX.§p1600§"
			"§d100§\n\n\nT'ouvres l'oeil sur tes pieds,§p300§ au sol,§p430§§d120§ l'autre oeil,§p520§"
			"\n§d0§                §d100§t'es debout sur l'asphalte,§p460§ les orteils à peine sur la ligne jaune du devant du parking,§320§ juste avant le bump de béton.§p1300§"
			"§d90§\n\nSara est rendue l'autre bord de la clôture§p130§,§p220§ déjà passée par-dessus la grille,§p180§ agrippée§p110§ légère encore dans le haut de la barrière,§p330§ accrochée.§p2600§"
			"\n\n\n§d180§Tu ...§p820§,§p1240§§d120§        ...tu penses pas§p210§§d130§ être capable§d140§ de faire§p140§§d160§ ça§p300§?§p2600§");

			//La voix du tutoriel qui te parle
			u.nvauto(); u.acanal("msn");		
			u.acond("intro¶tuto==1");	
			u.adeb("§bintro¶tuto~>0§");
			u.afin("§f0§§bintro¶tuto~>2§");			
			u.atexte("                           C'est main§f1§tenant à toi de guider [t]es actes.§p1000§ Écris la commande que tu souhaites effectuer,§p610§ puis appuie sur §p120§[ENTER§p90§].§p2200§");

			//Les mille et une suggestions d'actions à faire
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin("§bintro¶desuet~>1§§bcloture¶choix~>1§"); u.atexte("§p7130§Avancer§p1100§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p8840§Franchir la ligne§p2000§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p9270§Continuer§p800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p11600§Monter dans le grillage§p1400§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p12310§Être capable de grimper§p1800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p13530§Poursuivre§p2300§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p16020§Aller de l'avant§p1600§");			
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p16250§Rassembler son courage§p1800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p18510§Monter sur les toits§p3800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p19750§Surmonter sa peur§p2200§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p22670§Franchir la ligne jaune§p3000§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin(""); u.atexte("§p25830§Rejoindre Sara§p1800§");
			u.nvauto(); u.acanal("msn"); u.acond("intro¶tuto==2"); u.afin("§bcloture¶sara~>1§"); u.atexte("§p26930§Avancer jusqu'à la clôture§p2100§");


				//Pis... je crois que le code bug quand y'a plus de msn qui veulent s'inscrire que la limite imposée???
							//Faudrait vérifier ça!!!
							
//-----------------------------------------------------------------|   Traverser la clôture  |--------------------------------------------------------------------------------\\
							
	//Débuter un chapitre dont le but sera de passer par-dessus la clôture
	u.nvchapt();
		u.ccond("intro¶desuet&!cloture¶desuet");        //Rendre le premier chapitre accessible seulement quand t'as pas encore traversé + quand ce n'est plus l'intro													
						//Première condition composée!
							//Le symbole '&' signifie que les deux conditions doivent être À LA FOIS remplie pour que le motif soit activé. Ça veut dire "ET".
							//Si on voit '|', au contraire, ça signifie qu'une ou l'autre des conditions doivent être remplies, ou encore les deux à la fois. '|' signifie "OU".
						//J'utilise aussi de bêtes raccourcis d'expression logique: 
							//"intro¶desuet" tout seul signifie que "intro¶desuet" est égal à n'importe quoi sauf 0.  
								//J'aurais aussi pu l'écrire "intro¶desuet!=0", car l'opérateur "!=" signifie "pas égal à".
							//et "!cloture¶desuet" signifie que "cloture¶desuet" n'est pas égal à "n'importe quoi sauf 0". Donc est égal à 0. Donc "cloture¶desuet==0", dans le fond.
					
			//Sara te rassures
			u.nvauto(); u.acanal("sara");					//Le texte est parsemé de "§r§". Ce code spécial permet d'intégrer le motif manuel qui était en réserve au bon moment.						
			u.acond("cloture¶sara==1");						//Cette mécanique est utilisée afin de ne pas interrompre une phrase n'importe quand par la réception d'une commande.
			u.adeb("§bcloture¶sara~>0§§s§§p4000§");
			u.afin("\n\n\nC'EST LA FINNNNNN");			
			u.atexte("§d100§\n\n\n\n\n\"Tu vois§r§§p3400§§r§ c'est vraiment simple§r§§p1400§§r§,§p4120§§r§ c'est juste la partie où tu changes de bord §r§§2300§qui§p2000§ est un peu tricky§r§,§p6130§§r§ mais sinon y'a vraiment pas à s'inquiéter§r§,§p4700§§r§ tu vas voir ça va full bien s'passer§r§§p3100§§r§,§p4810§§r§ pis j'suis là si y'a d'quoi.\"§r§§p5600§§r§"	
			"§p4000§§r§\n\n\"§d110§Ok§r§,§p2430§§r§ fais juste avancer lentement§r§,§p4020§§r§ une fois que t'es dedans§p1400§ ça se fait tu seul.§r§§p5850§§r§ Sérieux.§r§§p4570§§r§§p3000§§r§§p3300§§r§"
					//Y'a vraiment un changement de ton, ici... Est-ce que j'veux garder ça?
			"\n§d0§          §d90§ok fais juste bouger,§p1830§ au moins§r§,§p4650§§r§ avance jusqu'à' clotûre§r§§p7560§§r§,§p4630§§r§ envoyes§r§,§4470§§r§ y fait frette!§r§§p4100§§r§");
					//Continuer dans cette veine jusqu'à une décision finale de "tu", qui est de chocker pour de bon.
									
															
			//Choix: "continuer", "avancer"	et autres formulations vagues  (Premier motif manuel! Wouhou!)
			u.nvmanu("aller de l'avant"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(avancer|continuer&vers|en direction d|pour atteindre|jusqu'&clôture|grillage|barrière|toît)(rejoindre|aller à la rencontre de|atteindre|rattraper&Sara|amie|complice|partenaire|compagne)");		// ()() = deux façons différentes d'appeler cette commande
					//Un motif manuel a besoin de commandes pour être appelé!
						//Cette fonction définit quel mots-clés auront besoin d'être présents (ou absent!) dans la commande entrée par la joueuse pour que le motif manuel s'active.
						//Elle permet d'utiliser plusieurs façon de dire la commande (séparées par des parenthèses) : ici, genre "avancer vers la clôture" ou genre "rejoindre Sara".
						//À l'intérieur de chaque façon de dire la commande (donc à l'intérieur de la parenthèse), on retrouve:
							//Des groupes de mots (séparés par '&'), qui doivent chacun être présent pour que la commande soit validée : ici, "avancer|continuer", "vers|en direction d|pour atteindre|jusqu'" et "clôture|grillage|barrière|toît" sont des groupes de mots différents
							//À l'intérieur des groupes de mots, il y a:
								//Des synonymes (séparés par '|')! En gros, on a besoin d'avoir soit "Sara", soit "amie", soit "complice", soit "partenaire" ou soit "compagne" pour que le groupe de mot soit reconnu comme présent.
							//Ils n'apparaissent pas ici, mais chaque façon de dire la commande peut aussi contenir des mots à éviter (mis entre crochets, et séparés par '|')!
					//Ici, autant "avancer en direction des toîts", "continuer jusqu'au grillage" et "aller rejoindre ton amie" seront reconnues commes des commandes valides pour ce motif.
			u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
					//On peut également définir des commandes qui doivent être écrites mots pour mots pour être reconnues
						//Ça permet, par exemple, d'éviter de valider des commandes "contraires" avec des mots-clés trop flous:
						//Par exemple, "avancer" va te faire avancer vers la clôture, mais pas "avancer vers la cathédrale" (si on avait mis ces synonymes comme autre façon de dire la commande, tout ce qui aurait contenu "avancer" aurait passé comme bon).
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶continuer~>1§§s§§d120§"); 		//Dès que le motif est lu, on efface ce que Sarah avait à dire
					//Nouveau code spécial:
						//"§o§" ('o' pour overwrite) sert à effacer le texte du canal spécifié (ici, "sara") pour arrêter son affichage. En gros, on "coupe à parole" à Sara.
						//Pour être sûre de bien fermer ça propret, on place la terminaison du canal juste après avoir tout effacé. Ici, ça permet de fermer son dialogue avec de derniers guillements (voir "u.canalterminaison()")
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite: il sera mis en réserve. Il faudra attendre qu'un code spécial "§r§" soit lu par n'importe quel canal (ici, ça va arriver dans le dialogue de Sara).
			u.mfin("§bcloture¶choix~>2§");
			u.mtexte("§d120§\n\nOuin,§p800§ tant qu'à déjà être rendue§p140§...§p1600§µ"				//Segment #1
			"§d140§\n\n\nNon,§p300§ tu vas pas chocker ici.§p1130§§d110§ T'es meilleure que ça.§p1800§§µ"		//Segment #2
			"\n\n\nTu tires ton capuchon vers l'arrière en levant le menton,§p350§"		//Segment #3
			"\ny'est plus dans tes yeux maintenant.§p1420§µ"							//Segment #3 (encore)
			"\n\nUn grand respire,§p570§ tu soulèves tes yeux§p430§ à hauteur de Sara.§1170§ 'A te sourit,§p440§ puis marmonne qu'ses mains sont gelées.§p620§µ"		//Segment #4
			"§d90§ Tu lances ta jambes en avant dans un grand pas,§230§ par-dessus l'obstacle de béton pis tu mets tes mains sur la grille.§p1000§");			//Segment #5
					//Nouveau mécanisme!
						//Pour introduire de la variété dans les phrases qui s'affichent, j'ai décidé que différentes combinaisons de phrases semblables pourraient être sélectionnées.
						//Ici, je sépare mon texte en plusieurs segments. Le séparateur utilisé est 'µ' (comme '§', c'est un caractère que j'suis sûre de ne pas utiliser sinon).
			u.mordre("1-3-5;1-4-5;2-3-5;2-4-5");		//Par défaut, chaque combinaison a une chance égale de se produire
					//Ici, je décide quelles seront les "combinaisons gagnantes" : celles qui pourront être sélectionnées pour être ajouté au canal "je".
					//Par exemple, ici, les segments #1 et #2 sont à peu près synonymes, de même que les #3 et #4. Donc j'mets juste toutes les combinaisons différentes.
	
				//Suite de "continuer" : faut demander explicitement de grimper (bout automatique qui l'explicite)
				u.nvauto(); u.acanal("je");
				u.acond("cloture¶choix==2&cloture¶continuer==1");
				u.adeb("§bcloture¶choix~>2§"); 
				u.afin("§mgrimper maintenant§");
				u.atexte("§d80§\nOuin§r§,§p400§ tu sais pas trop comment prendre ça§r§,§p510§ finalement.§r§§p820§    §r§Tu§p500§.§p420§..§r§§p370§ tu guess qu'il faut que t'escalades?§r§§p1500§§r§§d130§ T'insères tes doigts à l'intérieur des fils losangés.§r§§p3520§§r§ Ben,§p410§ d'ins trous d'la clôture,§p300§ dans l'fond.§r§§p4200§§r§"
				"\nÇa devrait être simple.§r§§p3600§§r§ T'as juster à te hisser.§r§§p4200§§r§ Te monter§p400§§r§,§p520§ avec un peu de force dans les bras§p300§.§r§§p3500§§r§§p3600§§r§§p4020§§r§ Bon.§p760§");		//Le code spécial §m§ est pour forcer l'exécution d'un motif manuel dont le nom correspond
			
				//Suite de "continuer" : faut demander explicitement de grimper (mais il se passe automatiquement si on attend assez longtemps)
				u.nvmanu("grimper maintenant"); u.mcanal("je");
				u.mcond("cloture¶choix==2&cloture¶continuer==1");
				u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît)(grimper|monter|escalader|se hisser)");
				u.mcommexact("aller de l'avant|avancer|continuer|poursuivre");
				u.mdeb(""); 
				u.mreserve(); u.mover();
				u.mfin("\n\n\nC'EST LA FINNNNNN");
				u.mtexte("§d80§ Tu places tes mains plus haut,§p220§ sécures tes doigts§p100§ pis tires§p200§§d100§ comme "
				"\n§d0§                     §d70§tes bottes glissent contre la clôture§p210§;§p330§ tu réussis à avoir une pogne pour tes pieds.§p1100§"
				"§d90§\n\nNice,§p140§ t'es d'ins airs.§p2300§");



			//Choix: "Franchir la ligne" ou autres formulation dramatiques/littérales (parce qu'il faut d'abord que t'enjambe la ligne de peinture jaune)
			u.nvmanu("franchir la ligne jaune"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(franchir|traverser|outrepasser|piétiner|fouler|marcher sur|passer|continuer outre&ligne|limite|trait|délimitation|frontière)");
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶franchir~>1§§s§§d120§"); 
			u.mfin("\n\n\nC'EST LA FINNNNNN");
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			u.mtexte("\n\n\nTU DÉPASSES TES LIMITES JAUNES MAIS QUELLE MÉTAPHORE");
						
			//Choix: "Grimper" ou autres
			u.nvmanu("grimper la clôture"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît[être capable d|pouvoir|être en posture de|se forcer à|se motiver à])");		// [] = on ne les veut pas!
			u.mcommexact("grimper|escalader|se hisser");
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶grimper~>1§§s§§d120§"); 
			u.mfin("\n\n\nC'EST LA FINNNNNN");
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			u.mtexte("\n\n\nTU GRIMPES LA CLÔTURE BRAVO POUR TOI");
						
			//Choix: "Surmonter sa peur" / "Rassembler son courage" / "Prendre son courage à deux mains", etc.
			u.nvmanu("surmonter sa peur"); u.mcanal("je");
			u.mcond("cloture¶choix==1");
			u.mcomm("(être capable d|pouvoir|être en posture de|se forcer à|se motiver à&grimper|monter|escalader|agripper|se hisser|franchir&clôture|grillage|barrière|grille|toît)"
			"(être capable d|pouvoir|être en posture de|se forcer à|se motiver à&grimper|escalader|se hisser)");
			u.mcommexact("surmonter sa peur|prendre son courage à deux mains|se prendre en mains|rassembler son courage|être courageuse");
			u.mdeb("§osara§§bcloture¶choix~>0§§bcloture¶courage~>1§§s§§d120§"); 
			u.mreserve();		//Lorsque ce motif sera appelé par une commande, il ne sera pas intégré tout de suite; il faudra attendre qu'un code spécial "§r§" soit atteint.
			u.mfin("\n\n\nC'EST LA FINNNNNN");
			u.mtexte("\n\n\nTU RASSEMBLES TON COURAGE C'EST BEAU CHAMPIONNE");
						
													
			
//-----------------------------------------------------------------|                         |--------------------------------------------------------------------------------\\
	
	//WORK IN PROGRESS
		//Modifier la bibliothèque pour suit my needs
		//u.biblio.modif("cloture","choix",1); u.biblio.modif("intro","desuet",1); u.biblio.modif("cloture","sara",1);
	
	
	//Enclencher le premier motif (oui, j'fais ça manuellement pour garder l'uniformité dans mes enclenchements)
	u.biblio.modif("intro","je",1);
	//Vérifier une toute première fois la disponibilité des motifs automatiques
	u.AutoInterpret();
	//Faire une boucle pour que les canaux s'expriment!
	u.jouer();				
	curspos(u.cons,0,13);			//Mettre le curseur dans un bel endroit à la fin


}		
