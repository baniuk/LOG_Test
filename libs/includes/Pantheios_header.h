/**
 * \file    Pantheios_header.h
 * \brief	Wsp�ne definicje plik�w nag��wkowtych i makr dla Panthiosa
 * \author  PB
 * \date    2013/04/06
 */
#ifndef Pantheios_header__
#define Pantheios_header__

#include <platformstl/platformstl.h>                /* for platform discrimination */

// pliki nag��wkowe do funkcji - nie myli� z linkowaniem dynamicznym poni�ej
#include <pantheios/pantheios.hpp>

/**
* dodaje do logu nazw� funkcji i linii, musi by� przed trace.h http://stackoverflow.com/questions/2343821/how-to-include-the-calling-class-and-line-number-in-the-log-using-pantheios
* zmiana wygl�du logu: http://www.codeproject.com/Articles/27119/Using-Callback-Back-ends-with-the-Pantheios-Loggin
* to musi byc wczesniej przed dolaczeniem trace.h
* gcc nie rozponaje makra __FUNCTION__, ale ma makro __func_, to sa makra standardowe w ANSI C
*/
#ifndef PANTHEIOS_INCL_PANTHEIOS_H_TRACE
	#ifdef __GNUG__ // dla unixa bez nazw funkcji
		#define PANTHEIOS_TRACE_PREFIX  PANTHEIOS_FILELINE_A  
	#else // dla win
		#define PANTHEIOS_TRACE_PREFIX         __FILE__ "(" PANTHEIOS_STRINGIZE(__LINE__) "): " __FUNCTION__ ": "
	#endif
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
// insertes - do konwersji liczb itp
#include <pantheios/inserters/real.hpp>
#include <pantheios/inserters/pointer.hpp>

// http://sourceforge.net/projects/pantheios/forums/forum/475314/topic/2186546
// 
/// Konwersja ci�g�w wymagana przez Pantheios, w zale�no�ci od ustawie� kompilatora u�ywa poprawnych ci�g�ow
#ifndef PSTR
	#define PSTR(x)         PANTHEIOS_LITERAL_STRING(x)
#endif

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

#endif // Pantheios_header__