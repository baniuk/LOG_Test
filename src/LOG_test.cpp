/**
*	\file LOG_test.cpp
*	\author PB
*	\brief Main file
*	\details
*	This file calls all modules and it is main entry point to the application. Creates multiplexed log according to severity level
*/

#include <iostream>
#include <platformstl/platformstl.h>                /* for platform discrimination */

// pliki nag��wkowe do funkcji - nie myli� z linkowaniem dynamicznym poni�ej
#include <pantheios/pantheios.hpp>

// dodaje do logu nazw� funkcji i linii, musi by� przed trace.h http://stackoverflow.com/questions/2343821/how-to-include-the-calling-class-and-line-number-in-the-log-using-pantheios
// zmiana wygl�du logu: http://www.codeproject.com/Articles/27119/Using-Callback-Back-ends-with-the-Pantheios-Loggin
#ifndef PANTHEIOS_INCL_PANTHEIOS_H_TRACE
	#define PANTHEIOS_TRACE_PREFIX         __FILE__ "(" PANTHEIOS_STRINGIZE(__LINE__) "): "  ": "
#endif /* PANTHEIOS_INCL_PANTHEIOS_H_TRACE */
#include <pantheios/trace.h>

#include <pantheios/backends/be.N.h>
#include <pantheios/backends/bec.file.h>
#include <pantheios/backends/bec.fprintf.h>
// simple - chyba tylko w debug, all zawsze ?? http://sourceforge.net/projects/pantheios/forums/forum/475314/topic/2186546
// N - If you use fe.simple, then all log statements whose severity is less than (=== more severe than, since lower means more severe) the active ceiling will go to all back-ends. 
// The "active ceiling" defaults to PANTHEIOS_SEV_DEBUG (meaning all statements are emitted) in debug builds, and to PANTHEIOS_SEV_NOTICE (meaning all statements with severity emergency, alert, critical, error, 
// warning and notice are emitted) in release builds. You may change the "active ceiling" at any time using pantheios_fe_simple_setSeverityCeiling()
// If you use fe.N, then each log statement may be subjected to filtering on a per-back-end basis, as defined by the contents of the PAN_FE_N_SEVERITY_CEILINGS array.
#include <pantheios/frontends/fe.N.h>

// Biblioteki ��czone dynamicznie, nie trzeba wpisywac ich nazwy. Dla UNIXA moze by� inaczej. Przyk�ad rozpoznania:
// http://www.pantheios.org/doc/html/c_2example_8c_8N_2example_8c_8N_8c-example.html#a10
// Trzeba pilnowac co si� ��czy, biblioteki s� zamienne ale program mo�e inaczej dzia�a�. Na przyk�ad jesli zamiast fe.N do��czy si� fe.simple to do obu �r�de� p�jdzie to samo bez filtrowania
#include <pantheios/implicit_link/core.h>
#include <pantheios/implicit_link/fe.N.h>
#include <pantheios/implicit_link/be.N.h>
// dla windows jest to windowsconsole, dla unixa to fprinf
//  http://binglongx.wordpress.com/2010/08/30/pantheios-logging-library-installation-and-use/
#include <pantheios/implicit_link/be.file.h>
#include <pantheios/implicit_link/be.fprintf.h>

// Biblioteki inne
#include "C_Point.h"

// http://sourceforge.net/projects/pantheios/forums/forum/475314/topic/2186546
// 
/// Konwersja ci�g�w wymagana przez Pantheios, w zale�no�ci od ustawie� kompilatora u�ywa poprawnych ci�g�ow
#ifndef PSTR
	#define PSTR(x)         PANTHEIOS_LITERAL_STRING(x)
#endif

/// Typ wyliczeniowy okreslaj�cy cele log�w
enum LOGI 
{  
	File = 1,  /**< Logowanie do pliku */
	Console = 2  /**< Logowanie do konsoli */
}; 

// nazwa aplikacji do log�w
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("LOG_test");

/**
 * \brief Struktura okre�laj�ca minimalny poziom b�edu kt�ry trafia do danego logu
 * 
 * DEBUG jest poziomem najni�szym, co znaczy �e do pliku trafi wszystko. Ta struktura dzia�a
 * jedynie gdy linkuje si� do biblioteki be.N. Kolejno�� b��d�w:
 * -# DEBUG
 * -# INFORMATIONAL
 * -# NOTICE
 * -# WARNING
 * -# ERROR
 * -# CRITICAL
 * -# ALERT
 * -# EMERGENCY
 * \n
 * Do konsoli trafi wszystko powy�ej ERROR
 */ 
 pan_fe_N_t PAN_FE_N_SEVERITY_CEILINGS[]  =
{
	{ File,  PANTHEIOS_SEV_DEBUG    } 
	, { Console,  PANTHEIOS_SEV_ERROR     } 
	, PANTHEIOS_FE_N_TERMINATOR_ENTRY(PANTHEIOS_SEV_CRITICAL)
};

/**  
 * \brief Struktura ��cz�ca poziom b�edu z konkretnym wyj�ciem
 * 
 * LOGI::File i LOGI::Console ��cz� si� z pozycjami w PAN_FE_N_SEVERITY_CEILINGS
 */ 
pan_be_N_t PAN_BE_N_BACKEND_LIST[] =
{
	PANTHEIOS_BE_N_STDFORM_ENTRY(File, pantheios_be_file, 0)
	, PANTHEIOS_BE_N_STDFORM_ENTRY(Console, pantheios_be_fprintf, 0)
	, PANTHEIOS_BE_N_TERMINATOR_ENTRY
};

using namespace std;

int main(void)
{
	pantheios_be_file_setFilePath(PSTR("file-1.log"), PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BEID_ALL);

	C_Point punkt(100,200);
	C_Point punkt_kopia;

	pantheios::log(pantheios::debug, PSTR("Entering main()"));
	// przyk�ad z do��czanie linii i nazwy plik�w, wymaga trace.h
	PANTHEIOS_TRACE_DEBUG(PSTR("debug"));
    pantheios::log_INFORMATIONAL(PSTR("informational"));
    pantheios::log_NOTICE(PSTR("notice"));
    pantheios::log_WARNING(PSTR("warning"));
    pantheios::log_ERROR(PSTR("error"));
    pantheios::log_CRITICAL(PSTR("critical"));
    pantheios::log_ALERT(PSTR("alert"));
    pantheios::log_EMERGENCY(PSTR("EMERGENCY"));
	
	cout << "x= " << punkt.getX() << ", y= " << punkt.getY() << endl;
	punkt.setPoint(1,2);
	punkt_kopia = punkt;
	cout << "x= " << punkt_kopia.getX() << ", y= " << punkt_kopia.getY() << endl;


	// Close all files, by setting the path to NULL.
    pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);

	// to ju� si� w logu pliku nie pojawi
    pantheios::log_NOTICE(PSTR("stmt 4"));
	return(0);
}
