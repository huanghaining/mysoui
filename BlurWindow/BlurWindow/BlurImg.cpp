#include "stdafx.h"
#include "BlurImg.h"


namespace SOUI{
	int SBlurImg::m_index = 0;
	SBlurImg::SBlurImg()
	{
		obj_index = ++m_index;
		IBitmap * pImg = NULL;
		GETRENDERFACTORY->CreateBitmap(&m_bkg);

		//m_bkg->LoadFromFile(L"E:\\source\\soui-master\\BlurWindow\\uires\\image\\3.png");
	}
	//void draw(SkCanvas *canvas){

	//	//基础数据
	//	const int offsetX = 10;
	//	const int offsetY = 10;
	//	const int sigmaX = 10;
	//	const int sigmaY = 10;
	//	SkPoint rectPts[] = { { 64, 48 }, { 192, 160 } };
	//	SkRect rect;
	//	rect.set(rectPts[0], rectPts[1]);
	//	SkPath path;
	//	path.addRect(rect);

	//	//-----------------------------------------

	//	//原始图形绘制
	//	SkPictureRecorder recorder;
	//	SkCanvas *recordingCanvas = recorder.beginRecording(rect);
	//	SkPaint paint;
	//	paint.setAntiAlias(true);
	//	paint.setStyle(SkPaint::kStrokeAndFill_Style);
	//	paint.setColor(SK_ColorRED);
	//	recordingCanvas->drawPath(path, paint);
	//	paint.setColor(SK_ColorBLUE);
	//	SkMatrix mat;
	//	mat.postTranslate(20, 20);
	//	path.transform(mat);
	//	recordingCanvas->drawPath(path, paint);
	//	sk_sp<SkPicture> playback = recorder.finishRecordingAsPicture();

	//	//---------------------------------------

	//	//图层绘制
	//	SkPaint layerPaint;
	//	layerPaint.setAntiAlias(true);
	//	layerPaint.setStyle(SkPaint::kStrokeAndFill_Style);
	//	//layerPaint.setColor(SK_ColorBLUE);
	//	layerPaint.setImageFilter(SkImageFilters::Blur(sigmaX, sigmaY, nullptr, nullptr));
	//	canvas->drawPicture(playback, nullptr, &layerPaint);
	//	//---------------------------------------
	//}
	//void draw()
	//{
	//	SkCanvas* SkPictureRecorder::beginRecording(int width, int height,
	//		SkBBHFactory* bbhFactory /* = NULL */,
	//		uint32_t recordFlags /* = 0 */) {
	//		this->reset();  // terminate any prior recording(s)
	//		fWidth = width;
	//		fHeight = height;

	//		const SkISize size = SkISize::Make(width, height);

	//		if (NULL != bbhFactory) {
	//			SkAutoTUnref<SkBBoxHierarchy> tree((*bbhFactory)(width, height));
	//			SkASSERT(NULL != tree);
	//			fPictureRecord = SkNEW_ARGS(SkBBoxHierarchyRecord, (size, recordFlags, tree.get()));
	//		}
	//		else {
	//			fPictureRecord = SkNEW_ARGS(SkPictureRecord, (size, recordFlags));
	//		}

	//		fPictureRecord->beginRecording();
	//		return this->getRecordingCanvas();
	//	}
	//	
	//	
	//}

	
		

	void SBlurImg::OnPaint(SOUI::IRenderTarget * pRT)
	{
		/*__super::OnPaint(pRT);
		if (m_index == 1)
		{
		;
		}*/
	
			CRect rcClient;
			GetClientRect(&rcClient);
			//演示使用IMaskFilter
			SAutoRefPtr<IMaskFilter> maskFilter;
			/*SAutoRefPtr<IPen> br, oldBr;
			pRT->CreatePen(PS_DASHDOTDOT, RGBA(200, 128, 128, 128), 10, &br);
			pRT->SelectObject(br, (IRenderObj**)&oldBr);*/
			GETRENDERFACTORY->CreateBlurMaskFilter(20, IMaskFilter::kInner_SkBlurStyle, IMaskFilter::kHighQuality_BlurFlag, &maskFilter);
			pRT->SetMaskFilter(maskFilter);
			//pRT->DrawBitmapEx(&m_bkg,);
			pRT->SetAntiAlias(true);
			
			//pRT->DrawBitmap(rcClient, m_bkg, rcClient.left,rcClient.top,  255);
			std::wstring objName = this->GetName();
			/*if (obj_index == 1 || obj_index == 3)
			{
				pRT->SetMaskFilter(NULL);
			}*/
			//pRT->SelectObject(oldBr);

	}
	//	CRect rcClient;
	//	GetClientRect(&rcClient);
	//	rcClient.DeflateRect(5, 5, 5, 5);
	//	CPoint center = rcClient.CenterPoint();

	//	// 计算矩形
	//	// 35 * 16
	//	CRect rcDraw(center, SOUI::CPoint(center.x + 200, center.y + 32));
	//	rcDraw.OffsetRect(-35, -16);
	//	CRect rcSrc(0, 0, 200, 32);


	//	//演示使用IMaskFilter
	//	SAutoRefPtr<IMaskFilter> maskFilter;
	//	SAutoRefPtr<IPen> br, oldBr;
	//	pRT->CreatePen(PS_SOLID, RGBA(200, 128, 128, 128), 10, &br);
	//	pRT->SelectObject(br, (IRenderObj**)&oldBr);
	//	GETRENDERFACTORY->CreateBlurMaskFilter(5, IMaskFilter::kNormal_SkBlurStyle, IMaskFilter::kAll_BlurFlag, &maskFilter);
	//	pRT->SetMaskFilter(maskFilter);
	//	pRT->DrawEllipse(&rcClient);
	//	//pRT->SetMaskFilter(NULL);
	//	pRT->SelectObject(oldBr);

	//	SYSTEMTIME last_refresh_time;
	//	::GetLocalTime(&last_refresh_time);

	//	DWORD mode = MAKELONG(EM_STRETCH, kHigh_FilterLevel);
	//	{
	//		double angle = GetHourAngle(last_refresh_time.wHour, last_refresh_time.wMinute);
	//		SMatrix matrix = InitMatrix(angle, center);
	//		pRT->SetTransform(matrix.GetData(), NULL);
	//		pRT->DrawBitmapEx(rcDraw, pointer_hour, &rcSrc, mode, 255);
	//	}

	//{
	//	double angle = GetMinuteSecondAngle(last_refresh_time.wMinute);
	//	SMatrix matrix = InitMatrix(angle, center);
	//	pRT->SetTransform(matrix.GetData(), NULL);
	//	pRT->DrawBitmapEx(rcDraw, pointer_minute, &rcSrc, mode, 255);
	//}

	//{
	//	double angle = GetMinuteSecondAngle(last_refresh_time.wSecond);
	//	SMatrix matrix = InitMatrix(angle, center);
	//	pRT->SetTransform(matrix.GetData(), NULL);
	//	pRT->DrawBitmapEx(rcDraw, pointer_second, &rcSrc, mode, 255);
	//}
	//pRT->SetTransform(SMatrix().GetData());
	//}

	//SMatrix SBlurImg::InitMatrix(double angle, CPoint &center)
	//{
	//	SMatrix mtx;
	//	mtx.setRotate(angle - 90, center.x, center.y);
	//	return mtx;
	//}


	//double SBlurImg::GetMinuteSecondAngle(int nValue)
	//{
	//	return (double)nValue * ((double)360 / 60);
	//}

	//double SBlurImg::GetHourAngle(int nHour, int nMinute)
	//{
	//	double base = (double)(nHour % 12) * ((double)360 / 12);
	//	base += (double)nMinute * ((double)360 / 12 / 60);
	//	return base;
	//}

	//void SBlurImg::OnTimer(char cTimerID)
	//{
	//	Invalidate();
	//}

	int SBlurImg::OnCreate(void*)
	{
		//SetTimer(TIMER_REFRESH, 200);
		return 0;
	}

}