#pragma once

#pragma once

/*
	Lớp: CLine
	Mô tả: Lớp vẽ đường thẳng
*/

class CLine
{
public:
	static void LineDDA(CDC* pDC, CPoint A, CPoint B, COLORREF color);
	static void LineBresenham(CDC* pDC, CPoint A, CPoint B, COLORREF color);

	static void LineDDA(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void LineBresenham(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
public:
	static void _LineDDA1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void _LineDDA2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);

	static void _LineBresenham1(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
	static void _LineBresenham2(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF color);
};