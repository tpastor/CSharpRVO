/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.4
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#define SWIGCSHARP


#ifdef __cplusplus
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigMovePointer {
    T *ptr;
    SwigMovePointer(T *p) : ptr(p) { }
    ~SwigMovePointer() { delete ptr; }
    SwigMovePointer& operator=(SwigMovePointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigMovePointer tmp(new T(t)); pointer = tmp; return *this; }
  operator T&() const { return *pointer.ptr; }
  T *operator&() { return pointer.ptr; }
};

template <typename T> T SwigValueInit() {
  return T();
}
#endif

/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__)) 
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__)) 
# else
#   define SWIGUNUSED 
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif 
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED 
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif 
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif



#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* Support for throwing C# exceptions from C/C++. There are two types: 
 * Exceptions that take a message and ArgumentExceptions that take a message and a parameter name. */
typedef enum {
  SWIG_CSharpApplicationException,
  SWIG_CSharpArithmeticException,
  SWIG_CSharpDivideByZeroException,
  SWIG_CSharpIndexOutOfRangeException,
  SWIG_CSharpInvalidCastException,
  SWIG_CSharpInvalidOperationException,
  SWIG_CSharpIOException,
  SWIG_CSharpNullReferenceException,
  SWIG_CSharpOutOfMemoryException,
  SWIG_CSharpOverflowException,
  SWIG_CSharpSystemException
} SWIG_CSharpExceptionCodes;

typedef enum {
  SWIG_CSharpArgumentException,
  SWIG_CSharpArgumentNullException,
  SWIG_CSharpArgumentOutOfRangeException
} SWIG_CSharpExceptionArgumentCodes;

typedef void (SWIGSTDCALL* SWIG_CSharpExceptionCallback_t)(const char *);
typedef void (SWIGSTDCALL* SWIG_CSharpExceptionArgumentCallback_t)(const char *, const char *);

typedef struct {
  SWIG_CSharpExceptionCodes code;
  SWIG_CSharpExceptionCallback_t callback;
} SWIG_CSharpException_t;

typedef struct {
  SWIG_CSharpExceptionArgumentCodes code;
  SWIG_CSharpExceptionArgumentCallback_t callback;
} SWIG_CSharpExceptionArgument_t;

static SWIG_CSharpException_t SWIG_csharp_exceptions[] = {
  { SWIG_CSharpApplicationException, NULL },
  { SWIG_CSharpArithmeticException, NULL },
  { SWIG_CSharpDivideByZeroException, NULL },
  { SWIG_CSharpIndexOutOfRangeException, NULL },
  { SWIG_CSharpInvalidCastException, NULL },
  { SWIG_CSharpInvalidOperationException, NULL },
  { SWIG_CSharpIOException, NULL },
  { SWIG_CSharpNullReferenceException, NULL },
  { SWIG_CSharpOutOfMemoryException, NULL },
  { SWIG_CSharpOverflowException, NULL },
  { SWIG_CSharpSystemException, NULL }
};

static SWIG_CSharpExceptionArgument_t SWIG_csharp_exceptions_argument[] = {
  { SWIG_CSharpArgumentException, NULL },
  { SWIG_CSharpArgumentNullException, NULL },
  { SWIG_CSharpArgumentOutOfRangeException, NULL }
};

static void SWIGUNUSED SWIG_CSharpSetPendingException(SWIG_CSharpExceptionCodes code, const char *msg) {
  SWIG_CSharpExceptionCallback_t callback = SWIG_csharp_exceptions[SWIG_CSharpApplicationException].callback;
  if ((size_t)code < sizeof(SWIG_csharp_exceptions)/sizeof(SWIG_CSharpException_t)) {
    callback = SWIG_csharp_exceptions[code].callback;
  }
  callback(msg);
}

static void SWIGUNUSED SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpExceptionArgumentCodes code, const char *msg, const char *param_name) {
  SWIG_CSharpExceptionArgumentCallback_t callback = SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentException].callback;
  if ((size_t)code < sizeof(SWIG_csharp_exceptions_argument)/sizeof(SWIG_CSharpExceptionArgument_t)) {
    callback = SWIG_csharp_exceptions_argument[code].callback;
  }
  callback(msg, param_name);
}


#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterExceptionCallbacks_RVO3DSimulator(
                                                SWIG_CSharpExceptionCallback_t applicationCallback,
                                                SWIG_CSharpExceptionCallback_t arithmeticCallback,
                                                SWIG_CSharpExceptionCallback_t divideByZeroCallback, 
                                                SWIG_CSharpExceptionCallback_t indexOutOfRangeCallback, 
                                                SWIG_CSharpExceptionCallback_t invalidCastCallback,
                                                SWIG_CSharpExceptionCallback_t invalidOperationCallback,
                                                SWIG_CSharpExceptionCallback_t ioCallback,
                                                SWIG_CSharpExceptionCallback_t nullReferenceCallback,
                                                SWIG_CSharpExceptionCallback_t outOfMemoryCallback, 
                                                SWIG_CSharpExceptionCallback_t overflowCallback, 
                                                SWIG_CSharpExceptionCallback_t systemCallback) {
  SWIG_csharp_exceptions[SWIG_CSharpApplicationException].callback = applicationCallback;
  SWIG_csharp_exceptions[SWIG_CSharpArithmeticException].callback = arithmeticCallback;
  SWIG_csharp_exceptions[SWIG_CSharpDivideByZeroException].callback = divideByZeroCallback;
  SWIG_csharp_exceptions[SWIG_CSharpIndexOutOfRangeException].callback = indexOutOfRangeCallback;
  SWIG_csharp_exceptions[SWIG_CSharpInvalidCastException].callback = invalidCastCallback;
  SWIG_csharp_exceptions[SWIG_CSharpInvalidOperationException].callback = invalidOperationCallback;
  SWIG_csharp_exceptions[SWIG_CSharpIOException].callback = ioCallback;
  SWIG_csharp_exceptions[SWIG_CSharpNullReferenceException].callback = nullReferenceCallback;
  SWIG_csharp_exceptions[SWIG_CSharpOutOfMemoryException].callback = outOfMemoryCallback;
  SWIG_csharp_exceptions[SWIG_CSharpOverflowException].callback = overflowCallback;
  SWIG_csharp_exceptions[SWIG_CSharpSystemException].callback = systemCallback;
}

#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterExceptionArgumentCallbacks_RVO3DSimulator(
                                                SWIG_CSharpExceptionArgumentCallback_t argumentCallback,
                                                SWIG_CSharpExceptionArgumentCallback_t argumentNullCallback,
                                                SWIG_CSharpExceptionArgumentCallback_t argumentOutOfRangeCallback) {
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentException].callback = argumentCallback;
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentNullException].callback = argumentNullCallback;
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentOutOfRangeException].callback = argumentOutOfRangeCallback;
}


/* Callback for returning strings to C# without leaking memory */
typedef char * (SWIGSTDCALL* SWIG_CSharpStringHelperCallback)(const char *);
static SWIG_CSharpStringHelperCallback SWIG_csharp_string_callback = NULL;


#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterStringCallback_RVO3DSimulator(SWIG_CSharpStringHelperCallback callback) {
  SWIG_csharp_string_callback = callback;
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentOutOfRangeException, msg, ""); return nullreturn; } else


#include "RVOSimulator.h"


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVO_ERROR_get() {
  unsigned long jresult ;
  size_t result;
  
  result = (size_t)RVO::RVO_ERROR;
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_Plane_point_set(void * jarg1, void * jarg2) {
  RVO::Plane *arg1 = (RVO::Plane *) 0 ;
  RVO::Vector3 arg2 ;
  RVO::Vector3 *argp2 ;
  
  arg1 = (RVO::Plane *)jarg1; 
  argp2 = (RVO::Vector3 *)jarg2; 
  if (!argp2) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "Attempt to dereference null RVO::Vector3", 0);
    return ;
  }
  arg2 = *argp2; 
  if (arg1) (arg1)->point = arg2;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_Plane_point_get(void * jarg1) {
  void * jresult ;
  RVO::Plane *arg1 = (RVO::Plane *) 0 ;
  RVO::Vector3 result;
  
  arg1 = (RVO::Plane *)jarg1; 
  result =  ((arg1)->point);
  jresult = new RVO::Vector3((const RVO::Vector3 &)result); 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_Plane_normal_set(void * jarg1, void * jarg2) {
  RVO::Plane *arg1 = (RVO::Plane *) 0 ;
  RVO::Vector3 arg2 ;
  RVO::Vector3 *argp2 ;
  
  arg1 = (RVO::Plane *)jarg1; 
  argp2 = (RVO::Vector3 *)jarg2; 
  if (!argp2) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "Attempt to dereference null RVO::Vector3", 0);
    return ;
  }
  arg2 = *argp2; 
  if (arg1) (arg1)->normal = arg2;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_Plane_normal_get(void * jarg1) {
  void * jresult ;
  RVO::Plane *arg1 = (RVO::Plane *) 0 ;
  RVO::Vector3 result;
  
  arg1 = (RVO::Plane *)jarg1; 
  result =  ((arg1)->normal);
  jresult = new RVO::Vector3((const RVO::Vector3 &)result); 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_new_Plane() {
  void * jresult ;
  RVO::Plane *result = 0 ;
  
  result = (RVO::Plane *)new RVO::Plane();
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_delete_Plane(void * jarg1) {
  RVO::Plane *arg1 = (RVO::Plane *) 0 ;
  
  arg1 = (RVO::Plane *)jarg1; 
  delete arg1;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_new_RVOSimulator__SWIG_0() {
  void * jresult ;
  RVO::RVOSimulator *result = 0 ;
  
  result = (RVO::RVOSimulator *)new RVO::RVOSimulator();
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_new_RVOSimulator__SWIG_1(float jarg1, float jarg2, unsigned long jarg3, float jarg4, float jarg5, float jarg6, void * jarg7) {
  void * jresult ;
  float arg1 ;
  float arg2 ;
  size_t arg3 ;
  float arg4 ;
  float arg5 ;
  float arg6 ;
  RVO::Vector3 *arg7 = 0 ;
  RVO::RVOSimulator *result = 0 ;
  
  arg1 = (float)jarg1; 
  arg2 = (float)jarg2; 
  arg3 = (size_t)jarg3; 
  arg4 = (float)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  arg7 = (RVO::Vector3 *)jarg7;
  if (!arg7) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return 0;
  } 
  result = (RVO::RVOSimulator *)new RVO::RVOSimulator(arg1,arg2,arg3,arg4,arg5,arg6,(RVO::Vector3 const &)*arg7);
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_new_RVOSimulator__SWIG_2(float jarg1, float jarg2, unsigned long jarg3, float jarg4, float jarg5, float jarg6) {
  void * jresult ;
  float arg1 ;
  float arg2 ;
  size_t arg3 ;
  float arg4 ;
  float arg5 ;
  float arg6 ;
  RVO::RVOSimulator *result = 0 ;
  
  arg1 = (float)jarg1; 
  arg2 = (float)jarg2; 
  arg3 = (size_t)jarg3; 
  arg4 = (float)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  result = (RVO::RVOSimulator *)new RVO::RVOSimulator(arg1,arg2,arg3,arg4,arg5,arg6);
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_delete_RVOSimulator(void * jarg1) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  delete arg1;
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_addAgent__SWIG_0(void * jarg1, void * jarg2) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  RVO::Vector3 *arg2 = 0 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (RVO::Vector3 *)jarg2;
  if (!arg2) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return 0;
  } 
  result = (arg1)->addAgent((RVO::Vector3 const &)*arg2);
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_addAgent__SWIG_1(void * jarg1, void * jarg2, float jarg3, unsigned long jarg4, float jarg5, float jarg6, float jarg7, void * jarg8) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  RVO::Vector3 *arg2 = 0 ;
  float arg3 ;
  size_t arg4 ;
  float arg5 ;
  float arg6 ;
  float arg7 ;
  RVO::Vector3 *arg8 = 0 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (RVO::Vector3 *)jarg2;
  if (!arg2) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return 0;
  } 
  arg3 = (float)jarg3; 
  arg4 = (size_t)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  arg7 = (float)jarg7; 
  arg8 = (RVO::Vector3 *)jarg8;
  if (!arg8) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return 0;
  } 
  result = (arg1)->addAgent((RVO::Vector3 const &)*arg2,arg3,arg4,arg5,arg6,arg7,(RVO::Vector3 const &)*arg8);
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_addAgent__SWIG_2(void * jarg1, void * jarg2, float jarg3, unsigned long jarg4, float jarg5, float jarg6, float jarg7) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  RVO::Vector3 *arg2 = 0 ;
  float arg3 ;
  size_t arg4 ;
  float arg5 ;
  float arg6 ;
  float arg7 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (RVO::Vector3 *)jarg2;
  if (!arg2) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return 0;
  } 
  arg3 = (float)jarg3; 
  arg4 = (size_t)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  arg7 = (float)jarg7; 
  result = (arg1)->addAgent((RVO::Vector3 const &)*arg2,arg3,arg4,arg5,arg6,arg7);
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_doStep(void * jarg1) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  (arg1)->doStep();
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_getAgentAgentNeighbor(void * jarg1, unsigned long jarg2, unsigned long jarg3) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  size_t arg3 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (size_t)jarg3; 
  result = ((RVO::RVOSimulator const *)arg1)->getAgentAgentNeighbor(arg2,arg3);
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_getAgentMaxNeighbors(void * jarg1, unsigned long jarg2) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = ((RVO::RVOSimulator const *)arg1)->getAgentMaxNeighbors(arg2);
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT float SWIGSTDCALL CSharp_RVOSimulator_getAgentMaxSpeed(void * jarg1, unsigned long jarg2) {
  float jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = (float)((RVO::RVOSimulator const *)arg1)->getAgentMaxSpeed(arg2);
  jresult = result; 
  return jresult;
}


SWIGEXPORT float SWIGSTDCALL CSharp_RVOSimulator_getAgentNeighborDist(void * jarg1, unsigned long jarg2) {
  float jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = (float)((RVO::RVOSimulator const *)arg1)->getAgentNeighborDist(arg2);
  jresult = result; 
  return jresult;
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_getAgentNumAgentNeighbors(void * jarg1, unsigned long jarg2) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = ((RVO::RVOSimulator const *)arg1)->getAgentNumAgentNeighbors(arg2);
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_getAgentNumORCAPlanes(void * jarg1, unsigned long jarg2) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = ((RVO::RVOSimulator const *)arg1)->getAgentNumORCAPlanes(arg2);
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_RVOSimulator_getAgentORCAPlane(void * jarg1, unsigned long jarg2, unsigned long jarg3) {
  void * jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  size_t arg3 ;
  RVO::Plane *result = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (size_t)jarg3; 
  result = (RVO::Plane *) &((RVO::RVOSimulator const *)arg1)->getAgentORCAPlane(arg2,arg3);
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_RVOSimulator_getAgentPosition(void * jarg1, unsigned long jarg2) {
  void * jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  RVO::Vector3 *result = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = (RVO::Vector3 *) &((RVO::RVOSimulator const *)arg1)->getAgentPosition(arg2);
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_RVOSimulator_getAgentPrefVelocity(void * jarg1, unsigned long jarg2) {
  void * jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  RVO::Vector3 *result = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = (RVO::Vector3 *) &((RVO::RVOSimulator const *)arg1)->getAgentPrefVelocity(arg2);
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT float SWIGSTDCALL CSharp_RVOSimulator_getAgentRadius(void * jarg1, unsigned long jarg2) {
  float jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = (float)((RVO::RVOSimulator const *)arg1)->getAgentRadius(arg2);
  jresult = result; 
  return jresult;
}


SWIGEXPORT float SWIGSTDCALL CSharp_RVOSimulator_getAgentTimeHorizon(void * jarg1, unsigned long jarg2) {
  float jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = (float)((RVO::RVOSimulator const *)arg1)->getAgentTimeHorizon(arg2);
  jresult = result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_RVOSimulator_getAgentVelocity(void * jarg1, unsigned long jarg2) {
  void * jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  RVO::Vector3 *result = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  result = (RVO::Vector3 *) &((RVO::RVOSimulator const *)arg1)->getAgentVelocity(arg2);
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT float SWIGSTDCALL CSharp_RVOSimulator_getGlobalTime(void * jarg1) {
  float jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  float result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  result = (float)((RVO::RVOSimulator const *)arg1)->getGlobalTime();
  jresult = result; 
  return jresult;
}


SWIGEXPORT unsigned long SWIGSTDCALL CSharp_RVOSimulator_getNumAgents(void * jarg1) {
  unsigned long jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  result = ((RVO::RVOSimulator const *)arg1)->getNumAgents();
  jresult = (unsigned long)result; 
  return jresult;
}


SWIGEXPORT float SWIGSTDCALL CSharp_RVOSimulator_getTimeStep(void * jarg1) {
  float jresult ;
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  float result;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  result = (float)((RVO::RVOSimulator const *)arg1)->getTimeStep();
  jresult = result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_removeAgent(void * jarg1, unsigned long jarg2) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  (arg1)->removeAgent(arg2);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentDefaults__SWIG_0(void * jarg1, float jarg2, unsigned long jarg3, float jarg4, float jarg5, float jarg6, void * jarg7) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  float arg2 ;
  size_t arg3 ;
  float arg4 ;
  float arg5 ;
  float arg6 ;
  RVO::Vector3 *arg7 = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (float)jarg2; 
  arg3 = (size_t)jarg3; 
  arg4 = (float)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  arg7 = (RVO::Vector3 *)jarg7;
  if (!arg7) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return ;
  } 
  (arg1)->setAgentDefaults(arg2,arg3,arg4,arg5,arg6,(RVO::Vector3 const &)*arg7);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentDefaults__SWIG_1(void * jarg1, float jarg2, unsigned long jarg3, float jarg4, float jarg5, float jarg6) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  float arg2 ;
  size_t arg3 ;
  float arg4 ;
  float arg5 ;
  float arg6 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (float)jarg2; 
  arg3 = (size_t)jarg3; 
  arg4 = (float)jarg4; 
  arg5 = (float)jarg5; 
  arg6 = (float)jarg6; 
  (arg1)->setAgentDefaults(arg2,arg3,arg4,arg5,arg6);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentMaxNeighbors(void * jarg1, unsigned long jarg2, unsigned long jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  size_t arg3 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (size_t)jarg3; 
  (arg1)->setAgentMaxNeighbors(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentMaxSpeed(void * jarg1, unsigned long jarg2, float jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float arg3 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->setAgentMaxSpeed(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentNeighborDist(void * jarg1, unsigned long jarg2, float jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float arg3 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->setAgentNeighborDist(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentPosition(void * jarg1, unsigned long jarg2, void * jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  RVO::Vector3 *arg3 = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (RVO::Vector3 *)jarg3;
  if (!arg3) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return ;
  } 
  (arg1)->setAgentPosition(arg2,(RVO::Vector3 const &)*arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentPrefVelocity(void * jarg1, unsigned long jarg2, void * jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  RVO::Vector3 *arg3 = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (RVO::Vector3 *)jarg3;
  if (!arg3) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return ;
  } 
  (arg1)->setAgentPrefVelocity(arg2,(RVO::Vector3 const &)*arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentRadius(void * jarg1, unsigned long jarg2, float jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float arg3 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->setAgentRadius(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentTimeHorizon(void * jarg1, unsigned long jarg2, float jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  float arg3 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (float)jarg3; 
  (arg1)->setAgentTimeHorizon(arg2,arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setAgentVelocity(void * jarg1, unsigned long jarg2, void * jarg3) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  size_t arg2 ;
  RVO::Vector3 *arg3 = 0 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (size_t)jarg2; 
  arg3 = (RVO::Vector3 *)jarg3;
  if (!arg3) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "RVO::Vector3 const & type is null", 0);
    return ;
  } 
  (arg1)->setAgentVelocity(arg2,(RVO::Vector3 const &)*arg3);
}


SWIGEXPORT void SWIGSTDCALL CSharp_RVOSimulator_setTimeStep(void * jarg1, float jarg2) {
  RVO::RVOSimulator *arg1 = (RVO::RVOSimulator *) 0 ;
  float arg2 ;
  
  arg1 = (RVO::RVOSimulator *)jarg1; 
  arg2 = (float)jarg2; 
  (arg1)->setTimeStep(arg2);
}


#ifdef __cplusplus
}
#endif

