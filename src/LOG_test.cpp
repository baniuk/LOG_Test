/**
*	\file LOG_test.cpp
*	\author PB
*	\brief Main file
*	\details
*	This file calls all modules and it is main entry point to the application. Creates multiplexed log according to severity level
*/

#include <iostream>
#include <Pantheios_header.h>

// Biblioteki inne
#include "C_Point.h"

/// Typ wyliczeniowy okreslaj�cy cele log�w
enum LOGI {
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
pan_fe_N_t PAN_FE_N_SEVERITY_CEILINGS[]  = {
    { File,  PANTHEIOS_SEV_DEBUG    }
    , { Console,  PANTHEIOS_SEV_ERROR     }
    , PANTHEIOS_FE_N_TERMINATOR_ENTRY(PANTHEIOS_SEV_CRITICAL)
};

/**
 * \brief Struktura ��cz�ca poziom b�edu z konkretnym wyj�ciem
 *
 * LOGI::File i LOGI::Console ��cz� si� z pozycjami w PAN_FE_N_SEVERITY_CEILINGS
 */
pan_be_N_t PAN_BE_N_BACKEND_LIST[] = {
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

    cout << PSTR("x= ") << punkt.getX() << PSTR(", y= ") << punkt.getY() << endl;
    punkt.setPoint(1,2);
    punkt_kopia = punkt;
    cout << PSTR("x= ") << punkt_kopia.getX() << PSTR(", y= ") << punkt_kopia.getY() << endl;


    // Close all files, by setting the path to NULL.
    pantheios_be_file_setFilePath(NULL, PANTHEIOS_BEID_ALL);

    // to ju� si� w logu pliku nie pojawi
    pantheios::log_NOTICE(PSTR("stmt 4"));
    return(0);
}
