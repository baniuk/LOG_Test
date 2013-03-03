/** 
* \file DOC_MainPage.h 
* \brief Main page documentation
*
* This file contains main page for doc and some todos
* \todo 
*		-# Dorobi� skrypt czyszcz�cy ca�y projekt z pozosta�o�ci CMake dla Unixa\n
*		-# Zrobi� jak w gtest osobny katlaog na pewne ustawienia i makra cmake (scie�ki do narzedzi itp)\n
*		-# Narz�dzia dla unixa w katalogu external_tools
*		-# Kompilacja MP jak w dokumentacji w EverNote /OpenSceneGraph/trunk � osg\n
*		-# poprawi� gitignore bo nie wsz�dzie b�dzie potrzebny w przypdku out-of-source build
*/

/** \mainpage Test bibliotek logujacych oraz budowa struktury projektu
*
* Program testuj�cy biblioteki logowania oraz budow� oprogramowania za pomoc� CMake.
* \section Instalacja
* Projekt wymaga nast�uj�cych komponent�w:
*	-# CMake - zainstalowany w systemie\n
*	\warning Je�li jest zainstalowany cygwin nale�y sprawdzi� czy �ciezka wskazuje w�a�ciwego Cmake. Je�li nie ma profili VC (przy wywo�aniu z konsoli VS) to mo�e by� z�y Cmake. 
*	-# Gtest - Projekt w VC jest oparty o makefile wygenerowany wcze�niej za pomoc� CMake - musi by� zainstalowany.\n
*	W ustawieniach projektu s� skrypty tworz�ce �rodowisko kompilacji 
*	-# Doxygen\n
* \section struktura Struktura projektu
*	- <a href="..\..\Readme">Struktura projektu</a>
*	- W konfiguracjach zmieniane s� jedynie:\n
*		-# Output directory
*		-# Intermediate Directory
* \section Pantheios
* W ustawieniach projektu musza by� �cie�ki do include i lib katalogu Pantheios.
* Dodatkowo ustawi� �cie�k� na STLSOFT
* \section CMake
* -# Testy\n
*	 Testowanie skrypt�w cmake - wej�� do katalogu KATALOG ze skrytptem i uruchomi�\n
*	\code
*	cmake -G "NMake Makefiles" KATALOG
*	\endcode
*	Po sko�czeniu uruchmi� skrypt clean.bat kt�ry wyczy�ci wszystko opr�cz skryptu w tym katalogu. CMake b�dzie tworzy� pliki tylko w katalogu w kt�rym jest wywo�any
* \section General
* -# Projekt g��wny kompilowany z Charakter Not Set, dla Unicode nie linkuje pantheios	
*/
