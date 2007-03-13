// @(#) $Id$

#ifndef ALIHLTLOGGING_H
#define ALIHLTLOGGING_H
/* Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/** @file   AliHLTLogging.h
    @author Matthias Richter, Timm Steinbeck
    @date   
    @brief  HLT module logging primitives.
*/

#include "AliHLTDataTypes.h"
#include "AliHLTStdIncludes.h"
#include "TObject.h"

//#define LOG_PREFIX ""       // logging prefix, for later extensions


/* the logging macros can be used inside methods of classes which inherit from 
 * AliHLTLogging
 */
// HLTMessage is not filtered
#define HLTMessage( ... )   LoggingVarargs(kHLTLogNone,      NULL , NULL , __FILE__ , __LINE__ , __VA_ARGS__ )

// function name
#if defined(__GNUC__) || defined(__ICC) || defined(__ECC) || defined(__APPLE__)
#define FUNCTIONNAME() __FUNCTION__
#else
#define FUNCTIONNAME() "???"
#endif

// the following macros are filtered by the Global and Local Log Filter
#define HLTBenchmark( ... ) LoggingVarargs(kHLTLogBenchmark, Class_Name() , FUNCTIONNAME() , __FILE__ , __LINE__ , __VA_ARGS__ )
#define HLTDebug( ... )     LoggingVarargs(kHLTLogDebug,     Class_Name() , FUNCTIONNAME() , __FILE__ , __LINE__ , __VA_ARGS__ )
#define HLTInfo( ... )      LoggingVarargs(kHLTLogInfo,      Class_Name() , FUNCTIONNAME() , __FILE__ , __LINE__ , __VA_ARGS__ )
#define HLTWarning( ... )   LoggingVarargs(kHLTLogWarning,   Class_Name() , FUNCTIONNAME() , __FILE__ , __LINE__ , __VA_ARGS__ )
#define HLTError( ... )     LoggingVarargs(kHLTLogError,     Class_Name() , FUNCTIONNAME() , __FILE__ , __LINE__ , __VA_ARGS__ )
#define HLTFatal( ... )     LoggingVarargs(kHLTLogFatal,     Class_Name() , FUNCTIONNAME() , __FILE__ , __LINE__ , __VA_ARGS__ )

// helper macro to set the keyword
#define HLTLogKeyword(a)    AliHLTKeyword hltlogTmpkey__LINE__(this, a)

#define HLT_DEFAULT_LOG_KEYWORD "no key"

class AliHLTLogging {
public:
  AliHLTLogging();
  AliHLTLogging(const AliHLTLogging&);
  AliHLTLogging& operator=(const AliHLTLogging&);
  virtual ~AliHLTLogging();

  // logging filter for all objects
  //
  static AliHLTComponentLogSeverity SetGlobalLogLevel(AliHLTComponentLogSeverity iLogFilter) {fGlobalLogFilter=iLogFilter; return fGlobalLogFilter;}

  // logging filter for individual object
  //
  AliHLTComponentLogSeverity SetLocalLogLevel(AliHLTComponentLogSeverity iLogFilter) {fLocalLogFilter=iLogFilter; return fLocalLogFilter;}

  // set the default key word
  // the keyword is intended to simplify the use of logging macros
  // 
  void SetDefaultKeyword(const char* keyword) { fpDefaultKeyword=keyword; }

  // set a temporary keyword
  // returns the old key value
  const char* SetKeyword(const char* keyword) 
    { 
      const char* currentKeyword=fpCurrentKeyword;
      fpCurrentKeyword=keyword;
      return currentKeyword; 
    }

  // get the current keyword
  //
  const char* GetKeyword() const
    {
      if (fpCurrentKeyword) return fpCurrentKeyword;
      else if (fpDefaultKeyword) return fpDefaultKeyword;
      return HLT_DEFAULT_LOG_KEYWORD;
    }
  
  static int Init(AliHLTfctLogging pFun);

  // genaral logging function
  //
  int Logging( AliHLTComponentLogSeverity severity, const char* origin, const char* keyword, const char* message, ... );

  // logging function with two origin parameters, used by the log macros
  //
  int LoggingVarargs(AliHLTComponentLogSeverity severity, 
		     const char* origin_class, const char* origin_func,
		     const char* file, int line, ... ) const;

  // apply filter, return 1 if message should pass
  //
  int CheckFilter(AliHLTComponentLogSeverity severity) const;

  // set global logging level
  //
  static void SetGlobalLoggingLevel(AliHLTComponentLogSeverity level);

  // set local logging level
  //
  void SetLocalLoggingLevel(AliHLTComponentLogSeverity level);

  /**
   * Print message to stdout
   */
  static int Message(void * param, AliHLTComponentLogSeverity severity, const char* origin, const char* keyword, const char* message);

#ifndef NOALIROOT_LOGGING
  /**
   * Print message through AliRoot log channels.
   */
  static int AliMessage(AliHLTComponentLogSeverity severity,
			const char* origin_class, const char* origin_func,
			const char* file, int line, const char* message);
#endif

  /**
   * Build the log string from format specifier and variadac arguments
   * @param format     format string of printf style
   * @param ap         opened and initialized argument list
   * @return const char string with the formatted message 
   */
  static const char* BuildLogString(const char *format, va_list ap);

  virtual void* GetParameter() {return NULL;}

  /**
   * Switch logging through AliLog on or off
   * @param sw          1 = logging through AliLog
   */
  void SwitchAliLog(int sw) {fgUseAliLog=(sw!=0);}

protected:

private:
  /** the global logging filter */
  static  AliHLTComponentLogSeverity fGlobalLogFilter;             // see above
  /** the local logging filter for one class */
  AliHLTComponentLogSeverity fLocalLogFilter;                      // see above
  /** logging callback from the framework */
  static AliHLTfctLogging fLoggingFunc;                            // see above
  /** default keyword */
  const char* fpDefaultKeyword;                                    //! transient
  /** current keyword */
  const char* fpCurrentKeyword;                                    //! transient
  /** switch for logging through AliLog, default on */
  static int fgUseAliLog;                                          // see above

  ClassDef(AliHLTLogging, 1)
};

/* the class AliHLTKeyword is a simple helper class used by the HLTLogKeyword macro
 * HLTLogKeyword("a keyword") creates an object of AliHLTKeyword which sets the keyword for the logging class
 * the object is destroyed automatically when the current scope is left and so the keyword is set
 * to the original value
 */
class AliHLTKeyword {
 public:
  AliHLTKeyword()
    :
    fpParent(NULL),
    fpOriginal(NULL)
    {
    }

  AliHLTKeyword(AliHLTLogging* parent, const char* keyword)
    :
    fpParent(parent),
    fpOriginal(NULL)
    {
      if (parent) {
	fpOriginal=fpParent->SetKeyword(keyword);
      }
    }

  AliHLTKeyword(const AliHLTKeyword& kw)
    :
    fpParent(kw.fpParent),
    fpOriginal(kw.fpOriginal)
    {
    }

  AliHLTKeyword& operator=(const AliHLTKeyword& kw)
    { 
      fpParent=kw.fpParent;
      fpOriginal=kw.fpOriginal;
      return *this;
    }

  ~AliHLTKeyword()
    {
      if (fpParent) {
	fpParent->SetKeyword(fpOriginal);
      }
    }

 private:
  AliHLTLogging* fpParent;
  const char* fpOriginal;
};
#endif

