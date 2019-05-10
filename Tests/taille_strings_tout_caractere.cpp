#include<iostream>
using namespace std;

int main() {
	string test1 = "bonjour";
	std::cout << "La longueur de \"" << test1 << "\" est de " << test1.length() << ".\n";

	string test2 = "§";
	std::cout << "La longueur de \"" << test2 << "\" est de " << test2.length() << ".\n";

	string test3 = "¶¼¢¤";
	std::cout << "La longueur de \"" << test3 << "\" (4 symboles) est de " << test3.length() << ".\n";	

	string test4 = "\n";
	std::cout << "La longueur de " << "<endline>" << "  est de " << test4.length() << ".\n";	

	string test5 = " ";
	std::cout << "La longueur de " << "<espace>" << "  est de " << test5.length() << ".\n";

}
