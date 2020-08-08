#pragma once

class CDibujo : public CStatic
{
	DECLARE_DYNAMIC(CDibujo)
public:
	CDibujo(int pos,int nopos);
	virtual ~CDibujo();
protected:
	HBITMAP m_bmpos,m_bmnopos;
	int m_pos,m_npos;

	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
};


