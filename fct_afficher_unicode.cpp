/*
                    ///||================================---2018/02/02---================================||\\\
\\\||================================---Simplement tenter d'utiliser des accents (UNICODE!) sur Windows---================================||///
*/


//Donc, ce que pourrait �tre un prototype:
void printanychar (std::string s) {
	for(int a=0;a<s.length();a++){
		if(s[a]=='�') std::wcout << L"\u00C0";
		else if(s[a]=='�') std::wcout << L"\u00E0";
		else if(s[a]=='�') std::wcout << L"\u00C7";		
		else if(s[a]=='�') std::wcout << L"\u00E7";
		else if(s[a]=='�') std::wcout << L"\u00C9";		
		else if(s[a]=='�') std::wcout << L"\u00E9";
		else if(s[a]=='�') std::wcout << L"\u00C8";
		else if(s[a]=='�') std::wcout << L"\u00E8";
		else if(s[a]=='�') std::wcout << L"\u00CE";
		else if(s[a]=='�') std::wcout << L"\u00EE";
		else if(s[a]=='�') std::wcout << L"\u00CF";
		else if(s[a]=='�') std::wcout << L"\u00EF";						
		else if(s[a]=='�') std::wcout << L"\u00D4";
		else if(s[a]=='�') std::wcout << L"\u00F4";
		else if(s[a]=='�') std::wcout << L"\u00D9";
		else if(s[a]=='�') std::wcout << L"\u00F9";	
		else if(s[a]=='�') std::wcout << L"\u00DB";
		else if(s[a]=='�') std::wcout << L"\u00FB";	
		else {
			char t;
			t = s[a]; 
			std::wcout << t;
		}
	}
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    std::wcout << L"Hello, \u0444!\n";
    //std::wcout << L"�";                                      //Ne fonctionne pas!
    std::wcout << L"\nEt si c'etait seulement mes accents?";   //C'est bien �a! wcout avec L"" (transforme les strings en wchar_t??) n'inclue pas les charact�res sp�ciaux!
    
    std::wcout << L"\nEt si c'\u00E9tait seulement mes accents?";     //Ok, l� �a marche avec l'Unicode.
    
    if('�'=='e') std::wcout <<  L"Donc, pour les strings standards, '\u00E9' == 'e'?";
    else std::wcout <<  L"\nHeureusement, pour les strings standards, '\u00E9' != 'e'. Good.";
    
    std::wcout << "\nEt disons, si on ne change pas pour wchar_t ? '\u00E9'";     //Et il faut transformer les strings...
    std::wcout << L"\nEt disons, si on change pour wchar_t ? '\u00E9'";     //Et il faut transformer les strings...
    
    std::string test = "Ceci est une string.";
    std::wcout << L"\n\nOk, disons, on a cette string : ";
    //std::wcout << test;  //Ne fonctionne pas, parce que c'est une string I guess??
    
    std::wstring wtest = L"Ceci est une string.";
    std::wcout << wtest;
    
    std::wcout << "\n\nTenter de d�tecter un e accent aigu: ";
    detect_e('�');
    
	//Test pour voir si je ne pourrais pas simplement assigner un char � wchar_t
	std::wcout << "\n\nPeut-on transformer un char en wchar_t juste comme ca?";
	char narrow = 'e';
	wchar_t wide;
	wide = narrow;
	std::wcout << L"\nCa a march\u00E9? Voici la lettre: ";
	std::wcout << "\nVersion en char: " << narrow;
	std::wcout << "\n Version en wchar_t: " << wide;  //Donc, techniquement, �a marche...
	
	//Test pour voir si je peux printer des phrases:
	std::wcout << "\n\n\nEssai fantastique d'un prototype:";
	printanychar("\n\nVoyons voir si �a a march�?");
	printanychar("\n\nWhouhou! Je suis all�e sur une �le de bon go�t, � Qu�bec!");
}


