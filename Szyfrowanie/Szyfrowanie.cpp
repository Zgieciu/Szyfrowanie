#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

//szyf Vigenere'a
char tabLowercase[26][26];
char tabUppercase[26][26];

//funkcja do szyfrowania, argumenty to tekst do zaszyfrowania i klucz szyfru, zwraca zaszyfrowany tekst
string encryption(string text, string key) {
    for (int i = 0; i < text.length(); i++) {
        if (text[i] >= 65 && text[i] <= 90) { // du¿e litery
            text[i] = tabUppercase[text[i] - 65][key[i] - 65];
        }
        else if (text[i] >= 97 && text[i] <= 122) { // ma³e litery 
            text[i] = tabLowercase[text[i] - 97][key[i] - 97];
        }
    }

    return text;
}

//funkcja do odszyfrowania, argumenty to tekst do odszyfrowania i klucz szyfru, zwraca odszyfrowany tekst
string decryption(string text, string key) {
    for (int i = 0; i < text.length(); i++) {
        if (text[i] >= 65 && text[i] <= 90) { // du¿e litery
            for (int j = 0; j < 26; j++) {
                if (tabUppercase[j][key[i] - 65] == text[i]) {
                    text[i] = j + 65;
                    break;
                }
            }

        }
        else if (text[i] >= 97 && text[i] <= 122) { // ma³e litery 
            for (int j = 0; j < 26; j++) {
                if (tabLowercase[j][key[i] - 97] == text[i]) {
                    text[i] = j + 97;
                    break;
                }
            }
        }
    }

    return text;
}

//szyfr Cezara
//funkcja do szyfrowania, argumenty to tekst do zaszyfrowania i przesuniêcie, zwraca zaszyfrowany tekst
string encryption(string text, int shift) {
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] >= 65 && text[i] <= 90) { // du¿e litery
            text[i] += shift;
            if (text[i] > 90) text[i] -= 26;
        }
        else if (text[i] >= 97 && text[i] <= 122) { // ma³e litery 
            int pom = text[i];
            pom += shift;                     //zmienna pomocnicza, u¿ywana do tego, aby index nie przekroczy³ rozmiaru tablicy ASCII
            if (pom > 122) pom -= 26;
            text[i] = pom;
        }
    }

    return text;
}

//funkcja do odszyfrowania, argumenty to tekst do odszyfrowania i przesuniêcie, zwraca odszyfrowany tekst
string decryption(string text, int shift) {
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] >= 65 && text[i] <= 90) { // du¿e litery
            text[i] -= shift;
            if (text[i] < 65) text[i] += 26;
        }
        else if (text[i] >= 97 && text[i] <= 122) { // ma³e litery 
            text[i] -= shift;
            if (text[i] < 97) text[i] += 26;
        }
    }

    return text;
}

int main()
{
    setlocale(LC_CTYPE, "Polish");
    int shift, option, pom;
    string text, line, key;
    fstream file;

    //zape³nianie tablic literami
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            pom = j + i + 97;
            if (pom > 122) pom -= 26;
            tabLowercase[i][j] = pom;
        }
    }

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            pom = j + i + 65;
            if (pom > 90) pom -= 26;
            tabUppercase[i][j] = pom;
        }
    }

    cout << "Program do szyfrowanie lub deszyfrowania danych za pomoc¹ szyfru Cezara i Vigenere'a\n" << endl;
    cout << "Wybierz którego szyfru chcesz u¿ywaæ: " << endl;

    do {
        menu:
        cout << "1.Szyfr Cezara" << endl;
        cout << "2.Szyfr Vigenere'a" << endl;
        cout << "3.Zakoñcz program" << endl;
        cin >> option;

        if (option == 1) {
            do {
                text = "";
                cout << endl << "Wybierz opcjê 1/2:" << endl;
                cout << "1. Szyfrowanie" << endl;
                cout << "2. Deszyfrowanie" << endl;
                cout << "3. Cofnij" << endl;
                cout << endl;

                do {
                    cin >> option;

                    while (option != 1 && option != 2 && option != 3) {
                        cout << "Zosta³a podana z³a opcja, wybierz jeszcze raz: " << endl;
                        cin >> option;
                    }
                    if (option == 1) {
                        cout << "Wybrno szyfrowanie\n";
                    }
                    else if (option == 2) {
                        cout << "Wybrno deszyfrowanie\n";
                    }
                    else {
                        goto menu;
                    }

                    cout << endl << "Podaj wartoœæ przesuniêcia: ";           //podawanie przesuniêcia 
                    cin >> shift;
                    while (shift < 1 || shift > 25) {
                        cout << "Przesuniêcie nie mo¿e byæ liczb¹ ujemn¹ oraz 0, maksymalne przesuniêcie wynosi 25, podaj przesuniêcie jeszcze raz: ";
                        cin >> shift;
                    }

                    if (option == 1) {                  //szyfrowanie
                        cout << endl << "Wybierz opcjê 1/2:" << endl;
                        cout << "1. Szyfrowanie poprzez wpisanie tekstu" << endl;
                        cout << "2. Szyfrowanie z pliku" << endl;
                        cout << endl;

                        do {
                            cin >> option;

                            if (option == 1) {
                                cout << "Podaj tekst do zaszyfrowania: " << endl;
                                getline(cin >> ws, text);
                            }
                            else if (option == 2) {
                                file.open("szyfrowanie.txt");         //podczas szyfrowania z pliku, w pliku ostatnia linijka musi zostaæ pusta

                                do {
                                    getline(file, line);
                                    text += line + " ";

                                } while (line != "");

                                file.close();
                            }
                            else {
                                cout << "Wybrano nie poprawn¹ opcjê, wybierz 1 lub 2" << endl;
                            }

                        } while (option != 1 && option != 2);

                        text = encryption(text, shift);
                    }
                    else if (option == 2) {                 //deszyfrowanie
                        cout << endl << "Wybierz opcjê 1/2:" << endl;
                        cout << "1. Deszyfrowanie poprzez wpisanie tekstu" << endl;
                        cout << "2. Deszyfrowanie z pliku" << endl;
                        cout << endl;

                        do {
                            cin >> option;

                            if (option == 1) {
                                cout << "Podaj tekst do deszyfrowania: " << endl;
                                getline(cin >> ws, text);
                            }
                            else if (option == 2) {
                                file.open("deszyfrowanie.txt");          //podczas deszyfrowania z pliku, w pliku ostatnia linijka musi zostaæ pusta

                                do {
                                    getline(file, line);
                                    text += line + " ";

                                } while (line != "");

                                file.close();
                            }
                            else {
                                cout << "Wybrano nie poprawn¹ opcjê, wybierz 1 lub 2" << endl;
                            }

                        } while (option != 1 && option != 2);

                        text = decryption(text, shift);
                    }

                    cout << "\nTekst po przejœciu przez szyfr Cezara:" << endl;
                    cout << text << endl;

                } while (option != 1 && option != 2 && option != 3);

            } while (option != 3);
        }
        else if (option == 2) {
            do {
                cout << endl << "Wybierz opcjê 1/2:" << endl;
                cout << "1. Szyfrowanie" << endl;
                cout << "2. Deszyfrowanie" << endl;
                cout << "3. Cofnij" << endl;
                cout << endl;
     
                do {
                    cin >> option;

                    while (option != 1 && option != 2 && option != 3) {
                        cout << "Zosta³a podana z³a opcja, wybierz jeszcze raz: " << endl;
                        cin >> option;
                    }

                    if (option == 1) {                                       //szyfrowanie
                        cout << "Wybrno szyfrowanie\n";
                        cout << "\nPodaj tekst do zaszyfrowania:\n";
                        getline(cin >> ws, text);
                        cout << "\nPodaj klucz szyfru:\n";
                        getline(cin >> ws, key);
                        text = encryption(text, key);
                    }

                    else if (option == 2) {                                  //deszyfrowanie
                        cout << "Wybrano deszyfrowanie\n";
                        cout << "\nPodaj tekst do odszyfrowania:\n";
                        getline(cin >> ws, text);
                        cout << "\nPodaj klucz szyfru:\n";
                        getline(cin >> ws, key);
                        text = decryption(text, key);
                    }

                    else if (option == 3) {
                        goto menu;
                    }

                cout << "\nTekst po przejœciu przez szyfr Vigenere'a:" << endl;
                cout << text << endl;

            } while (option != 1 && option != 2 && option != 3);

        } while (option != 3);
        }
        else if (option == 3) {
            cout << endl << "Dziêkujemy za u¿ycie naszego programu. :)" << endl;
            break;
        }
        else {
            cout << "Zosta³a podana z³a opcja, wybierz jeszcze raz: " << endl;
        }

    } while (option != 3);
    
}
