/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"


#ifndef _Label_Decorator_h
#define _Label_Decorator_h


#include "Decorator.h"

class SetDecoratorTextDialog;
class Dictionary;

#define ClassLabelDecorator	"LabelDecorator"

class LabelDecorator : public Decorator
{

  // P R I V A T E   P R I V A T E   P R I V A T E
  // P R I V A T E   P R I V A T E   P R I V A T E
  private:
    static bool LabelDecoratorClassInitialized;

    // D R A G - N - D R O P
    // D R A G - N - D R O P
    static Dictionary *DragTypeDictionary;
    //static Widget      DragIcon;

    //
    // stores various techniques for printing/parsing text
    //
    static Dictionary *CommentStyleDictionary;

  // P R O T E C T E D   P R O T E C T E D   P R O T E C T E D   
  // P R O T E C T E D   P R O T E C T E D   P R O T E C T E D   
  protected:
    //XmString      	   labelString;
    //static  String 	   DefaultResources[]; 
    char 		   font[20];
    Dictionary*		   otherStrings;

    virtual void 	   completeDecorativePart();

    SetDecoratorTextDialog *setTextDialog;
   
    //
    // There is a protected constructor so that the name can be supplied by
    // subclasses.  This is an unusual class in that it can be subclassed and
    // instantiated directly.
    //
    LabelDecorator(bool developerStyle, const char *name);

    static void BuildTheCommentStyleDictionary();
    virtual Dictionary* getCommentStyleDictionary() { 
	return LabelDecorator::CommentStyleDictionary;
    }

    static char* UnFilterString(char*, int*);

  // P U B L I C   P U B L I C   P U B L I C
  // P U B L I C   P U B L I C   P U B L I C
  public:
    static    Decorator*     AllocateDecorator (bool devStyle);
    virtual   void	     openDefaultWindow();
    virtual   bool        hasDefaultWindow() { return true; }
    virtual   Dialog*	     getDialog() { return (Dialog*)this->setTextDialog; }
    virtual   void           setAppearance (bool developerStyle);
    virtual   void           uncreateDecorator();
    virtual   void	     associateDialog(Dialog*);


    // G E O M E T R Y   A N D   R E S O U R C E S
    // G E O M E T R Y   A N D   R E S O U R C E S
    virtual   void 	     setLabel(const char *newStr, bool re_layout = true);
    virtual   void	     setFont(const char *);
	      const char *   getFont() { return this->font; }
    //virtual   void	     setArgs (Arg *args, int *n);
	      const char *   getLabelValue();
	      const char *   getLabel();
	      bool	     acceptsLayoutChanges() { return false; }
	      //XmFontList     getFontList();

    // C O N T R O L   P A N E L   C O M M E N T   F U N C T I O N S
    // C O N T R O L   P A N E L   C O M M E N T   F U N C T I O N S
    virtual   bool	     printComment (FILE *f);
    virtual   bool	     parseComment (const char *comment, 
					      const char *filename, int line);

    //
    // Record/Retrieve ancillary text
    //
    const char* getOtherString(const char* keyword);
    void        setOtherString(const char* keyword, const char* value);

    //
    // Support for a subclass which needs to tickle the vpe after the dialog
    // assigns new text.
    //
    virtual void    postTextGrowthWork(){}

    // J A V A     J A V A     J A V A     J A V A     J A V A     
    // J A V A     J A V A     J A V A     J A V A     J A V A     
    virtual bool printAsJava(FILE* , const char*, int);
    virtual bool printJavaResources(FILE* , const char*, const char*);

    // D R A G - N - D R O P
    // D R A G - N - D R O P
    virtual Dictionary* getDragDictionary() { return LabelDecorator::DragTypeDictionary; }
    //virtual bool     decodeDragType (int, char *, XtPointer *, unsigned long *, long);

    // T H E   T H I N G S   W E   U S E   A L L   T H E   T I M E
    // T H E   T H I N G S   W E   U S E   A L L   T H E   T I M E
    // T H E   T H I N G S   W E   U S E   A L L   T H E   T I M E
    virtual   void initialize();
    	  	   LabelDecorator(bool developerStyle =true);
    	  	  ~LabelDecorator(); 
    const    char* getClassName() { return ClassLabelDecorator; }
    virtual  bool isA(Symbol classname);
};


#endif // _Label_Decorator_h
