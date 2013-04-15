// C_Point_TEST.cpp : Defines the entry point for the console application.
//
#include <gtest/gtest.h>
#include <C_Point.h>

/// Typ wyliczeniowy okreslaj�cy cele log�w
enum LOGI 
{  
	File = 1,  /**< Logowanie do pliku */
	Console = 2  /**< Logowanie do konsoli */
}; 

// nazwa aplikacji do log�w - poniewa� Package1 linkuje si� do Panth. to tu trzeba tez zadeklarowac te sprawy
PANTHEIOS_EXTERN_C const PAN_CHAR_T PANTHEIOS_FE_PROCESS_IDENTITY[] = PSTR("TEST_Package1");

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

int main(int argc, char* argv[])
{
	// w��czenie logowania
	pantheios_be_file_setFilePath(PSTR("TEST_Package1.log"), PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BE_FILE_F_TRUNCATE, PANTHEIOS_BEID_ALL);
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

