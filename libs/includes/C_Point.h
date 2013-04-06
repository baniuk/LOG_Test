/**
 * \file    C_Point.h
 * \brief	Definiuje punkt w przestrzeni
 * \author  PB
 * \date    2012/03/01
 */
#ifndef C_Point_h__
#define C_Point_h__


#define _USE_MATH_DEFINES
#include <cmath>

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
// insertes - do konwersji liczb itp
#include <pantheios/inserters/real.hpp>
#include <pantheios/inserters/pointer.hpp>
// gcc nie rozponaje makra __FUNCTION__, ale ma makro __func_, to sa makra standardowe w ANSI C
#ifndef PSTR
	#define PSTR(x)         PANTHEIOS_LITERAL_STRING(x)
#endif
// to musi byc wczesniej przed dolaczeniem trace.h
#ifndef PANTHEIOS_INCL_PANTHEIOS_H_TRACE
	#ifdef __GNUG__ // dla unixa bez nazw funkcji
		#define PANTHEIOS_TRACE_PREFIX  PANTHEIOS_FILELINE_A  
	#else // dla win
		#define PANTHEIOS_TRACE_PREFIX         __FILE__ "(" PANTHEIOS_STRINGIZE(__LINE__) "): " __FUNCTION__ ": "
	#endif
#endif /* PANTHEIOS_INCL_PANTHEIOS_H_TRACE */
#include <pantheios/trace.h>
/** 
 * Klasa implementuj¹ca punkt w przestreni dwuwymiarowej
 */ 
class C_Point
{
public:
	C_Point();
	C_Point(double _x, double _y);
	~C_Point();
	/// kopjuje punkt do innego obiektu dest
	void CopyToDest(C_Point &dest) const;
	/// ustawia wartoœæ punktu
	void setPoint(double _x, double _y);
	/// zwraca wartoœci punktów
	void getPoint(double &_x, double &_y) const;
	/// operator kopiownia
	C_Point& operator=(const C_Point &rhs);
	/// operator odejmowania A-=B
	C_Point& operator-=(const C_Point &rhs);
	/// operator dzielenia z podstawieniem A/=B
	C_Point& operator/=(double rhs);
	/// operator mnozenia z podstawieniem A*=B
	C_Point& operator*=(double rhs);
	/// operator dodawania A+=B
	C_Point& operator+=(const C_Point &rhs);
	/// operator dodawania C=A+B
	const C_Point operator+(const C_Point &rhs) const;
	/// operaor odejmowania C = A-B
	const C_Point operator-(const C_Point &rhs) const;
	// get x
	double getX() const { return x0; }
	// get y
	double getY() const { return y0; }
private:
	double x0, y0;	// wspó³rzêdne punktu

};
#endif // C_Point_h__
