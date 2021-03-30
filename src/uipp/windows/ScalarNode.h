/***********************************************************************/
/* Open Visualization Data Explorer                                    */
/* (C) Copyright IBM Corp. 1989,1999                                   */
/* ALL RIGHTS RESERVED                                                 */
/* This code licensed under the                                        */
/*    "IBM PUBLIC LICENSE - Open Visualization Data Explorer"          */
/***********************************************************************/

#include <dxconfig.h>
#include "defines.h"

#ifndef _ScalarNode_h
#define _ScalarNode_h


#include "InteractorNode.h"
#include "StepperInteractor.h"
#include "List.h"

class Network;

//
// Class name definition:
//
#define ClassScalarNode	"ScalarNode"

//
// ScalarNode class definition:
//				
class ScalarNode : public InteractorNode 
{

  private:
    //
    // Private member data:
    //
    bool	vectorType;
    bool	needsRangeCheck;
    int		rangeCheckDeferrals;

    //
    // Adjusts the dimensionality of all attribute components for
    // this->doDimensionalityChange().
    //
    bool adjustAttributeDimensions(int old_dim, int new_dim);

  protected:
    //
    // Protected member data:
    //

    //
    // If we're parsing input #4 (which is now REFRESH and was at one point REMAP)
    // and the net version is older than 3.1.0 (which is compiled in by DXVersion.h),
    // then set the defaulting status = true.  Reason:  the older ui was setting
    // the defaulting status of this unused param to false.  Now that we want to use
    // the param again, old nets believe the param is set.
    //
    virtual bool parseIOComment(bool input, const char* comment,
		const char* filename, int lineno, bool valueOnly = false);

    //
    // Make sure the number of inputs is the number expected.
    //
    bool verifyInputCount();

    //
    // Adjusts the dimensionality of all outputs for
    // this->doDimensionalityChange().
    //
    virtual bool adjustOutputDimensions(int old_dim, int new_dim);

    //
    // Global flag for all interactor instances indicating whether or not to 
    // do continuous updates to the exec.
    //
    bool	isContinuousUpdate;	


    bool cfgParseComponentComment(const char *comment,
					const char *filename, int lineno);
    bool cfgParseInstanceComment(const char *comment,
					const char *filename, int lineno);

    //
    // Print the '// interactor...' comment  to the .cfg file.
    // We override the parent's method so that we can print num_components
    // correctly.
    //
    virtual bool cfgPrintInteractorComment(FILE *f);
    //
    // Print auxiliary info for this interactor, which includes all global
    // information about each component.
    //
    virtual bool cfgPrintInteractorAuxInfo(FILE *f);
    //
    // Print auxiliary info for the interactor instance,  which includes
    // all local information about each component.
    //
    virtual bool cfgPrintInstanceAuxInfo(FILE *f, InteractorInstance *ii);

    //
    // Get a ScalarInstance instead of an InteractorInstance.
    //
    virtual InteractorInstance	*newInteractorInstance();

    //
    // Parse comments the 'local increment' comment. 
    //
    bool cfgParseLocalIncrementComment(const char *comment,
					const char *filename, int lineno);

    //
    // Parse comments the 'local increment' comment. 
    //
    bool cfgParseLocalContinuousComment(const char *comment,
					const char *filename, int lineno);

    // The messages we deal with can contain one or more of the following...
    //
    // 'min=%g' 'max=%g' 'delta=%g' 'value=%g' 'decimals=%d'
    //
    //  or one or more of the following...
    //
    // 'min=[%g %g %g]' 'max=[%g %g %g]' 'delta=[%g %g %g]' 'value=[%g %g %g]'
    // 'decimals=[%g %g %g]'
    //
    // Returns the number of attributes parsed.
    virtual int  handleInteractorMsgInfo(const char *line);
    //
    // Handles...
    // 'min=%g' 'max=%g' 'delta=%g' 'value=%g' 'decimals=%d'
    //
    int handleScalarMsgInfo(const char *line);
    //
    // Handles...
    // 'dim=%d'
    // 'min=[%g %g %g]' 'max=[%g %g %g]' 'delta=[%g %g %g]' 'value=[%g %g %g]'
    // 'decimals=[%g %g %g]'
    //
    int handleVectorMsgInfo(const char *line);

    //
    // Set the interactor's default attributes (attributes that can
    // be shared by derived classes).
    //
    virtual bool setDefaultAttributes();

    //
    // Get and set the USUALLY global component values.  In some cases
    // (i.e. ScalarListNode), the component values are saved with the 
    // InteractorInstance.  So we make these protected and only allow
    // the ScalarInstance class to access them.
    //
    bool setComponentValue(int component, double value);
    double getComponentValue(int component);
    friend class ScalarInstance;

    //
    // Do what ever is necessary when the given component of the output 
    // value is out of range as indicated by the limits.  Typically, this just 
    // means resetting the current output value that is associated with the 
    // node.  ScalarListNodes however, have the current (non-output) value 
    // associated with the interactor instance. Therefore, ScalarListNodes, 
    // re-implement this to reset the component values of all their instances.
    // If 'component' is less than 0, then min/max are ignored and all 
    // components are checked with the current min/max values.
    //
    virtual void doRangeCheckComponentValue(int component, 
				double min, double max); 

    //
    // Call doRangeCheckComponentValue() if range checking is not deferred.
    //
    void rangeCheckComponentValue(int component, double min, double max); 

    //
    // Provide methods to delay doRangeCheckComponentValue().
    //
    bool isRangeCheckingDeferred()
                        { return this->rangeCheckDeferrals != 0;}
    void deferRangeChecking()   {this->rangeCheckDeferrals++;}
    void undeferRangeChecking()
                        {  ASSERT(this->rangeCheckDeferrals > 0);
                           if ((--this->rangeCheckDeferrals == 0) &&
                               this->needsRangeCheck)
                                this->rangeCheckComponentValue(-1, 0.0, 0.0);
                        }


    //
    // Initialize the attributes with the give string values.
    //
    bool initMinimumAttribute(const char *val);
    bool setMinimumAttribute(const char *val);
    bool initMaximumAttribute(const char *val);
    bool setMaximumAttribute(const char *val);
    bool initDeltaAttribute(const char *val);
    bool setDeltaAttribute(const char *val);
    bool initDecimalsAttribute(const char *val);
    bool setDecimalsAttribute(const char *val);

    //
    // Change the dimensionality of a Vector interactor.
    //
    virtual bool doDimensionalityChange(int new_dim);


  public:
    //
    // Constructor:
    //
    ScalarNode(NodeDefinition *nd, Network *net, int instnc, 
				bool isVector = false, int dimensions = 1); 

    //
    // Destructor:
    //
    ~ScalarNode(){}

    //
    // Set the attributes for the given component of the given instance
    // of an interactor.
    //
    bool setAllComponentRanges(double *min, double *max);
    bool setComponentMinimum(int component, double min);
    bool setComponentMaximum(int component, double max);
    bool setComponentDelta(int component, double delta);
    bool setComponentDecimals(int component, int decimals); 
    void setContinuous(bool val) { isContinuousUpdate = val; }
    void setContinuous() { isContinuousUpdate = true; }
    void clrContinuous() { isContinuousUpdate = false; }

    //
    // Get the global attributes for the given component of an interactor.
    //
    double getComponentMinimum(int component);
    double getComponentMaximum(int component);
    double getComponentDelta(int component);
    int    getComponentDecimals(int component);
    bool isIntegerTypeComponent(); 
    bool isContinuous()  { return isContinuousUpdate; }

    bool isVectorType() { return this->vectorType; }

    //
    // Called once for each instance 
    //
    virtual bool initialize();

    //
    // Indicates whether this node has outputs that can be remapped by the
    // server.
    //
    virtual bool hasRemappableOutput() { return true; }

    //
    // Call the super class method, but then catch the output comment 
    // to determine the number of components.  
    // We need to do this when we have a 2d vector and no .cfg file to
    // tell us so.  We then get numComponent==3, but all the parameter
    // values are 2d, which results in an ASSERTion failure.
    //
    virtual bool     netParseComment(const char* comment,
					    const char *file, int lineno);

    //
    // Parse comments found in the .cfg that the InteractorNode knows how to
    // parse plus ones that it does not.
    //
    virtual bool cfgParseComment(const char *comment,
					const char *filename, int lineno);

    //
    // Does this node implement doDimensionalityChange();
    //
    virtual bool hasDynamicDimensionality(bool ignoreDataDriven = false);

    //
    // Determine if this node is a node of the given class
    //
    virtual bool isA(Symbol classname);

    bool isMinimumVisuallyWriteable();
    bool isMaximumVisuallyWriteable();
    bool isDecimalsVisuallyWriteable();
    bool isDeltaVisuallyWriteable();

    virtual bool printJavaValue(FILE*);
    virtual const char* getJavaNodeName() { return "ScalarNode"; }


    //
    // Returns a pointer to the class name.
    //
    const char* getClassName()
    {
	return ClassScalarNode;
    }
};


#endif // _ScalarNode_h
