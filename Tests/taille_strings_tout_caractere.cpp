#include<iostream>
using namespace std;

int main() {
	string test1 = "bonjour";
	std::cout << "La longueur de \"" << test1 << "\" est de " << test1.length() << ".\n";

	string test2 = "�";
	std::cout << "La longueur de \"" << test2 << "\" est de " << test2.length() << ".\n";

	string test3 = "����";
	std::cout << "La longueur de \"" << test3 << "\" (4 symboles) est de " << test3.length() << ".\n";	

	string test4 = "\n";
	std::cout << "La longueur de " << "<endline>" << "  est de " << test4.length() << ".\n";	

	string test5 = " ";
	std::cout << "La longueur de " << "<espace>" << "  est de " << test5.length() << ".\n";

	string test6 = "\\\"";
	std::cout << "la longueur de " << "\\\\\\\"" << "  est de " << test6.length() << ".\n";
	std::cout << "De plus, sa premi�re position est " << test6[0] << ".\n";
	std::cout << "Et sa deuxi�me position est " << test6[1] << ".\n";

}
