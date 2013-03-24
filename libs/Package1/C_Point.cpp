#include <C_Point.h>

C_Point::C_Point( double _x, double _y ) :
	x0(_x),
	y0(_y)
{
	PANTHEIOS_TRACE_DEBUG(PSTR("Entering"));
	PANTHEIOS_TRACE_DEBUG(PSTR("x = "),pantheios::real(x0),PSTR(" y = "),pantheios::real(y0));
	PANTHEIOS_TRACE_DEBUG(PSTR("Leaving"));
}

C_Point::C_Point() :
	x0(0),
	y0(0)
{

}

C_Point::~C_Point()
{

}

void C_Point::CopyToDest( C_Point &dest ) const
{
	dest.x0 = x0;
	dest.y0 = y0;
}

void C_Point::setPoint( double _x, double _y )
{
	// http://www.pantheios.org/doc/html/group__group____application__layer__interface____inserters.html
	PANTHEIOS_TRACE_DEBUG(PSTR("Entering"));
	x0 = _x;	
	y0 = _y;
	PANTHEIOS_TRACE_DEBUG(PSTR("x = "),pantheios::real(x0),PSTR(" y = "),pantheios::real(y0));
	PANTHEIOS_TRACE_DEBUG(PSTR("Leaving"));
}

void C_Point::getPoint( double &_x, double &_y ) const
{
	_x = x0;
	_y = y0;
}

C_Point& C_Point::operator=( const C_Point &rhs )
{
	PANTHEIOS_TRACE_DEBUG(PSTR("Entering"));
	rhs.getPoint(x0,y0);
	PANTHEIOS_TRACE_DEBUG(PSTR("Returned pointer "), pantheios::pointer(this,pantheios::fmt::fullHex));
	PANTHEIOS_TRACE_DEBUG(PSTR("Leaving"));
	return *this;
}

C_Point& C_Point::operator+=( const C_Point &rhs )
{
	double x,y;
	rhs.getPoint(x,y);
	this->setPoint(x0+x,y0+y);
	return *this;
}

C_Point& C_Point::operator-=( const C_Point &rhs )
{
	double x,y;
	rhs.getPoint(x,y);
	this->setPoint(x0-x,y0-y);
	return *this;
}

const C_Point C_Point::operator+( const C_Point &rhs ) const
{
	C_Point result = *this;
	result+=rhs;
	return result;
}

const C_Point C_Point::operator-( const C_Point &rhs ) const
{
	C_Point result = *this;
	result-=rhs;
	return result;
}

C_Point& C_Point::operator/=( double rhs )
{
	x0/=rhs;
	y0/=rhs;
	return *this;
}

C_Point& C_Point::operator*=( double rhs )
{
	x0*=rhs;
	y0*=rhs;
	return *this;
}

