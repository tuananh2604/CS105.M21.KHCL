#pragma once

class Circle
{
public:
	static void Midpoint(CDC* pDC, CPoint c, float r, COLORREF color);
	static void Midpoint(CDC* pDC, int xc, int yc, float r, COLORREF color);
private:
	static void _Midpoint(CDC* pDC, int xc, int yc, float r, COLORREF color);
};