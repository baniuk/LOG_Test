/**
*	\file LOG_test.cpp
*	\author PB
*	\brief Main file
*	\details
*	This file calls all modules and it is main entry point to the application. Creates multiplexed log according to severity level
*/

#include <iostream>
#include <platformstl/platformstl.h>                /* for platform discrimination */

// pliki nag³ówkowe do funkcji - nie myliæ z linkowaniem dynamicznym poni¿ej
#include <pantheios/pantheios.hpp>
#include <pantheios/backends/be.N.h>
#include <pantheios/backends/bec.file.h>
#include <pantheios/backends/bec.fprintf.h>
// simple - chyba tylko w debug, all zawsze ?? http://sourceforge.net/projects/pantheios/forums/forum/475314/topic/2186546
// N - If you use fe.simple, then all log statements whose severity is less than (=== more severe than, since lower means more severe) the active ceiling will go to all back-ends. 
// The "active ceiling" defaults to PANTHEIOS_SEV_DEBUG (meaning all statements are emitted) in debug builds, and to PANTHEIOS_SEV_NOTICE (meaning all statements with severity emergency, alert, critical, error, 
// warning and notice are emitted) in release builds. You may change the "active ceiling" at any time using pantheios_fe_simple_setSeverityCeiling()
// If you use fe.N, then each log statement may be subjected to filtering on a per-back-end basis, as defined by the contents of the PAN_FE_N_SEVERITY_CEILINGS array.
#include <pantheios/frontends/fe.N.h>

// Biblioteki ³¹czone dynamicznie, nie trzeba wpisywac ich nazwy. Dla UNIXA moze byæ inaczej. Przyk³ad rozpoznania:
// http://www.pantheios.org/doc/html/c_2example_8c_8N_2example_8c_8N_8c-example.html#a10
// Trzeba pilnowac co siê ³¹czy, biblioteki s¹ zamienne ale program mo¿e inaczej dzia³aæ. Na przyk³ad jesli zamiast fe.N do³¹czy siê fe.simple to do obu Ÿróde³ pójdzie to samo bez filtrowania
#include <pantheios/implicit_link/core.h>
#include <pantheios/implicit_link/fe.N.h>
#include <pantheios/implicit_link/be.N.h>
// dla windows jest to windowsconsole, dla unixa to fprinf
//  http://binglongx.wordpress.com/2010/08/30/pantheios-logging-library-installation-and-use/
#include <pantheios/implicit_link/be.file.h>
#include <pantheios/implicit_link/be.fprintf.h>

// http://sourceforge.net/projects/pantheios/forums/forum/475314/topic/2186546
// 
/// Konwersja ci¹gów wymagana przez Pantheios
#ifndef PSTR
	#define PSTR(x)         PANTHEIOS_LITERAL_STRING(x)
#endif

/// Typ wyliczeniowy okreslaj¹cy cele logów
enum LOGI 
{  
	File = 1,  /**< Logowanie do pliku */
	Console = 2  /**< Logowanie do konsoli */
}; 

// nazwa aplikacji do logów
extern "C" const char PANTHEIOS_FE_PROCESS_IDENTITY[] = "LOG_test";

/**
 * \brief Struktura okreœlaj¹ca minimalny poziom b³edu który trafia do danego logu
 * 
 * DEBUG jest poziomem najni¿szym, co znaczy ¿e do pliku trafi wszystko. Ta struktura dzia³a
 * jedynie gdy linkuje siê do biblioteki be.N. Kolejnoœæ b³êdów:
 * -# DEBUG
 * -# INFORMATIONAL
 * -# NOTICE
 * -# WARNING
 * -# ERROR
 * -# CRITICAL
 * -# ALERT
 * -# EMERGENCY
 * \n
 * Do konsoli trafi wszystko powy¿ej ERROR
 */ 
 pan_fe_N_t PAN_FE_N_SEVERITY_CEILINGS[]  =
{
	{ File,  PANTHEIOS_SEV_DEBUG    } 
	, { Console,  PANTHEIOS_SEV_ERROR     } 
	, PANTHEIOS_FE_N_TERMINATOR_ENTRY(PANTHEIOS_SEV_CRITICAL)
};

/**  
 * \brief Struktura ³¹cz¹ca poziom b³edu z konkretnym wyjœciem
 * 
 * LOGI::File i LOGI::Console ³¹cz¹ siê z pozycjami w PAN_FE_N_SEVERITY_CEILINGS
 */ 
pan_be_N_t PAN_BE_N_BACKEND_LIST[] =
{
	PANTHEIOS_BE_N_STDFORM_ENTRY(File, pantheios_be_file, 0)
	, PANTHEIOS_BE_N_STDFORM_ENTRY(Console, pantheios_be_fprintf, 0)
	, PANTHEIOS_BE_N_TERMINATOR_ENTRY
};

int main(void)
{
	pantheios_be_file_setFilePath(PSTR("file-1.log"), PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BEID_ALL);

	pantheios::log(pantheios::debug, "Entering main()");
	pantheios::log_DEBUG("debug");
    pantheios::log_INFORMATIONAL("informational");
    pantheios::log_NOTICE("notice");
    pantheios::log_WARNING("warning");
    pantheios::log_ERROR("error");
    pantheios::log_CRITICAL("critical");
    pantheios::log_ALERT("alert");
    pantheios::log_EMERGENCY("EMERGENCY");

	// Close all files, by setting the path to NULL.
    pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);

	// to ju¿ siê w logu pliku nie pojawi
    pantheios::log_NOTICE(PSTR("stmt 4"));

	return(0);
}
