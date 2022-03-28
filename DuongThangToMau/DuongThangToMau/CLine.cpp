#include "pch.h"
#include "CLine.h"
#include "math.h"

#define Round(x) (int) (x + 0.5)

void CLine::LineDDA(CDC* pDC, CPoint A, CPoint B, COLORREF color)
{
	LineDDA(pDC, A.x, A.y, B.x, B.y, color);
}

void CLine::LineBresenham(CDC* pDC, CPoint A, CPoint B, COLORREF color)
{
	LineBresenham(pDC, A.x, A.y, B.x, B.y, color);
}

void CLine::LineDDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	if ((x1 == x2) && (y1 == y2))
	{
		pDC->SetPixel(x1, y1, color);
		return;
	}

	if (abs(x2 - x1) >= abs(y2 - y1))
	{
		if (x1 <= x2)
			_LineDDA1(pDC, x1, y1, x2, y2, color);
		else
			_LineDDA1(pDC, x2, y2, x1, y1, color);
	}
	else
	{
		if (y1 <= y2)
			_LineDDA2(pDC, x1, y1, x2, y2, color);
		else
			_LineDDA2(pDC, x2, y2, x1, y1, color);
	}
}

void CLine::LineBresenham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	if ((x1 == x2) && (y1 == y2)) //Nếu 2 điểm trùng nhau
	{
		pDC->SetPixel(x1, y1, color);
		return;
	}

	if (abs(x2 - x1) >= abs(y2 - y1))
	{
		if (x1 <= x2)
			_LineBresenham1(pDC, x1, y1, x2, y2, color);
		else
			_LineBresenham1(pDC, x2, y2, x1, y1, color);
	}
	else
	{
		if (y1 <= y2)
			_LineBresenham2(pDC, x1, y1, x2, y2, color);
		else
			_LineBresenham2(pDC, x2, y2, x1, y1, color);
	}
}

void CLine::_LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	pDC->SetPixel(x1, y1, color);
	float m = float(y2 - y1) / (x2 - x1);
	float y = y1;

	while (x1 < x2)
	{
		x1 += 1;
		y += m;
		pDC->SetPixel(x1, Round(y), color);
	}
}

void CLine::_LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	pDC->SetPixel(x1, y1, color);
	float m = float(x2 - x1) / (y2 - y1);
	float x = x1;

	while (y1 < y2)
	{
		y1 += 1;
		x += m;
		pDC->SetPixel(Round(x), y1, color);
	}
}

void CLine::_LineBresenham1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	int Dx = x2 - x1;
	int Dy = y2 - y1;

	int yStep = (Dy >= 0) ? 1 : -1;

	Dx = abs(Dx);
	Dy = abs(Dy);

	//Giải thuật chính
	int Const1 = Dy << 1; // Const1 = 2 * Dy
	int Const2 = (Dy - Dx) << 1; // Const2 = 2 * (Dy-Dx)
	int p = Const1 - Dx;

	pDC->SetPixel(x1, y1, color);

	for (int i = 0; i < Dx; i++)
	{
		if (p < 0)
			p += Const1;
		else
		{
			p += Const2;
			y1 += yStep;
		}

		++x1;
		pDC->SetPixel(x1, y1, color);
	}
}

void CLine::_LineBresenham2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color)
{
	int Dx = x2 - x1;
	int Dy = y2 - y1;

	int xStep = (Dx >= 0) ? 1 : -1;

	Dx = abs(Dx);
	Dy = abs(Dy);

	int Const1 = Dx << 1;
	int Const2 = (Dy - Dx) << 1;

	int p = 2 * Const1 - Dx;

	pDC->SetPixel(x1, y1, color);

	for (int i = 0; i < Dy; ++i)
	{
		if (p < 0)
			p += Const1;
		else
		{
			p += Const2;
			x1 += xStep;
		}

		++y1;
		pDC->SetPixel(x1, y1, color);
	}
}