/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef TRACEFILES_TRACETYPES_HPP
#define TRACEFILES_TRACETYPES_HPP

#include "oops/symbol.hpp"
#include "trace/traceDataTypes.hpp"
#include "utilities/globalDefinitions.hpp"
#include "utilities/ticks.hpp"

enum JVMContentType {
  _not_a_content_type = (JVM_CONTENT_TYPES_START - 1),
  
  CONTENT_TYPE_THREADGROUP,
  CONTENT_TYPE_CLASSLOADER,
  CONTENT_TYPE_METHOD,
  CONTENT_TYPE_SYMBOL,
  CONTENT_TYPE_THREADSTATE,
  CONTENT_TYPE_GCNAME,
  CONTENT_TYPE_GCCAUSE,
  CONTENT_TYPE_GCWHEN,
  CONTENT_TYPE_G1HEAPREGIONTYPE,
  CONTENT_TYPE_G1YCTYPE,
  CONTENT_TYPE_GCTHRESHOLDUPDATER,
  CONTENT_TYPE_REFERENCETYPE,
  CONTENT_TYPE_METADATATYPE,
  CONTENT_TYPE_METASPACEOBJTYPE,
  CONTENT_TYPE_NARROWOOPMODE,
  CONTENT_TYPE_VMOPERATIONTYPE,
  CONTENT_TYPE_COMPILERPHASETYPE,
  CONTENT_TYPE_FLAGVALUEORIGIN,
  CONTENT_TYPE_CODEBLOBTYPE,
  CONTENT_TYPE_INFLATECAUSE,
  CONTENT_TYPE_MODULE,
  CONTENT_TYPE_PACKAGE,

  NUM_JVM_CONTENT_TYPES
};


enum JVMEventRelations {
  JVM_REL_NOT_AVAILABLE = 0,
  
  JVM_REL_GcId,
  JVM_REL_CompileId,
  JVM_REL_SweepId,
  JVM_REL_JavaMonitorAddress,
  JVM_REL_SafepointId,

  NUM_EVENT_RELATIONS
};

/**
 * Create typedefs for the TRACE types:
 *   typedef s8 TYPE_LONG;
 *   typedef s4 TYPE_INTEGER;
 *   typedef const char * TYPE_STRING;
 *   ...
 */

typedef s8  TYPE_LONG;

typedef u8  TYPE_ULONG;

typedef s4  TYPE_INTEGER;

typedef unsigned  TYPE_UINT;

typedef u2  TYPE_USHORT;

typedef s2  TYPE_SHORT;

typedef s1  TYPE_BYTE;

typedef u1  TYPE_UBYTE;

typedef float  TYPE_FLOAT;

typedef double  TYPE_DOUBLE;

typedef bool  TYPE_BOOLEAN;

typedef u8  TYPE_BYTES;

typedef u8  TYPE_IOBYTES;

typedef u8  TYPE_BYTES64;

typedef s8  TYPE_EPOCHMILLIS;

typedef s8  TYPE_MILLIS;

typedef s8  TYPE_NANOS;

typedef Ticks  TYPE_TICKS;

typedef Tickspan  TYPE_TICKSPAN;

typedef u8  TYPE_ADDRESS;

typedef float  TYPE_PERCENTAGE;

typedef const char*  TYPE_STRING;

typedef const Symbol*  TYPE_SYMBOL;

typedef const Klass*  TYPE_CLASS;

typedef const ClassLoaderData*  TYPE_CLASSLOADER;

typedef const ModuleEntry*  TYPE_MODULE;

typedef const PackageEntry*  TYPE_PACKAGE;

typedef const Method*  TYPE_METHOD;

typedef u8  TYPE_STACKTRACE;

typedef u8  TYPE_THREAD;

typedef u8  TYPE_THREADGROUP;

typedef u8  TYPE_FRAMETYPE;

typedef u8  TYPE_THREADSTATE;

typedef u8  TYPE_GCNAME;

typedef u8  TYPE_GCCAUSE;

typedef u8  TYPE_GCWHEN;

typedef u8  TYPE_G1HEAPREGIONTYPE;

typedef u8  TYPE_G1YCTYPE;

typedef u8  TYPE_GCTHRESHOLDUPDATER;

typedef u8  TYPE_REFERENCETYPE;

typedef u8  TYPE_METADATATYPE;

typedef u8  TYPE_METASPACEOBJTYPE;

typedef u8  TYPE_NARROWOOPMODE;

typedef u8  TYPE_COMPILERPHASETYPE;

typedef u8  TYPE_VMOPERATIONTYPE;

typedef u8  TYPE_FLAGVALUEORIGIN;

typedef u8  TYPE_CODEBLOBTYPE;

typedef u8  TYPE_INFLATECAUSE;


#endif // TRACEFILES_TRACETYPES_HPP
