/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#include "ImageWindow.h"
#include "RenderingOptionsDialog.h"
#include "ToggleButtonInterface.h"
#include "ButtonInterface.h"


bool RenderingOptionsDialog::ClassInitialized = false;

RenderingOptionsDialog::RenderingOptionsDialog(
				     ImageWindow *w):
			    Dialog("renderingOptions")
{

    if (NOT RenderingOptionsDialog::ClassInitialized)
    {
        RenderingOptionsDialog::ClassInitialized = true;
	//this->installDefaultResources(theApplication->getRootWidget());
    }
    this->imageWindow = w;
}

RenderingOptionsDialog::~RenderingOptionsDialog()
{
    if (this->isManaged())
	this->unmanage();

    if (this->upNone) 		delete this->upNone;
    if (this->upWireframe) 	delete this->upWireframe;
    if (this->upDots) 		delete this->upDots;
    if (this->upBox) 		delete this->upBox;
    if (this->downNone) 	delete this->downNone;
    if (this->downWireframe) 	delete this->downWireframe;
    if (this->downDots) 	delete this->downDots;
    if (this->downBox) 		delete this->downBox;
    if (this->hardwareButton) 	delete this->hardwareButton;
    if (this->softwareButton) 	delete this->softwareButton;
}

//Widget RenderingOptionsDialog::createUpPulldown(Widget parent)
//{
//    Widget pulldown = XmCreatePulldownMenu(parent, "upPulldownMenu",
//	NULL, 0);
//    this->upNone = new ButtonInterface(pulldown, 
//	"upNone", this->imageWindow->getUpNoneCmd());
//    this->upWireframe = new ButtonInterface(pulldown, 
//	"upWireframe", this->imageWindow->getUpWireframeCmd());
//    this->upDots = new ButtonInterface(pulldown, 
//	"upDots", this->imageWindow->getUpDotsCmd());
//    this->upBox = new ButtonInterface(pulldown, 
//	"upBox", this->imageWindow->getUpBoxCmd());
//    return pulldown;
//}
//Widget RenderingOptionsDialog::createDownPulldown(Widget parent)
//{
//    Widget pulldown = XmCreatePulldownMenu(parent, "downPulldownMenu",
//	NULL, 0);
//    this->downNone = new ButtonInterface(pulldown, 
//	"downNone", this->imageWindow->getDownNoneCmd());
//    this->downWireframe = new ButtonInterface(pulldown, 
//	"downWireframe", this->imageWindow->getDownWireframeCmd());
//    this->downDots = new ButtonInterface(pulldown, 
//	"downDots", this->imageWindow->getDownDotsCmd());
//    this->downBox = new ButtonInterface(pulldown, 
//	"downBox", this->imageWindow->getDownBoxCmd());
//    return pulldown;
//}


void RenderingOptionsDialog::createDialog()
{
//    Arg arg[10];
//    ImageWindow *iw = this->imageWindow;
//
//    XtSetArg(arg[0], XmNautoUnmanage, False);
////    Widget dialog = XmCreateFormDialog( parent, this->name, arg, 1);
//    Widget dialog = this->CreateMainForm( parent, this->name, arg, 1);
//
//    XtVaSetValues(XtParent(dialog), XmNtitle, "Rendering...", NULL);
//
//    Widget modeLabel = XtVaCreateManagedWidget(
//	"modeLabel", xmLabelWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_FORM,
//        XmNtopOffset       , 10,
//        XmNleftAttachment  , XmATTACH_FORM,
//        XmNleftOffset      , 5,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 5,
//	NULL);
//
//    Widget modeSection = XtVaCreateManagedWidget(
//	"modeSection", xmRowColumnWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , modeLabel,
//        XmNtopOffset       , 10,
//        XmNleftAttachment  , XmATTACH_FORM,
//        XmNleftOffset      , 5,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 5,
//
//        XmNorientation     , XmHORIZONTAL,
//        XmNspacing         , 21,
//        XmNmarginWidth     , 21,
//        XmNradioBehavior   , True,
//	NULL);
//
//    this->softwareButton = new ToggleButtonInterface(modeSection,
//	  "softwareButton", iw->getSoftwareCmd(), true);
//    XtVaSetValues(this->softwareButton->getRootWidget(),
//        XmNindicatorType   , XmONE_OF_MANY,
//        XmNshadowThickness , 0,
//	NULL);
//    this->hardwareButton = new ToggleButtonInterface(modeSection,
//	  "hardwareButton", iw->getHardwareCmd(), false);
//    XtVaSetValues(this->hardwareButton->getRootWidget(),
//        XmNindicatorType   , XmONE_OF_MANY,
//        XmNshadowThickness , 0,
//	NULL);
//
//    Widget separator1 = XtVaCreateManagedWidget(
//	"separator1", xmSeparatorWidgetClass, dialog,
//        XmNtopAttachment    , XmATTACH_WIDGET,
//        XmNtopWidget        , modeSection,
//        XmNtopOffset        , 10,
//        XmNleftAttachment   , XmATTACH_FORM,
//        XmNleftOffset       , 2,
//        XmNrightAttachment  , XmATTACH_FORM,
//        XmNrightOffset      , 2,
//	NULL);
//
//    Widget upLabel = XtVaCreateManagedWidget(
//	"upLabel", xmLabelWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , separator1,
//        XmNtopOffset       , 10,
//        XmNleftAttachment  , XmATTACH_FORM,
//        XmNleftOffset      , 5,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 5,
//	NULL);
//
//    Widget upApproxLabel = XtVaCreateManagedWidget(
//	"upApproxLabel", xmLabelWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , upLabel,
//        XmNtopOffset       , 10,
//        XmNleftAttachment  , XmATTACH_FORM,
//        XmNleftOffset      , 5,
//	NULL);
//
//#if defined(aviion)
//    XmString xmstr = XmStringCreateLtoR ("", "bold");
//#endif
//    Widget upPulldown = this->createUpPulldown(dialog);
//    Widget buttonUpOptionMenu = this->buttonUpOptionMenu =
//	     XtVaCreateManagedWidget(
//	"buttonUpOptionMenu", xmRowColumnWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , upLabel,
//        XmNtopOffset       , 10,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 2,
//        XmNentryAlignment  , XmALIGNMENT_CENTER,
//	XmNrowColumnType   , XmMENU_OPTION,
//	XmNsubMenuId       , upPulldown,
//#if defined(aviion)
//	XmNlabelString     , xmstr,
//#endif
//	NULL);
//
//    Widget upDensityLabel = XtVaCreateManagedWidget(
//	"upDensityLabel", xmLabelWidgetClass, dialog,
//        XmNtopAttachment  , XmATTACH_WIDGET,
//        XmNtopWidget      , buttonUpOptionMenu,
//        XmNtopOffset      , 10,
//        XmNleftAttachment , XmATTACH_FORM,
//        XmNleftOffset     , 5,
//	NULL);
//
//    this->upEveryNumber = XtVaCreateManagedWidget(
//       "upEveryNumber", xmNumberWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , buttonUpOptionMenu,
//        XmNtopOffset       , 10,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 5,
//        XmNiMinimum        , 1,
//        XmNiMaximum        , 1000000,
//        XmNrecomputeSize   , False,
//        XmNdataType        , INTEGER,
//        XmNcharPlaces      , 7,
//        XmNeditable        , True,
//	NULL);
//    XtAddCallback(this->upEveryNumber, XmNactivateCallback,
//        (XtCallbackProc)RenderingOptionsDialog_NumberCB, (XtPointer)this);
//
//
//    Widget separator2 = XtVaCreateManagedWidget(
//	"separator2", xmSeparatorWidgetClass, dialog,
//        XmNtopAttachment    , XmATTACH_WIDGET,
//        XmNtopWidget        , this->upEveryNumber,
//        XmNtopOffset        , 10,
//        XmNleftAttachment   , XmATTACH_FORM,
//        XmNleftOffset       , 2,
//        XmNrightAttachment  , XmATTACH_FORM,
//        XmNrightOffset      , 2,
//	NULL);
//
//    Widget downLabel = XtVaCreateManagedWidget(
//	"downLabel", xmLabelWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , separator2,
//        XmNtopOffset       , 10,
//        XmNleftAttachment  , XmATTACH_FORM,
//        XmNleftOffset      , 5,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 5,
//	NULL);
//
//    Widget downApproxLabel = XtVaCreateManagedWidget(
//	"downApproxLabel", xmLabelWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , downLabel,
//        XmNtopOffset       , 10,
//        XmNleftAttachment  , XmATTACH_FORM,
//        XmNleftOffset      , 5,
//	NULL);
//
//    Widget downPulldown = this->createDownPulldown(dialog);
//    Widget buttonDownOptionMenu = this->buttonDownOptionMenu =
//	     XtVaCreateManagedWidget(
//	"buttonDownOptionMenu", xmRowColumnWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , downLabel,
//        XmNtopOffset       , 10,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 2,
//        XmNentryAlignment  , XmALIGNMENT_CENTER,
//	XmNrowColumnType   , XmMENU_OPTION,
//	XmNsubMenuId       , downPulldown,
//#if defined(aviion)
//	XmNlabelString     , xmstr,
//	NULL);
//    XmStringFree(xmstr);
//#else
//	NULL);
//#endif
//
//    Widget downDensityLabel = XtVaCreateManagedWidget(
//	"downDensityLabel", xmLabelWidgetClass, dialog,
//        XmNtopAttachment  , XmATTACH_WIDGET,
//        XmNtopWidget      , buttonDownOptionMenu,
//        XmNtopOffset      , 10,
//        XmNleftAttachment , XmATTACH_FORM,
//        XmNleftOffset     , 5,
//	NULL);
//
//    this->downEveryNumber = XtVaCreateManagedWidget(
//       "downEveryNumber", xmNumberWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , buttonDownOptionMenu,
//        XmNtopOffset       , 10,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 5,
//        XmNiMinimum        , 1,
//        XmNiMaximum        , 1000000,
//        XmNrecomputeSize   , False,
//        XmNdataType        , INTEGER,
//        XmNcharPlaces      , 7,
//        XmNeditable        , True,
//	NULL);
//    XtAddCallback(this->downEveryNumber, XmNactivateCallback,
//        (XtCallbackProc)RenderingOptionsDialog_NumberCB, (XtPointer)this);
//
//    Widget separator3 = XtVaCreateManagedWidget(
//	"separator3", xmSeparatorWidgetClass, dialog,
//        XmNtopAttachment   , XmATTACH_WIDGET,
//        XmNtopWidget       , this->downEveryNumber,
//        XmNtopOffset       , 10,
//        XmNleftAttachment  , XmATTACH_FORM,
//        XmNleftOffset      , 5,
//        XmNrightAttachment , XmATTACH_FORM,
//        XmNrightOffset     , 5,
//	NULL);
//
//    this->cancel =  XtVaCreateManagedWidget(
//	"closeButton", xmPushButtonWidgetClass, dialog,
//	XmNtopAttachment  , XmATTACH_WIDGET,
//	XmNtopWidget      , separator3,
//	XmNtopOffset      , 10,
//	XmNleftAttachment , XmATTACH_FORM,
//	XmNleftOffset     , 5,
//	XmNbottomAttachment, XmATTACH_FORM,
//	XmNbottomOffset   , 5,
//	XmNrecomputeSize  , False,
//	NULL);
//    
//    this->sensitizeRenderMode(! iw->isRenderModeConnected());
//    this->sensitizeButtonUpApprox(! iw->isButtonUpApproxConnected());
//    this->sensitizeButtonDownApprox(! iw->isButtonDownApproxConnected());
//    this->sensitizeButtonUpDensity(! iw->isButtonUpDensityConnected());
//    this->sensitizeButtonDownDensity(! iw->isButtonDownDensityConnected());
//
//    return dialog;    
}

void RenderingOptionsDialog::manage()
{
 //   Dimension dialogWidth;

 //   if (!XtIsRealized(this->getRootWidget()))
	//XtRealizeWidget(this->getRootWidget());

 //   XtVaGetValues(this->getRootWidget(),
	//XmNwidth, &dialogWidth,
	//NULL);

 //   Position x;
 //   Position y;
 //   Dimension width;
 //   XtVaGetValues(parent,
	//XmNx, &x,
	//XmNy, &y,
	//XmNwidth, &width,
	//NULL);

 //   if (x > dialogWidth + 25)
	//x -= dialogWidth + 25;
 //   else
	//x += width + 25;

 //   Display *dpy = XtDisplay(this->getRootWidget());
 //   if (x > WidthOfScreen(DefaultScreenOfDisplay(dpy)) - dialogWidth)
	//x = WidthOfScreen(DefaultScreenOfDisplay(dpy)) - dialogWidth;
 //   XtVaSetValues(this->getRootWidget(),
	//XmNdefaultPosition, False, 
	//NULL);
 //   XtVaSetValues(XtParent(this->getRootWidget()),
	//XmNdefaultPosition, False, 
	//XmNx, x, 
	//XmNy, y, 
	//NULL);

 //   this->Dialog::manage();

 //   this->resetApproximations();
}

void RenderingOptionsDialog::update()
{  
    this->resetApproximations();

    bool sw;
    this->imageWindow->getSoftware(sw);

    if (sw)
    {
	this->softwareButton->setState(true, false);
	this->hardwareButton->setState(false, false);
    }
    else
    {
	this->softwareButton->setState(false, false);
	this->hardwareButton->setState(true, false);
    }
}


void RenderingOptionsDialog::resetApproximations()
{
 //   ApproxMode mode;
 //   Widget b;

 //   this->imageWindow->getApproximation(true, mode);
 //   switch (mode) {
 //   case APPROX_WIREFRAME:
	//b = this->upWireframe->getRootWidget();
	//break;
 //   case APPROX_DOTS:
	//b = this->upDots->getRootWidget();
	//break;
 //   case APPROX_BOX:
	//b = this->upBox->getRootWidget();
	//break;
 //   case APPROX_NONE:
 //   default:
	//b = this->upNone->getRootWidget();
	//break;
 //   }

 //   if (! b)
	// 
 //   ASSERT(b);
 //   XtVaSetValues(this->buttonUpOptionMenu,
	//XmNmenuHistory, b,
	//NULL);

 //   this->imageWindow->getApproximation(false, mode);
 //   switch (mode) {
 //   case APPROX_WIREFRAME:
	//b = this->downWireframe->getRootWidget();
	//break;
 //   case APPROX_DOTS:
	//b = this->downDots->getRootWidget();
	//break;
 //   case APPROX_BOX:
	//b = this->downBox->getRootWidget();
	//break;
 //   case APPROX_NONE:
 //   default:
	//b = this->upNone->getRootWidget();
	//break;
 //   }
 //   ASSERT(b);
 //   XtVaSetValues(this->buttonDownOptionMenu,
	//XmNmenuHistory, b,
	//NULL);
 //   
 //   int density;
 //   this->imageWindow->getDensity(true, density);
 //   XtVaSetValues(this->upEveryNumber,
	//XmNiValue, density,
	//NULL);
 //   this->imageWindow->getDensity(false, density);
 //   XtVaSetValues(this->downEveryNumber,
	//XmNiValue, density,
	//NULL);
 //   
 //   bool sw;
 //   this->imageWindow->getSoftware(sw);
 //   if (sw)
 //   {
	//this->imageWindow->getUpWireframeCmd()->deactivate();
	//this->imageWindow->getDownWireframeCmd()->deactivate();
	//XtVaSetValues(this->hardwareButton->getRootWidget(),
	//    XmNset, False, NULL);
	//XtVaSetValues(this->softwareButton->getRootWidget(),
	//    XmNset, True, NULL);
	//XtSetSensitive(this->upEveryNumber,  False);
	//XtSetSensitive(this->downEveryNumber,False);
 //   }
 //   else
 //   {
	//this->imageWindow->getUpWireframeCmd()->activate();
	//this->imageWindow->getDownWireframeCmd()->activate();
	//XtVaSetValues(this->hardwareButton->getRootWidget(),
	//    XmNset, True, NULL);
	//XtVaSetValues(this->softwareButton->getRootWidget(),
	//    XmNset, False, NULL);
	//XtSetSensitive(this->upEveryNumber,  True);
	//XtSetSensitive(this->downEveryNumber,True);
 //   }

 //   if (this->imageWindow->isRenderModeConnected())
	//this->sensitizeRenderMode(False);

 //   if (this->imageWindow->isButtonUpApproxConnected())
	//this->sensitizeButtonUpApprox(False);

 //   if (this->imageWindow->isButtonDownApproxConnected())
	//this->sensitizeButtonDownApprox(False);

 //   if (this->imageWindow->isButtonUpDensityConnected())
	//this->sensitizeButtonUpDensity(False);

 //   if (this->imageWindow->isButtonDownDensityConnected())
	//this->sensitizeButtonDownDensity(False);
}
//extern "C" void RenderingOptionsDialog_NumberCB(Widget	 widget,
//				      XtPointer clientData,
//				      XtPointer callData)
//{
//    RenderingOptionsDialog *dialog = (RenderingOptionsDialog*)clientData;
//
//    int v;
//    XtVaGetValues(widget, XmNiValue, &v, NULL);
//
//    if (widget == dialog->upEveryNumber)
//	dialog->imageWindow->setDensity(true, v);
//    else if (widget == dialog->downEveryNumber)
//	dialog->imageWindow->setDensity(false, v);
//}
////
//// Install the default resources for this class.
////
//void RenderingOptionsDialog::installDefaultResources(Widget  baseWidget)
//{
//    this->setDefaultResources(baseWidget,
//				RenderingOptionsDialog::DefaultResources);
//    this->Dialog::installDefaultResources( baseWidget);
//}

void RenderingOptionsDialog::sensitizeRenderMode(bool flag)
{
    if (flag)
    {
	this->softwareButton->activate();
	this->hardwareButton->activate();
    }
    else
    {
	this->softwareButton->deactivate();
	this->hardwareButton->deactivate();
    }
}

void RenderingOptionsDialog::sensitizeButtonUpApprox(bool flag)
{
    //XtSetSensitive(this->buttonUpOptionMenu, flag);
}

void RenderingOptionsDialog::sensitizeButtonDownApprox(bool flag)
{
    //XtSetSensitive(this->buttonDownOptionMenu, flag);
}

void RenderingOptionsDialog::sensitizeButtonUpDensity(bool flag)
{
    //XtSetSensitive(this->upEveryNumber, flag);
}

void RenderingOptionsDialog::sensitizeButtonDownDensity(bool flag)
{
    //XtSetSensitive(this->downEveryNumber, flag);
}
