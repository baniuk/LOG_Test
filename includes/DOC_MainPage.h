/** 
* \file DOC_MainPage.h 
* \brief Main page documentation
*
* This file contains main page for doc and some todos
* \todo 
*		-# Dodac przelacznik -j xx do make na UNIX do kompilacji na xx rdzeni (Uwaga to jest tylko do make a nie do kompilatora)\n
*		-# Narzêdzia dla unixa w katalogu external_tools\n
*		-# Kompilacja MP na WIN - dodaÄ‡ do proejktÃ³w jako opcja kompilatora\n
*		-# U¿yc instalacji ¿eby kopiowac liby do okreslonego katalogu, np bin - gotowe biblioteki, build - œmieci podczas kompilacji
		-# Dla unixa nie tworzy wersji debug dla boosta. Przejzec takze katalogi dla bibliotek - zmienne sa zle zadeklarowane
		
*/

/** \mainpage Test bibliotek logujacych oraz budowa struktury projektu
*
* Program testuj¹cy biblioteki logowania oraz budowê oprogramowania za pomoc¹ CMake.
* \section Instalacja
* Projekt wymaga nastêuj¹cych komponentów:
*	-# CMake - zainstalowany w systemie\n
*	\warning Jeœli jest zainstalowany cygwin nale¿y sprawdziæ czy œciezka wskazuje w³aœciwego Cmake. Jeœli nie ma profili VC (przy wywo³aniu z konsoli VS) to mo¿e byæ z³y Cmake. 
*	-# Gtest - Projekt w VC jest oparty o makefile wygenerowany wczeœniej za pomoc¹ CMake - musi byæ zainstalowany.\n
*	W ustawieniach projektu s¹ skrypty tworz¹ce œrodowisko kompilacji 
*	-# Doxygen\n
* \section struktura Struktura projektu
*	- <a href="..\..\Readme">Struktura projektu</a>
*	- W konfiguracjach zmieniane s¹ jedynie:\n
*		-# Output directory
*		-# Intermediate Directory
* \section Pantheios
* W ustawieniach projektu musza byæ œcie¿ki do include i lib katalogu Pantheios.
* Dodatkowo ustawiæ œcie¿kê na STLSOFT
* \section CMake
* -# Testy\n
*	 Testowanie skryptów cmake - wejœæ do katalogu KATALOG ze skrytptem i uruchomiæ\n
*	\code
*	cmake -G "NMake Makefiles" KATALOG
*	\endcode
*	Po skoñczeniu uruchmiæ skrypt clean.bat który wyczyœci wszystko oprócz skryptu w tym katalogu. CMake bêdzie tworzy³ pliki tylko w katalogu w którym jest wywo³any
* \section General
* -# Projekt g³ówny kompilowany z Charakter Not Set, dla Unicode nie linkuje pantheios	
*/
