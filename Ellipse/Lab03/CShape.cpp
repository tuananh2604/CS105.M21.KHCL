#include "pch.h"
#include "CShape.h"
#include "CLine.h"
#include "math.h"
#define Round( a ) (int)(a + 0.5)
const double PI = 3.141592653589793238463;

void CShape::PointReflectionEllipse(CDC* pDC, int x0, int y0, int x, int y, COLORREF color)
{
	pDC->SetPixel(x0 + x, y0 + y, color);
	pDC->SetPixel(x0 + x, y0 - y, color);
	pDC->SetPixel(x0 - x, y0 + y, color);
	pDC->SetPixel(x0 - x, y0 - y, color);
}

void CShape::Pentagon(CDC* pDC, int xc, int yc, int r, COLORREF color)
{
	int x[5];
	int y[5];

	float alpha = -PI / 2;
	float const1 = 2 * PI / 5;
	int i;

	for (i = 0; i < 5; ++i)
	{
		x[i] = r * cos(alpha) + xc;
		y[i] = r * sin(alpha) + yc;
		alpha += const1;
	}

	for (i = 0; i < 4; i++)
		CLine::LineDDA(pDC, x[i], y[i], x[i + 1], y[i + 1], color);
	CLine::LineDDA(pDC, x[4], y[4], x[0], y[0], color);
}
//***********************************************************************************

void CShape::Hexagon(CDC* pDC, int xc, int yc, int r, COLORREF color)
{
	int x[6];
	int y[6];

	float alpha = 0;
	float const1 = PI / 3;

	int i;
	for (i = 0; i < 6; ++i)
	{
		x[i] = r * cos(alpha) + xc;
		y[i] = r * sin(alpha) + yc;
		alpha += const1;
	}

	for (i = 0; i < 5; i++)
		CLine::LineDDA(pDC, x[i], y[i], x[i + 1], y[i + 1], color);
	CLine::LineDDA(pDC, x[5], y[5], x[0], y[0], color);
}
//***********************************************************************************


void CShape::Star(CDC* pDC, CPoint I, int R, COLORREF color, int n)
{
	Star(pDC, I.x, I.y, R, color, n);
}

void CShape::Star(CDC* pDC, int xc, int yc, int R, COLORREF color, int n)
{
	float r = R * sin(PI / (2.0 * n)) / sin(PI - 3 * PI / (2.0 * n));
	int* x = new int[2 * n];
	int* y = new int[2 * n];

	float alpha = -PI / 2;
	float const1 = PI / n;
	float const2 = 2 * PI / n;

	int i;
	for (i = 0; i < 2 * n; i += 2)
	{
		x[i] = R * cos(alpha) + xc;
		y[i] = R * sin(alpha) + yc;
		//x[i+1] = r * cos(alpha) + xc; // Dùng hai dòng này để vẽ phi tiêu
		//y[i+1] = r * sin(alpha) + yc;
		x[i + 1] = r * cos(1.0 * alpha + const1) + xc; //Dùng hai dòng này để vẽ sao như bình thường
		y[i + 1] = r * sin(1.0 * alpha + const1) + yc;

		alpha += const2;
	}

	for (i = 0; i < 2 * n - 1; ++i)
		CLine::LineDDA(pDC, x[i], y[i], x[i + 1], y[i + 1], color);
	CLine::LineDDA(pDC, x[2 * n - 1], y[2 * n - 1], x[0], y[0], color);
}

void CShape::Ellipse(CDC* pDC, int x0, int y0, int a, int b, COLORREF color)
{
	int asqr = a * a;
	int bsqr = b * b;

	int x = 0;
	int y = b;

	int p = Round(asqr / 4) + bsqr - asqr * b;
	int px = 0;
	int py = 2 * asqr * y;


	PointReflectionEllipse(pDC, x0, y0, x, y, color);

	while (px < py) {

		x++;

		px += 2 * bsqr;

		if (p < 0) {

			p += bsqr + px;

		}
		else {

			y--;

			py -= 2 * asqr;

			p += bsqr + px - py;

		}

		PointReflectionEllipse(pDC, x0, y0, x, y, color);

	}

	p = bsqr * (x + 0.5) * (x + 0.5) + asqr * (y - 1) * (y - 1) - asqr * bsqr;
	while (y > 0)
	{
		y--;

		py -= 2 * asqr;

		if (p > 0) {

			p += asqr - py;

		}
		else {

			x++;

			px += 2 * bsqr;

			p += asqr - py + px;

		}

		PointReflectionEllipse(pDC, x0, y0, x, y, color);
	}
}
