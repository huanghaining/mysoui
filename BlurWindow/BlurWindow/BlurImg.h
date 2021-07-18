#pragma once

using namespace SOUI;

#include "matrix/SMatrix.h"

namespace SOUI{

	class SBlurImg : public SImageWnd
	{
		SOUI_CLASS_NAME(SBlurImg, L"blurimage")

	public:
		SBlurImg();

		enum { TIMER_REFRESH = 1 };

	protected:
		//SMatrix InitMatrix(double angle, CPoint &center);

		//double GetMinuteSecondAngle(int nValue);
		//double GetHourAngle(int nHour, int nMinute);

	protected:
		int  OnCreate(void*);
		void OnPaint(SOUI::IRenderTarget * pRT);
		//void OnTimer(char cTimerID);

		SOUI_MSG_MAP_BEGIN()
			MSG_WM_PAINT_EX(OnPaint)
			//MSG_WM_TIMER_EX(OnTimer)
			MSG_WM_CREATE(OnCreate)
			SOUI_MSG_MAP_END()

	protected:
		SOUI_ATTRS_BEGIN()
			ATTR_IMAGEAUTOREF(L"m_bkg", m_bkg, TRUE)
		SOUI_ATTRS_END()

		SAutoRefPtr<IBitmap> m_bkg;
		static int m_index ;
		int obj_index = 0;
	};

}