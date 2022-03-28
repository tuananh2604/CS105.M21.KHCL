#include "pch.h"
#include "Circle.h"
#include "math.h"

#define Round(x) int(x + 0.5)

void Circle::Midpoint(CDC* pDC, CPoint c, float r, COLORREF color)
{
	Circle::Midpoint(pDC, c.x, c.y, r, color);
}

void Circle::Midpoint(CDC* pDC, int xc, int yc, float r, COLORREF color)
{
	if (r == 0)
	{
		pDC->SetPixel(xc, yc, color);
	}
	else
	{
		Circle::_Midpoint(pDC, xc, yc, r, color);
	}
}


void Circle::_Midpoint(CDC* pDC, int xc, int yc, float r, COLORREF color)
{
	float f = -r + 1 / 4;
	int x = 0;
	float y = r;
	float a = sqrt(2);
	while (x <= r / a)
	{
		pDC->SetPixel(Round(x + xc), Round(y + yc), color);
		pDC->SetPixel(Round(x + xc), Round(-y + yc), color);
		pDC->SetPixel(Round(-x + xc), Round(y + yc), color);
		pDC->SetPixel(Round(-x + xc), Round(-y + yc), color);
		pDC->SetPixel(Round(y + xc), Round(x + yc), color);
		pDC->SetPixel(Round(y + xc), Round(-x + yc), color);
		pDC->SetPixel(Round(-y + xc), Round(x + yc), color);
		pDC->SetPixel(Round(-y + xc), Round(-x + yc), color);

		/*x++;
		y = sqrt(pow(r, 2) - pow(x, 2));*/
		if (f < 0)
		{
			f += 2 * x + 3;
			x++;
		}
		else
		{
			f += 2 * x - 2 * y + 5;
			x++;
			y--;
		}
	}
}
