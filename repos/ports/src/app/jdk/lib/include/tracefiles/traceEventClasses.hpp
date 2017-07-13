/* AUTOMATICALLY GENERATED FILE - DO NOT EDIT */

#ifndef TRACEFILES_TRACEEVENTCLASSES_HPP
#define TRACEFILES_TRACEEVENTCLASSES_HPP

// On purpose outside the INCLUDE_TRACE
// Some parts of traceEvent.hpp are used outside of
// INCLUDE_TRACE

#include "tracefiles/traceTypes.hpp"
#include "trace/traceEvent.hpp"
#include "utilities/macros.hpp"
#include "utilities/ticks.hpp"
#if INCLUDE_TRACE
#include "trace/traceStream.hpp"
#include "utilities/ostream.hpp"

  
struct TraceStructVirtualSpace
{
private:
  u8 _start; 
  u8 _committedEnd; 
  u8 _committedSize; 
  u8 _reservedEnd; 
  u8 _reservedSize;
public:
  void set_start(u8 value) { this->_start = value; }
  void set_committedEnd(u8 value) { this->_committedEnd = value; }
  void set_committedSize(u8 value) { this->_committedSize = value; }
  void set_reservedEnd(u8 value) { this->_reservedEnd = value; }
  void set_reservedSize(u8 value) { this->_reservedSize = value; }

  void writeStruct(TraceStream& ts) {
    ts.print_val("Start Address", _start);
    ts.print(", ");
    ts.print_val("Committed End Address", _committedEnd);
    ts.print(", ");
    ts.print_val("Committed Size", _committedSize);
    ts.print(", ");
    ts.print_val("Reserved End Address", _reservedEnd);
    ts.print(", ");
    ts.print_val("Reserved Size", _reservedSize);
  }
};


struct TraceStructObjectSpace
{
private:
  u8 _start; 
  u8 _end; 
  u8 _used; 
  u8 _size;
public:
  void set_start(u8 value) { this->_start = value; }
  void set_end(u8 value) { this->_end = value; }
  void set_used(u8 value) { this->_used = value; }
  void set_size(u8 value) { this->_size = value; }

  void writeStruct(TraceStream& ts) {
    ts.print_val("Start Address", _start);
    ts.print(", ");
    ts.print_val("End Address", _end);
    ts.print(", ");
    ts.print_val("Used", _used);
    ts.print(", ");
    ts.print_val("Size", _size);
  }
};


struct TraceStructMetaspaceSizes
{
private:
  u8 _committed; 
  u8 _used; 
  u8 _reserved;
public:
  void set_committed(u8 value) { this->_committed = value; }
  void set_used(u8 value) { this->_used = value; }
  void set_reserved(u8 value) { this->_reserved = value; }

  void writeStruct(TraceStream& ts) {
    ts.print_val("Committed", _committed);
    ts.print(", ");
    ts.print_val("Used", _used);
    ts.print(", ");
    ts.print_val("Reserved", _reserved);
  }
};


struct TraceStructCopyFailed
{
private:
  u8 _objectCount; 
  u8 _firstSize; 
  u8 _smallestSize; 
  u8 _totalSize;
public:
  void set_objectCount(u8 value) { this->_objectCount = value; }
  void set_firstSize(u8 value) { this->_firstSize = value; }
  void set_smallestSize(u8 value) { this->_smallestSize = value; }
  void set_totalSize(u8 value) { this->_totalSize = value; }

  void writeStruct(TraceStream& ts) {
    ts.print_val("Object Count", _objectCount);
    ts.print(", ");
    ts.print_val("First Failed Object Size", _firstSize);
    ts.print(", ");
    ts.print_val("Smallest Failed Object Size", _smallestSize);
    ts.print(", ");
    ts.print_val("Total Object Size", _totalSize);
  }
};


struct TraceStructG1EvacuationStatistics
{
private:
  unsigned _gcId; 
  u8 _allocated; 
  u8 _wasted; 
  u8 _used; 
  u8 _undoWaste; 
  u8 _regionEndWaste; 
  unsigned _regionsRefilled; 
  u8 _directAllocated; 
  u8 _failureUsed; 
  u8 _failureWaste;
public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_allocated(u8 value) { this->_allocated = value; }
  void set_wasted(u8 value) { this->_wasted = value; }
  void set_used(u8 value) { this->_used = value; }
  void set_undoWaste(u8 value) { this->_undoWaste = value; }
  void set_regionEndWaste(u8 value) { this->_regionEndWaste = value; }
  void set_regionsRefilled(unsigned value) { this->_regionsRefilled = value; }
  void set_directAllocated(u8 value) { this->_directAllocated = value; }
  void set_failureUsed(u8 value) { this->_failureUsed = value; }
  void set_failureWaste(u8 value) { this->_failureWaste = value; }

  void writeStruct(TraceStream& ts) {
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Allocated", _allocated);
    ts.print(", ");
    ts.print_val("Wasted", _wasted);
    ts.print(", ");
    ts.print_val("Used", _used);
    ts.print(", ");
    ts.print_val("Undo Wasted", _undoWaste);
    ts.print(", ");
    ts.print_val("Region End Wasted", _regionEndWaste);
    ts.print(", ");
    ts.print_val("Region Refills", _regionsRefilled);
    ts.print(", ");
    ts.print_val("Allocated (direct)", _directAllocated);
    ts.print(", ");
    ts.print_val("Used (failure)", _failureUsed);
    ts.print(", ");
    ts.print_val("Wasted (failure)", _failureWaste);
  }
};


struct TraceStructCalleeMethod
{
private:
  const char* _type; 
  const char* _name; 
  const char* _descriptor;
public:
  void set_type(const char* value) { this->_type = value; }
  void set_name(const char* value) { this->_name = value; }
  void set_descriptor(const char* value) { this->_descriptor = value; }

  void writeStruct(TraceStream& ts) {
    ts.print_val("Class", _type);
    ts.print(", ");
    ts.print_val("Method Name", _name);
    ts.print(", ");
    ts.print_val("Method Descriptor", _descriptor);
  }
};

class EventThreadStart : public TraceEvent<EventThreadStart>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceThreadStartEvent;

 private:
  u8 _thread;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Java Thread Start: [");
    ts.print_val("Java Thread", _thread);
    ts.print("]\n");
  }

 public:
  void set_thread(u8 value) { this->_thread = value; }

  bool should_write(void) {
    return true;
  }


  EventThreadStart(EventStartTime timing=TIMED) : TraceEvent<EventThreadStart>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventThreadEnd : public TraceEvent<EventThreadEnd>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceThreadEndEvent;

 private:
  u8 _thread;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Java Thread End: [");
    ts.print_val("Java Thread", _thread);
    ts.print("]\n");
  }

 public:
  void set_thread(u8 value) { this->_thread = value; }

  bool should_write(void) {
    return true;
  }


  EventThreadEnd(EventStartTime timing=TIMED) : TraceEvent<EventThreadEnd>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventThreadSleep : public TraceEvent<EventThreadSleep>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceThreadSleepEvent;

 private:
  s8 _time;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Java Thread Sleep: [");
    ts.print_val("Sleep Time", _time);
    ts.print("]\n");
  }

 public:
  void set_time(s8 value) { this->_time = value; }

  bool should_write(void) {
    return true;
  }


  EventThreadSleep(EventStartTime timing=TIMED) : TraceEvent<EventThreadSleep>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventThreadPark : public TraceEvent<EventThreadPark>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceThreadParkEvent;

 private:
  const Klass* _parkedClass; 
  s8 _timeout; 
  u8 _address;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Java Thread Park: [");
    ts.print_val("Class Parked On", _parkedClass);
    ts.print(", ");
    ts.print_val("Park Timeout", _timeout);
    ts.print(", ");
    ts.print_val("Address of Object Parked", _address);
    ts.print("]\n");
  }

 public:
  void set_parkedClass(const Klass* value) { this->_parkedClass = value; }
  void set_timeout(s8 value) { this->_timeout = value; }
  void set_address(u8 value) { this->_address = value; }

  bool should_write(void) {
    return true;
  }


  EventThreadPark(EventStartTime timing=TIMED) : TraceEvent<EventThreadPark>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventJavaMonitorEnter : public TraceEvent<EventJavaMonitorEnter>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceJavaMonitorEnterEvent;

 private:
  const Klass* _monitorClass; 
  u8 _previousOwner; 
  u8 _address;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Java Monitor Blocked: [");
    ts.print_val("Monitor Class", _monitorClass);
    ts.print(", ");
    ts.print_val("Previous Monitor Owner", _previousOwner);
    ts.print(", ");
    ts.print_val("Monitor Address", _address);
    ts.print("]\n");
  }

 public:
  void set_monitorClass(const Klass* value) { this->_monitorClass = value; }
  void set_previousOwner(u8 value) { this->_previousOwner = value; }
  void set_address(u8 value) { this->_address = value; }

  bool should_write(void) {
    return true;
  }


  EventJavaMonitorEnter(EventStartTime timing=TIMED) : TraceEvent<EventJavaMonitorEnter>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventJavaMonitorWait : public TraceEvent<EventJavaMonitorWait>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceJavaMonitorWaitEvent;

 private:
  const Klass* _monitorClass; 
  u8 _notifier; 
  s8 _timeout; 
  bool _timedOut; 
  u8 _address;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Java Monitor Wait: [");
    ts.print_val("Monitor Class", _monitorClass);
    ts.print(", ");
    ts.print_val("Notifier Thread", _notifier);
    ts.print(", ");
    ts.print_val("Timeout", _timeout);
    ts.print(", ");
    ts.print_val("Timed Out", _timedOut);
    ts.print(", ");
    ts.print_val("Monitor Address", _address);
    ts.print("]\n");
  }

 public:
  void set_monitorClass(const Klass* value) { this->_monitorClass = value; }
  void set_notifier(u8 value) { this->_notifier = value; }
  void set_timeout(s8 value) { this->_timeout = value; }
  void set_timedOut(bool value) { this->_timedOut = value; }
  void set_address(u8 value) { this->_address = value; }

  bool should_write(void) {
    return true;
  }


  EventJavaMonitorWait(EventStartTime timing=TIMED) : TraceEvent<EventJavaMonitorWait>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventJavaMonitorInflate : public TraceEvent<EventJavaMonitorInflate>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceJavaMonitorInflateEvent;

 private:
  const Klass* _monitorClass; 
  u8 _address; 
  u8 _cause;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Java Monitor Inflated: [");
    ts.print_val("Monitor Class", _monitorClass);
    ts.print(", ");
    ts.print_val("Monitor Address", _address);
    ts.print(", ");
    ts.print_val("Monitor Inflation Cause", _cause);
    ts.print("]\n");
  }

 public:
  void set_monitorClass(const Klass* value) { this->_monitorClass = value; }
  void set_address(u8 value) { this->_address = value; }
  void set_cause(u8 value) { this->_cause = value; }

  bool should_write(void) {
    return true;
  }


  EventJavaMonitorInflate(EventStartTime timing=TIMED) : TraceEvent<EventJavaMonitorInflate>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventReservedStackActivation : public TraceEvent<EventReservedStackActivation>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceReservedStackActivationEvent;

 private:
  const Method* _method;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Reserved Stack Activation: [");
    ts.print_val("Java Method", _method);
    ts.print("]\n");
  }

 public:
  void set_method(const Method* value) { this->_method = value; }

  bool should_write(void) {
    return true;
  }


  EventReservedStackActivation(EventStartTime timing=TIMED) : TraceEvent<EventReservedStackActivation>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventClassLoad : public TraceEvent<EventClassLoad>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceClassLoadEvent;

 private:
  const Klass* _loadedClass; 
  const ClassLoaderData* _definingClassLoader; 
  const ClassLoaderData* _initiatingClassLoader;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Class Load: [");
    ts.print_val("Loaded Class", _loadedClass);
    ts.print(", ");
    ts.print_val("Defining Class Loader", _definingClassLoader);
    ts.print(", ");
    ts.print_val("Initiating Class Loader", _initiatingClassLoader);
    ts.print("]\n");
  }

 public:
  void set_loadedClass(const Klass* value) { this->_loadedClass = value; }
  void set_definingClassLoader(const ClassLoaderData* value) { this->_definingClassLoader = value; }
  void set_initiatingClassLoader(const ClassLoaderData* value) { this->_initiatingClassLoader = value; }

  bool should_write(void) {
    return true;
  }


  EventClassLoad(EventStartTime timing=TIMED) : TraceEvent<EventClassLoad>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventClassDefine : public TraceEvent<EventClassDefine>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceClassDefineEvent;

 private:
  const Klass* _definedClass; 
  const ClassLoaderData* _definingClassLoader;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Class Define: [");
    ts.print_val("Defined Class", _definedClass);
    ts.print(", ");
    ts.print_val("Defining Class Loader", _definingClassLoader);
    ts.print("]\n");
  }

 public:
  void set_definedClass(const Klass* value) { this->_definedClass = value; }
  void set_definingClassLoader(const ClassLoaderData* value) { this->_definingClassLoader = value; }

  bool should_write(void) {
    return true;
  }


  EventClassDefine(EventStartTime timing=TIMED) : TraceEvent<EventClassDefine>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventClassUnload : public TraceEvent<EventClassUnload>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceClassUnloadEvent;

 private:
  const Klass* _unloadedClass; 
  const ClassLoaderData* _definingClassLoader;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Class Unload: [");
    ts.print_val("Unloaded Class", _unloadedClass);
    ts.print(", ");
    ts.print_val("Defining Class Loader", _definingClassLoader);
    ts.print("]\n");
  }

 public:
  void set_unloadedClass(const Klass* value) { this->_unloadedClass = value; }
  void set_definingClassLoader(const ClassLoaderData* value) { this->_definingClassLoader = value; }

  bool should_write(void) {
    return true;
  }


  EventClassUnload(EventStartTime timing=TIMED) : TraceEvent<EventClassUnload>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventIntFlagChanged : public TraceEvent<EventIntFlagChanged>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceIntFlagChangedEvent;

 private:
  const char* _name; 
  s4 _oldValue; 
  s4 _newValue; 
  u8 _origin;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Int Flag Changed: [");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Origin", _origin);
    ts.print("]\n");
  }

 public:
  void set_name(const char* value) { this->_name = value; }
  void set_oldValue(s4 value) { this->_oldValue = value; }
  void set_newValue(s4 value) { this->_newValue = value; }
  void set_origin(u8 value) { this->_origin = value; }

  bool should_write(void) {
    return true;
  }


  EventIntFlagChanged(EventStartTime timing=TIMED) : TraceEvent<EventIntFlagChanged>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventUnsignedIntFlagChanged : public TraceEvent<EventUnsignedIntFlagChanged>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceUnsignedIntFlagChangedEvent;

 private:
  const char* _name; 
  unsigned _oldValue; 
  unsigned _newValue; 
  u8 _origin;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Unsigned Int Flag Changed: [");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Origin", _origin);
    ts.print("]\n");
  }

 public:
  void set_name(const char* value) { this->_name = value; }
  void set_oldValue(unsigned value) { this->_oldValue = value; }
  void set_newValue(unsigned value) { this->_newValue = value; }
  void set_origin(u8 value) { this->_origin = value; }

  bool should_write(void) {
    return true;
  }


  EventUnsignedIntFlagChanged(EventStartTime timing=TIMED) : TraceEvent<EventUnsignedIntFlagChanged>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventLongFlagChanged : public TraceEvent<EventLongFlagChanged>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceLongFlagChangedEvent;

 private:
  const char* _name; 
  s8 _oldValue; 
  s8 _newValue; 
  u8 _origin;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Long Flag Changed: [");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Origin", _origin);
    ts.print("]\n");
  }

 public:
  void set_name(const char* value) { this->_name = value; }
  void set_oldValue(s8 value) { this->_oldValue = value; }
  void set_newValue(s8 value) { this->_newValue = value; }
  void set_origin(u8 value) { this->_origin = value; }

  bool should_write(void) {
    return true;
  }


  EventLongFlagChanged(EventStartTime timing=TIMED) : TraceEvent<EventLongFlagChanged>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventUnsignedLongFlagChanged : public TraceEvent<EventUnsignedLongFlagChanged>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceUnsignedLongFlagChangedEvent;

 private:
  const char* _name; 
  u8 _oldValue; 
  u8 _newValue; 
  u8 _origin;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Unsigned Long Flag Changed: [");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Origin", _origin);
    ts.print("]\n");
  }

 public:
  void set_name(const char* value) { this->_name = value; }
  void set_oldValue(u8 value) { this->_oldValue = value; }
  void set_newValue(u8 value) { this->_newValue = value; }
  void set_origin(u8 value) { this->_origin = value; }

  bool should_write(void) {
    return true;
  }


  EventUnsignedLongFlagChanged(EventStartTime timing=TIMED) : TraceEvent<EventUnsignedLongFlagChanged>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventDoubleFlagChanged : public TraceEvent<EventDoubleFlagChanged>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceDoubleFlagChangedEvent;

 private:
  const char* _name; 
  double _oldValue; 
  double _newValue; 
  u8 _origin;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Double Flag Changed: [");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Origin", _origin);
    ts.print("]\n");
  }

 public:
  void set_name(const char* value) { this->_name = value; }
  void set_oldValue(double value) { this->_oldValue = value; }
  void set_newValue(double value) { this->_newValue = value; }
  void set_origin(u8 value) { this->_origin = value; }

  bool should_write(void) {
    return true;
  }


  EventDoubleFlagChanged(EventStartTime timing=TIMED) : TraceEvent<EventDoubleFlagChanged>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventBooleanFlagChanged : public TraceEvent<EventBooleanFlagChanged>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceBooleanFlagChangedEvent;

 private:
  const char* _name; 
  bool _oldValue; 
  bool _newValue; 
  u8 _origin;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Boolean Flag Changed: [");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Origin", _origin);
    ts.print("]\n");
  }

 public:
  void set_name(const char* value) { this->_name = value; }
  void set_oldValue(bool value) { this->_oldValue = value; }
  void set_newValue(bool value) { this->_newValue = value; }
  void set_origin(u8 value) { this->_origin = value; }

  bool should_write(void) {
    return true;
  }


  EventBooleanFlagChanged(EventStartTime timing=TIMED) : TraceEvent<EventBooleanFlagChanged>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventStringFlagChanged : public TraceEvent<EventStringFlagChanged>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceStringFlagChangedEvent;

 private:
  const char* _name; 
  const char* _oldValue; 
  const char* _newValue; 
  u8 _origin;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("String Flag Changed: [");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Origin", _origin);
    ts.print("]\n");
  }

 public:
  void set_name(const char* value) { this->_name = value; }
  void set_oldValue(const char* value) { this->_oldValue = value; }
  void set_newValue(const char* value) { this->_newValue = value; }
  void set_origin(u8 value) { this->_origin = value; }

  bool should_write(void) {
    return true;
  }


  EventStringFlagChanged(EventStartTime timing=TIMED) : TraceEvent<EventStringFlagChanged>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGCHeapSummary : public TraceEvent<EventGCHeapSummary>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGCHeapSummaryEvent;

 private:
  unsigned _gcId; 
  u8 _when; 
  TraceStructVirtualSpace _heapSpace;
  u8 _heapUsed;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Heap Summary: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("When", _when);
    ts.print(", ");
    _heapSpace.writeStruct(ts);
    ts.print(", ");
    ts.print_val("Heap Used", _heapUsed);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_when(u8 value) { this->_when = value; }
  void set_heapSpace(const TraceStructVirtualSpace& value) { this->_heapSpace = value; }
  void set_heapUsed(u8 value) { this->_heapUsed = value; }

  bool should_write(void) {
    return true;
  }


  EventGCHeapSummary(EventStartTime timing=TIMED) : TraceEvent<EventGCHeapSummary>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventMetaspaceSummary : public TraceEvent<EventMetaspaceSummary>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceMetaspaceSummaryEvent;

 private:
  unsigned _gcId; 
  u8 _when; 
  u8 _gcThreshold; 
  TraceStructMetaspaceSizes _metaspace;
  TraceStructMetaspaceSizes _dataSpace;
  TraceStructMetaspaceSizes _classSpace;


  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Metaspace Summary: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("When", _when);
    ts.print(", ");
    ts.print_val("GC Threshold", _gcThreshold);
    ts.print(", ");
    _metaspace.writeStruct(ts);
    ts.print(", ");
    _dataSpace.writeStruct(ts);
    ts.print(", ");
    _classSpace.writeStruct(ts);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_when(u8 value) { this->_when = value; }
  void set_gcThreshold(u8 value) { this->_gcThreshold = value; }
  void set_metaspace(const TraceStructMetaspaceSizes& value) { this->_metaspace = value; }
  void set_dataSpace(const TraceStructMetaspaceSizes& value) { this->_dataSpace = value; }
  void set_classSpace(const TraceStructMetaspaceSizes& value) { this->_classSpace = value; }

  bool should_write(void) {
    return true;
  }


  EventMetaspaceSummary(EventStartTime timing=TIMED) : TraceEvent<EventMetaspaceSummary>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventMetaspaceGCThreshold : public TraceEvent<EventMetaspaceGCThreshold>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceMetaspaceGCThresholdEvent;

 private:
  u8 _oldValue; 
  u8 _newValue; 
  u8 _updater;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Metaspace GC Threshold: [");
    ts.print_val("Old Value", _oldValue);
    ts.print(", ");
    ts.print_val("New Value", _newValue);
    ts.print(", ");
    ts.print_val("Updater", _updater);
    ts.print("]\n");
  }

 public:
  void set_oldValue(u8 value) { this->_oldValue = value; }
  void set_newValue(u8 value) { this->_newValue = value; }
  void set_updater(u8 value) { this->_updater = value; }

  bool should_write(void) {
    return true;
  }


  EventMetaspaceGCThreshold(EventStartTime timing=TIMED) : TraceEvent<EventMetaspaceGCThreshold>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventMetaspaceAllocationFailure : public TraceEvent<EventMetaspaceAllocationFailure>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceMetaspaceAllocationFailureEvent;

 private:
  const ClassLoaderData* _classLoader; 
  bool _anonymousClassLoader; 
  u8 _size; 
  u8 _metadataType; 
  u8 _metaspaceObjectType;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Metaspace Allocation Failure: [");
    ts.print_val("Class Loader", _classLoader);
    ts.print(", ");
    ts.print_val("Anonymous Class Loader", _anonymousClassLoader);
    ts.print(", ");
    ts.print_val("Size", _size);
    ts.print(", ");
    ts.print_val("Metadata Type", _metadataType);
    ts.print(", ");
    ts.print_val("Metaspace Object Type", _metaspaceObjectType);
    ts.print("]\n");
  }

 public:
  void set_classLoader(const ClassLoaderData* value) { this->_classLoader = value; }
  void set_anonymousClassLoader(bool value) { this->_anonymousClassLoader = value; }
  void set_size(u8 value) { this->_size = value; }
  void set_metadataType(u8 value) { this->_metadataType = value; }
  void set_metaspaceObjectType(u8 value) { this->_metaspaceObjectType = value; }

  bool should_write(void) {
    return true;
  }


  EventMetaspaceAllocationFailure(EventStartTime timing=TIMED) : TraceEvent<EventMetaspaceAllocationFailure>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventMetaspaceOOM : public TraceEvent<EventMetaspaceOOM>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceMetaspaceOOMEvent;

 private:
  const ClassLoaderData* _classLoader; 
  bool _anonymousClassLoader; 
  u8 _size; 
  u8 _metadataType; 
  u8 _metaspaceObjectType;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Metaspace Out of Memory: [");
    ts.print_val("Class Loader", _classLoader);
    ts.print(", ");
    ts.print_val("Anonymous Class Loader", _anonymousClassLoader);
    ts.print(", ");
    ts.print_val("Size", _size);
    ts.print(", ");
    ts.print_val("Metadata Type", _metadataType);
    ts.print(", ");
    ts.print_val("Metaspace Object Type", _metaspaceObjectType);
    ts.print("]\n");
  }

 public:
  void set_classLoader(const ClassLoaderData* value) { this->_classLoader = value; }
  void set_anonymousClassLoader(bool value) { this->_anonymousClassLoader = value; }
  void set_size(u8 value) { this->_size = value; }
  void set_metadataType(u8 value) { this->_metadataType = value; }
  void set_metaspaceObjectType(u8 value) { this->_metaspaceObjectType = value; }

  bool should_write(void) {
    return true;
  }


  EventMetaspaceOOM(EventStartTime timing=TIMED) : TraceEvent<EventMetaspaceOOM>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventMetaspaceChunkFreeListSummary : public TraceEvent<EventMetaspaceChunkFreeListSummary>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceMetaspaceChunkFreeListSummaryEvent;

 private:
  unsigned _gcId; 
  u8 _when; 
  u8 _metadataType; 
  u8 _specializedChunks; 
  u8 _specializedChunksTotalSize; 
  u8 _smallChunks; 
  u8 _smallChunksTotalSize; 
  u8 _mediumChunks; 
  u8 _mediumChunksTotalSize; 
  u8 _humongousChunks; 
  u8 _humongousChunksTotalSize;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Metaspace Chunk Free List Summary: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("When", _when);
    ts.print(", ");
    ts.print_val("Metadata Type", _metadataType);
    ts.print(", ");
    ts.print_val("Specialized Chunks", _specializedChunks);
    ts.print(", ");
    ts.print_val("Specialized Chunks Total Size", _specializedChunksTotalSize);
    ts.print(", ");
    ts.print_val("Small Chunks", _smallChunks);
    ts.print(", ");
    ts.print_val("Small Chunks Total Size", _smallChunksTotalSize);
    ts.print(", ");
    ts.print_val("Medium Chunks", _mediumChunks);
    ts.print(", ");
    ts.print_val("Medium Chunks Total Size", _mediumChunksTotalSize);
    ts.print(", ");
    ts.print_val("Humongous Chunks", _humongousChunks);
    ts.print(", ");
    ts.print_val("Humongous Chunks Total Size", _humongousChunksTotalSize);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_when(u8 value) { this->_when = value; }
  void set_metadataType(u8 value) { this->_metadataType = value; }
  void set_specializedChunks(u8 value) { this->_specializedChunks = value; }
  void set_specializedChunksTotalSize(u8 value) { this->_specializedChunksTotalSize = value; }
  void set_smallChunks(u8 value) { this->_smallChunks = value; }
  void set_smallChunksTotalSize(u8 value) { this->_smallChunksTotalSize = value; }
  void set_mediumChunks(u8 value) { this->_mediumChunks = value; }
  void set_mediumChunksTotalSize(u8 value) { this->_mediumChunksTotalSize = value; }
  void set_humongousChunks(u8 value) { this->_humongousChunks = value; }
  void set_humongousChunksTotalSize(u8 value) { this->_humongousChunksTotalSize = value; }

  bool should_write(void) {
    return true;
  }


  EventMetaspaceChunkFreeListSummary(EventStartTime timing=TIMED) : TraceEvent<EventMetaspaceChunkFreeListSummary>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventPSHeapSummary : public TraceEvent<EventPSHeapSummary>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TracePSHeapSummaryEvent;

 private:
  unsigned _gcId; 
  u8 _when; 
  TraceStructVirtualSpace _oldSpace;
  TraceStructObjectSpace _oldObjectSpace;
  TraceStructVirtualSpace _youngSpace;
  TraceStructObjectSpace _edenSpace;
  TraceStructObjectSpace _fromSpace;
  TraceStructObjectSpace _toSpace;


  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Parallel Scavenge Heap Summary: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("When", _when);
    ts.print(", ");
    _oldSpace.writeStruct(ts);
    ts.print(", ");
    _oldObjectSpace.writeStruct(ts);
    ts.print(", ");
    _youngSpace.writeStruct(ts);
    ts.print(", ");
    _edenSpace.writeStruct(ts);
    ts.print(", ");
    _fromSpace.writeStruct(ts);
    ts.print(", ");
    _toSpace.writeStruct(ts);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_when(u8 value) { this->_when = value; }
  void set_oldSpace(const TraceStructVirtualSpace& value) { this->_oldSpace = value; }
  void set_oldObjectSpace(const TraceStructObjectSpace& value) { this->_oldObjectSpace = value; }
  void set_youngSpace(const TraceStructVirtualSpace& value) { this->_youngSpace = value; }
  void set_edenSpace(const TraceStructObjectSpace& value) { this->_edenSpace = value; }
  void set_fromSpace(const TraceStructObjectSpace& value) { this->_fromSpace = value; }
  void set_toSpace(const TraceStructObjectSpace& value) { this->_toSpace = value; }

  bool should_write(void) {
    return true;
  }


  EventPSHeapSummary(EventStartTime timing=TIMED) : TraceEvent<EventPSHeapSummary>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1HeapSummary : public TraceEvent<EventG1HeapSummary>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1HeapSummaryEvent;

 private:
  unsigned _gcId; 
  u8 _when; 
  u8 _edenUsedSize; 
  u8 _edenTotalSize; 
  u8 _survivorUsedSize; 
  unsigned _numberOfRegions;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 Heap Summary: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("When", _when);
    ts.print(", ");
    ts.print_val("Eden Used Size", _edenUsedSize);
    ts.print(", ");
    ts.print_val("Eden Total Size", _edenTotalSize);
    ts.print(", ");
    ts.print_val("Survivor Used Size", _survivorUsedSize);
    ts.print(", ");
    ts.print_val("Number of Regions", _numberOfRegions);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_when(u8 value) { this->_when = value; }
  void set_edenUsedSize(u8 value) { this->_edenUsedSize = value; }
  void set_edenTotalSize(u8 value) { this->_edenTotalSize = value; }
  void set_survivorUsedSize(u8 value) { this->_survivorUsedSize = value; }
  void set_numberOfRegions(unsigned value) { this->_numberOfRegions = value; }

  bool should_write(void) {
    return true;
  }


  EventG1HeapSummary(EventStartTime timing=TIMED) : TraceEvent<EventG1HeapSummary>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGarbageCollection : public TraceEvent<EventGarbageCollection>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGarbageCollectionEvent;

 private:
  unsigned _gcId; 
  u8 _name; 
  u8 _cause; 
  Tickspan _sumOfPauses; 
  Tickspan _longestPause;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Garbage Collection: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Name", _name);
    ts.print(", ");
    ts.print_val("Cause", _cause);
    ts.print(", ");
    ts.print_val("Sum of Pauses", _sumOfPauses.value());
    ts.print(", ");
    ts.print_val("Longest Pause", _longestPause.value());
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_name(u8 value) { this->_name = value; }
  void set_cause(u8 value) { this->_cause = value; }

#if INCLUDE_TRACE
    void set_sumOfPauses(const Tickspan& time) { _sumOfPauses = time; }
#else
    void set_sumOfPauses(const Tickspan& ignore) {}
#endif

#if INCLUDE_TRACE
    void set_longestPause(const Tickspan& time) { _longestPause = time; }
#else
    void set_longestPause(const Tickspan& ignore) {}
#endif


  bool should_write(void) {
    return true;
  }


  EventGarbageCollection(EventStartTime timing=TIMED) : TraceEvent<EventGarbageCollection>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventParallelOldGarbageCollection : public TraceEvent<EventParallelOldGarbageCollection>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceParallelOldGarbageCollectionEvent;

 private:
  unsigned _gcId; 
  u8 _densePrefix;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Parallel Old Garbage Collection: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Dense Prefix", _densePrefix);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_densePrefix(u8 value) { this->_densePrefix = value; }

  bool should_write(void) {
    return true;
  }


  EventParallelOldGarbageCollection(EventStartTime timing=TIMED) : TraceEvent<EventParallelOldGarbageCollection>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventYoungGarbageCollection : public TraceEvent<EventYoungGarbageCollection>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceYoungGarbageCollectionEvent;

 private:
  unsigned _gcId; 
  unsigned _tenuringThreshold;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Young Garbage Collection: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Tenuring Threshold", _tenuringThreshold);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_tenuringThreshold(unsigned value) { this->_tenuringThreshold = value; }

  bool should_write(void) {
    return true;
  }


  EventYoungGarbageCollection(EventStartTime timing=TIMED) : TraceEvent<EventYoungGarbageCollection>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventOldGarbageCollection : public TraceEvent<EventOldGarbageCollection>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceOldGarbageCollectionEvent;

 private:
  unsigned _gcId;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Old Garbage Collection: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }

  bool should_write(void) {
    return true;
  }


  EventOldGarbageCollection(EventStartTime timing=TIMED) : TraceEvent<EventOldGarbageCollection>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1GarbageCollection : public TraceEvent<EventG1GarbageCollection>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1GarbageCollectionEvent;

 private:
  unsigned _gcId; 
  u8 _type;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 Garbage Collection: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Type", _type);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_type(u8 value) { this->_type = value; }

  bool should_write(void) {
    return true;
  }


  EventG1GarbageCollection(EventStartTime timing=TIMED) : TraceEvent<EventG1GarbageCollection>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1MMU : public TraceEvent<EventG1MMU>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1MMUEvent;

 private:
  unsigned _gcId; 
  s8 _timeSlice; 
  s8 _gcTime; 
  s8 _pauseTarget;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 MMU Information: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Time Slice", _timeSlice);
    ts.print(", ");
    ts.print_val("GC Time", _gcTime);
    ts.print(", ");
    ts.print_val("Pause Target", _pauseTarget);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_timeSlice(s8 value) { this->_timeSlice = value; }
  void set_gcTime(s8 value) { this->_gcTime = value; }
  void set_pauseTarget(s8 value) { this->_pauseTarget = value; }

  bool should_write(void) {
    return true;
  }


  EventG1MMU(EventStartTime timing=TIMED) : TraceEvent<EventG1MMU>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventEvacuationInformation : public TraceEvent<EventEvacuationInformation>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceEvacuationInformationEvent;

 private:
  unsigned _gcId; 
  unsigned _cSetRegions; 
  u8 _cSetUsedBefore; 
  u8 _cSetUsedAfter; 
  unsigned _allocationRegions; 
  u8 _allocationRegionsUsedBefore; 
  u8 _allocationRegionsUsedAfter; 
  u8 _bytesCopied; 
  unsigned _regionsFreed;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Evacuation Information: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Collection Set Regions", _cSetRegions);
    ts.print(", ");
    ts.print_val("Collection Set Before", _cSetUsedBefore);
    ts.print(", ");
    ts.print_val("Collection Set After", _cSetUsedAfter);
    ts.print(", ");
    ts.print_val("Allocation Regions", _allocationRegions);
    ts.print(", ");
    ts.print_val("Allocation Regions Before", _allocationRegionsUsedBefore);
    ts.print(", ");
    ts.print_val("Allocation Regions After", _allocationRegionsUsedAfter);
    ts.print(", ");
    ts.print_val("Bytes Copied", _bytesCopied);
    ts.print(", ");
    ts.print_val("Regions Freed", _regionsFreed);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_cSetRegions(unsigned value) { this->_cSetRegions = value; }
  void set_cSetUsedBefore(u8 value) { this->_cSetUsedBefore = value; }
  void set_cSetUsedAfter(u8 value) { this->_cSetUsedAfter = value; }
  void set_allocationRegions(unsigned value) { this->_allocationRegions = value; }
  void set_allocationRegionsUsedBefore(u8 value) { this->_allocationRegionsUsedBefore = value; }
  void set_allocationRegionsUsedAfter(u8 value) { this->_allocationRegionsUsedAfter = value; }
  void set_bytesCopied(u8 value) { this->_bytesCopied = value; }
  void set_regionsFreed(unsigned value) { this->_regionsFreed = value; }

  bool should_write(void) {
    return true;
  }


  EventEvacuationInformation(EventStartTime timing=TIMED) : TraceEvent<EventEvacuationInformation>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGCReferenceStatistics : public TraceEvent<EventGCReferenceStatistics>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGCReferenceStatisticsEvent;

 private:
  unsigned _gcId; 
  u8 _type; 
  u8 _count;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("GC Reference Statistics: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Type", _type);
    ts.print(", ");
    ts.print_val("Total Count", _count);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_type(u8 value) { this->_type = value; }
  void set_count(u8 value) { this->_count = value; }

  bool should_write(void) {
    return true;
  }


  EventGCReferenceStatistics(EventStartTime timing=TIMED) : TraceEvent<EventGCReferenceStatistics>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventObjectCountAfterGC : public TraceEvent<EventObjectCountAfterGC>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceObjectCountAfterGCEvent;

 private:
  unsigned _gcId; 
  const Klass* _objectClass; 
  s8 _count; 
  u8 _totalSize;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Object Count after GC: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Object Class", _objectClass);
    ts.print(", ");
    ts.print_val("Count", _count);
    ts.print(", ");
    ts.print_val("Total Size", _totalSize);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_objectClass(const Klass* value) { this->_objectClass = value; }
  void set_count(s8 value) { this->_count = value; }
  void set_totalSize(u8 value) { this->_totalSize = value; }

  bool should_write(void) {
    return true;
  }


  EventObjectCountAfterGC(EventStartTime timing=TIMED) : TraceEvent<EventObjectCountAfterGC>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1EvacuationYoungStatistics : public TraceEvent<EventG1EvacuationYoungStatistics>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1EvacuationYoungStatisticsEvent;

 private:
  TraceStructG1EvacuationStatistics _statistics;


  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 Evacuation Statistics for Young: [");
    _statistics.writeStruct(ts);
    ts.print("]\n");
  }

 public:
  void set_statistics(const TraceStructG1EvacuationStatistics& value) { this->_statistics = value; }

  bool should_write(void) {
    return true;
  }


  EventG1EvacuationYoungStatistics(EventStartTime timing=TIMED) : TraceEvent<EventG1EvacuationYoungStatistics>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1EvacuationOldStatistics : public TraceEvent<EventG1EvacuationOldStatistics>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1EvacuationOldStatisticsEvent;

 private:
  TraceStructG1EvacuationStatistics _statistics;


  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 Evacuation Memory Statistics for Old: [");
    _statistics.writeStruct(ts);
    ts.print("]\n");
  }

 public:
  void set_statistics(const TraceStructG1EvacuationStatistics& value) { this->_statistics = value; }

  bool should_write(void) {
    return true;
  }


  EventG1EvacuationOldStatistics(EventStartTime timing=TIMED) : TraceEvent<EventG1EvacuationOldStatistics>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1BasicIHOP : public TraceEvent<EventG1BasicIHOP>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1BasicIHOPEvent;

 private:
  unsigned _gcId; 
  u8 _threshold; 
  float _thresholdPercentage; 
  u8 _targetOccupancy; 
  u8 _currentOccupancy; 
  u8 _recentMutatorAllocationSize; 
  s8 _recentMutatorDuration; 
  double _recentAllocationRate; 
  s8 _lastMarkingDuration;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 Basic IHOP Statistics: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Current IHOP Threshold", _threshold);
    ts.print(", ");
    ts.print_val("Current IHOP Threshold", _thresholdPercentage);
    ts.print(", ");
    ts.print_val("Target Occupancy", _targetOccupancy);
    ts.print(", ");
    ts.print_val("Current Occupancy", _currentOccupancy);
    ts.print(", ");
    ts.print_val("Recent Mutator Allocation Size", _recentMutatorAllocationSize);
    ts.print(", ");
    ts.print_val("Recent Mutator Duration", _recentMutatorDuration);
    ts.print(", ");
    ts.print_val("Recent Allocation Rate", _recentAllocationRate);
    ts.print(", ");
    ts.print_val("Last Marking Duration", _lastMarkingDuration);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_threshold(u8 value) { this->_threshold = value; }
  void set_thresholdPercentage(float value) { this->_thresholdPercentage = value; }
  void set_targetOccupancy(u8 value) { this->_targetOccupancy = value; }
  void set_currentOccupancy(u8 value) { this->_currentOccupancy = value; }
  void set_recentMutatorAllocationSize(u8 value) { this->_recentMutatorAllocationSize = value; }
  void set_recentMutatorDuration(s8 value) { this->_recentMutatorDuration = value; }
  void set_recentAllocationRate(double value) { this->_recentAllocationRate = value; }
  void set_lastMarkingDuration(s8 value) { this->_lastMarkingDuration = value; }

  bool should_write(void) {
    return true;
  }


  EventG1BasicIHOP(EventStartTime timing=TIMED) : TraceEvent<EventG1BasicIHOP>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1AdaptiveIHOP : public TraceEvent<EventG1AdaptiveIHOP>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1AdaptiveIHOPEvent;

 private:
  unsigned _gcId; 
  u8 _threshold; 
  float _thresholdPercentage; 
  u8 _ihopTargetOccupancy; 
  u8 _currentOccupancy; 
  u8 _additionalBufferSize; 
  double _predictedAllocationRate; 
  s8 _predictedMarkingDuration; 
  bool _predictionActive;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 Adaptive IHOP Statistics: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Threshold", _threshold);
    ts.print(", ");
    ts.print_val("Threshold", _thresholdPercentage);
    ts.print(", ");
    ts.print_val("IHOP Target Occupancy", _ihopTargetOccupancy);
    ts.print(", ");
    ts.print_val("Current Occupancy", _currentOccupancy);
    ts.print(", ");
    ts.print_val("Additional Buffer", _additionalBufferSize);
    ts.print(", ");
    ts.print_val("Predicted Allocation Rate", _predictedAllocationRate);
    ts.print(", ");
    ts.print_val("Predicted Marking Duration", _predictedMarkingDuration);
    ts.print(", ");
    ts.print_val("Prediction Active", _predictionActive);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_threshold(u8 value) { this->_threshold = value; }
  void set_thresholdPercentage(float value) { this->_thresholdPercentage = value; }
  void set_ihopTargetOccupancy(u8 value) { this->_ihopTargetOccupancy = value; }
  void set_currentOccupancy(u8 value) { this->_currentOccupancy = value; }
  void set_additionalBufferSize(u8 value) { this->_additionalBufferSize = value; }
  void set_predictedAllocationRate(double value) { this->_predictedAllocationRate = value; }
  void set_predictedMarkingDuration(s8 value) { this->_predictedMarkingDuration = value; }
  void set_predictionActive(bool value) { this->_predictionActive = value; }

  bool should_write(void) {
    return true;
  }


  EventG1AdaptiveIHOP(EventStartTime timing=TIMED) : TraceEvent<EventG1AdaptiveIHOP>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventPromoteObjectInNewPLAB : public TraceEvent<EventPromoteObjectInNewPLAB>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TracePromoteObjectInNewPLABEvent;

 private:
  unsigned _gcId; 
  const Klass* _objectClass; 
  u8 _objectSize; 
  unsigned _tenuringAge; 
  bool _tenured; 
  u8 _plabSize;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Promotion in new PLAB: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Object Class", _objectClass);
    ts.print(", ");
    ts.print_val("Object Size", _objectSize);
    ts.print(", ");
    ts.print_val("Object Tenuring Age", _tenuringAge);
    ts.print(", ");
    ts.print_val("Tenured", _tenured);
    ts.print(", ");
    ts.print_val("PLAB Size", _plabSize);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_objectClass(const Klass* value) { this->_objectClass = value; }
  void set_objectSize(u8 value) { this->_objectSize = value; }
  void set_tenuringAge(unsigned value) { this->_tenuringAge = value; }
  void set_tenured(bool value) { this->_tenured = value; }
  void set_plabSize(u8 value) { this->_plabSize = value; }

  bool should_write(void) {
    return true;
  }


  EventPromoteObjectInNewPLAB(EventStartTime timing=TIMED) : TraceEvent<EventPromoteObjectInNewPLAB>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventPromoteObjectOutsidePLAB : public TraceEvent<EventPromoteObjectOutsidePLAB>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TracePromoteObjectOutsidePLABEvent;

 private:
  unsigned _gcId; 
  const Klass* _objectClass; 
  u8 _objectSize; 
  unsigned _tenuringAge; 
  bool _tenured;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Promotion outside PLAB: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Object Class", _objectClass);
    ts.print(", ");
    ts.print_val("Object Size", _objectSize);
    ts.print(", ");
    ts.print_val("Object Tenuring Age", _tenuringAge);
    ts.print(", ");
    ts.print_val("Tenured", _tenured);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_objectClass(const Klass* value) { this->_objectClass = value; }
  void set_objectSize(u8 value) { this->_objectSize = value; }
  void set_tenuringAge(unsigned value) { this->_tenuringAge = value; }
  void set_tenured(bool value) { this->_tenured = value; }

  bool should_write(void) {
    return true;
  }


  EventPromoteObjectOutsidePLAB(EventStartTime timing=TIMED) : TraceEvent<EventPromoteObjectOutsidePLAB>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventPromotionFailed : public TraceEvent<EventPromotionFailed>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TracePromotionFailedEvent;

 private:
  unsigned _gcId; 
  TraceStructCopyFailed _promotionFailed;
  u8 _thread;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Promotion Failed: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    _promotionFailed.writeStruct(ts);
    ts.print(", ");
    ts.print_val("Running thread", _thread);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_promotionFailed(const TraceStructCopyFailed& value) { this->_promotionFailed = value; }
  void set_thread(u8 value) { this->_thread = value; }

  bool should_write(void) {
    return true;
  }


  EventPromotionFailed(EventStartTime timing=TIMED) : TraceEvent<EventPromotionFailed>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventEvacuationFailed : public TraceEvent<EventEvacuationFailed>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceEvacuationFailedEvent;

 private:
  unsigned _gcId; 
  TraceStructCopyFailed _evacuationFailed;


  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Evacuation Failed: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    _evacuationFailed.writeStruct(ts);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_evacuationFailed(const TraceStructCopyFailed& value) { this->_evacuationFailed = value; }

  bool should_write(void) {
    return true;
  }


  EventEvacuationFailed(EventStartTime timing=TIMED) : TraceEvent<EventEvacuationFailed>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventConcurrentModeFailure : public TraceEvent<EventConcurrentModeFailure>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceConcurrentModeFailureEvent;

 private:
  unsigned _gcId;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Concurrent Mode Failure: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }

  bool should_write(void) {
    return true;
  }


  EventConcurrentModeFailure(EventStartTime timing=TIMED) : TraceEvent<EventConcurrentModeFailure>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGCPhasePause : public TraceEvent<EventGCPhasePause>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGCPhasePauseEvent;

 private:
  unsigned _gcId; 
  const char* _name;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("GC Phase Pause: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Name", _name);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_name(const char* value) { this->_name = value; }

  bool should_write(void) {
    return true;
  }


  EventGCPhasePause(EventStartTime timing=TIMED) : TraceEvent<EventGCPhasePause>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGCPhasePauseLevel1 : public TraceEvent<EventGCPhasePauseLevel1>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGCPhasePauseLevel1Event;

 private:
  unsigned _gcId; 
  const char* _name;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("GC Phase Pause Level 1: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Name", _name);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_name(const char* value) { this->_name = value; }

  bool should_write(void) {
    return true;
  }


  EventGCPhasePauseLevel1(EventStartTime timing=TIMED) : TraceEvent<EventGCPhasePauseLevel1>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGCPhasePauseLevel2 : public TraceEvent<EventGCPhasePauseLevel2>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGCPhasePauseLevel2Event;

 private:
  unsigned _gcId; 
  const char* _name;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("GC Phase Pause Level 2: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Name", _name);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_name(const char* value) { this->_name = value; }

  bool should_write(void) {
    return true;
  }


  EventGCPhasePauseLevel2(EventStartTime timing=TIMED) : TraceEvent<EventGCPhasePauseLevel2>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGCPhasePauseLevel3 : public TraceEvent<EventGCPhasePauseLevel3>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGCPhasePauseLevel3Event;

 private:
  unsigned _gcId; 
  const char* _name;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("GC Phase Pause Level 3: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Name", _name);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_name(const char* value) { this->_name = value; }

  bool should_write(void) {
    return true;
  }


  EventGCPhasePauseLevel3(EventStartTime timing=TIMED) : TraceEvent<EventGCPhasePauseLevel3>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventGCPhaseConcurrent : public TraceEvent<EventGCPhaseConcurrent>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceGCPhaseConcurrentEvent;

 private:
  unsigned _gcId; 
  const char* _name;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("GC Phase Concurrent: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Name", _name);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_name(const char* value) { this->_name = value; }

  bool should_write(void) {
    return true;
  }


  EventGCPhaseConcurrent(EventStartTime timing=TIMED) : TraceEvent<EventGCPhaseConcurrent>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventAllocationRequiringGC : public TraceEvent<EventAllocationRequiringGC>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceAllocationRequiringGCEvent;

 private:
  unsigned _gcId; 
  u8 _size;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Allocation Requiring GC: [");
    ts.print_val("Pending GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Allocation Size", _size);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_size(u8 value) { this->_size = value; }

  bool should_write(void) {
    return true;
  }


  EventAllocationRequiringGC(EventStartTime timing=TIMED) : TraceEvent<EventAllocationRequiringGC>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventTenuringDistribution : public TraceEvent<EventTenuringDistribution>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceTenuringDistributionEvent;

 private:
  unsigned _gcId; 
  unsigned _age; 
  u8 _size;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Tenuring Distribution: [");
    ts.print_val("GC Identifier", _gcId);
    ts.print(", ");
    ts.print_val("Age", _age);
    ts.print(", ");
    ts.print_val("Size", _size);
    ts.print("]\n");
  }

 public:
  void set_gcId(unsigned value) { this->_gcId = value; }
  void set_age(unsigned value) { this->_age = value; }
  void set_size(u8 value) { this->_size = value; }

  bool should_write(void) {
    return true;
  }


  EventTenuringDistribution(EventStartTime timing=TIMED) : TraceEvent<EventTenuringDistribution>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventG1HeapRegionTypeChange : public TraceEvent<EventG1HeapRegionTypeChange>
{
 public:
  static const bool hasThread = false;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceG1HeapRegionTypeChangeEvent;

 private:
  unsigned _index; 
  u8 _from; 
  u8 _to; 
  u8 _start; 
  u8 _used; 
  unsigned _allocationContext;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("G1 Heap Region Type Change: [");
    ts.print_val("Index", _index);
    ts.print(", ");
    ts.print_val("From", _from);
    ts.print(", ");
    ts.print_val("To", _to);
    ts.print(", ");
    ts.print_val("Start", _start);
    ts.print(", ");
    ts.print_val("Used", _used);
    ts.print(", ");
    ts.print_val("Allocation Context", _allocationContext);
    ts.print("]\n");
  }

 public:
  void set_index(unsigned value) { this->_index = value; }
  void set_from(u8 value) { this->_from = value; }
  void set_to(u8 value) { this->_to = value; }
  void set_start(u8 value) { this->_start = value; }
  void set_used(u8 value) { this->_used = value; }
  void set_allocationContext(unsigned value) { this->_allocationContext = value; }

  bool should_write(void) {
    return true;
  }


  EventG1HeapRegionTypeChange(EventStartTime timing=TIMED) : TraceEvent<EventG1HeapRegionTypeChange>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventCompilation : public TraceEvent<EventCompilation>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceCompilationEvent;

 private:
  const Method* _method; 
  unsigned _compileId; 
  u2 _compileLevel; 
  bool _succeded; 
  bool _isOsr; 
  u8 _codeSize; 
  u8 _inlinedBytes;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Compilation: [");
    ts.print_val("Java Method", _method);
    ts.print(", ");
    ts.print_val("Compilation Identifier", _compileId);
    ts.print(", ");
    ts.print_val("Compilation Level", _compileLevel);
    ts.print(", ");
    ts.print_val("Succeeded", _succeded);
    ts.print(", ");
    ts.print_val("On Stack Replacement", _isOsr);
    ts.print(", ");
    ts.print_val("Compiled Code Size", _codeSize);
    ts.print(", ");
    ts.print_val("Inlined Code Size", _inlinedBytes);
    ts.print("]\n");
  }

 public:
  void set_method(const Method* value) { this->_method = value; }
  void set_compileId(unsigned value) { this->_compileId = value; }
  void set_compileLevel(u2 value) { this->_compileLevel = value; }
  void set_succeded(bool value) { this->_succeded = value; }
  void set_isOsr(bool value) { this->_isOsr = value; }
  void set_codeSize(u8 value) { this->_codeSize = value; }
  void set_inlinedBytes(u8 value) { this->_inlinedBytes = value; }

  bool should_write(void) {
    return true;
  }


  EventCompilation(EventStartTime timing=TIMED) : TraceEvent<EventCompilation>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventCompilerPhase : public TraceEvent<EventCompilerPhase>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceCompilerPhaseEvent;

 private:
  u8 _phase; 
  unsigned _compileId; 
  u2 _phaseLevel;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Compiler Phase: [");
    ts.print_val("Compile Phase", _phase);
    ts.print(", ");
    ts.print_val("Compilation Identifier", _compileId);
    ts.print(", ");
    ts.print_val("Phase Level", _phaseLevel);
    ts.print("]\n");
  }

 public:
  void set_phase(u8 value) { this->_phase = value; }
  void set_compileId(unsigned value) { this->_compileId = value; }
  void set_phaseLevel(u2 value) { this->_phaseLevel = value; }

  bool should_write(void) {
    return true;
  }


  EventCompilerPhase(EventStartTime timing=TIMED) : TraceEvent<EventCompilerPhase>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventCompilationFailure : public TraceEvent<EventCompilationFailure>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceCompilationFailureEvent;

 private:
  const char* _failureMessage; 
  unsigned _compileId;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Compilation Failure: [");
    ts.print_val("Failure Message", _failureMessage);
    ts.print(", ");
    ts.print_val("Compilation Identifier", _compileId);
    ts.print("]\n");
  }

 public:
  void set_failureMessage(const char* value) { this->_failureMessage = value; }
  void set_compileId(unsigned value) { this->_compileId = value; }

  bool should_write(void) {
    return true;
  }


  EventCompilationFailure(EventStartTime timing=TIMED) : TraceEvent<EventCompilationFailure>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventCompilerInlining : public TraceEvent<EventCompilerInlining>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceCompilerInliningEvent;

 private:
  unsigned _compileId; 
  const Method* _caller; 
  TraceStructCalleeMethod _callee;
  bool _succeeded; 
  const char* _message; 
  s4 _bci;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Method Inlining: [");
    ts.print_val("Compilation Identifier", _compileId);
    ts.print(", ");
    ts.print_val("Caller Method", _caller);
    ts.print(", ");
    _callee.writeStruct(ts);
    ts.print(", ");
    ts.print_val("Succeeded", _succeeded);
    ts.print(", ");
    ts.print_val("Message", _message);
    ts.print(", ");
    ts.print_val("Byte Code Index", _bci);
    ts.print("]\n");
  }

 public:
  void set_compileId(unsigned value) { this->_compileId = value; }
  void set_caller(const Method* value) { this->_caller = value; }
  void set_callee(const TraceStructCalleeMethod& value) { this->_callee = value; }
  void set_succeeded(bool value) { this->_succeeded = value; }
  void set_message(const char* value) { this->_message = value; }
  void set_bci(s4 value) { this->_bci = value; }

  bool should_write(void) {
    return true;
  }


  EventCompilerInlining(EventStartTime timing=TIMED) : TraceEvent<EventCompilerInlining>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventSweepCodeCache : public TraceEvent<EventSweepCodeCache>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceSweepCodeCacheEvent;

 private:
  s4 _sweepId; 
  unsigned _sweptCount; 
  unsigned _flushedCount; 
  unsigned _zombifiedCount;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Sweep Code Cache: [");
    ts.print_val("Sweep Identifier", _sweepId);
    ts.print(", ");
    ts.print_val("Methods Swept", _sweptCount);
    ts.print(", ");
    ts.print_val("Methods Flushed", _flushedCount);
    ts.print(", ");
    ts.print_val("Methods Zombified", _zombifiedCount);
    ts.print("]\n");
  }

 public:
  void set_sweepId(s4 value) { this->_sweepId = value; }
  void set_sweptCount(unsigned value) { this->_sweptCount = value; }
  void set_flushedCount(unsigned value) { this->_flushedCount = value; }
  void set_zombifiedCount(unsigned value) { this->_zombifiedCount = value; }

  bool should_write(void) {
    return true;
  }


  EventSweepCodeCache(EventStartTime timing=TIMED) : TraceEvent<EventSweepCodeCache>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventCodeCacheFull : public TraceEvent<EventCodeCacheFull>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceCodeCacheFullEvent;

 private:
  u8 _codeBlobType; 
  u8 _startAddress; 
  u8 _commitedTopAddress; 
  u8 _reservedTopAddress; 
  s4 _entryCount; 
  s4 _methodCount; 
  s4 _adaptorCount; 
  u8 _unallocatedCapacity; 
  s4 _fullCount;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Code Cache Full: [");
    ts.print_val("Code Heap", _codeBlobType);
    ts.print(", ");
    ts.print_val("Start Address", _startAddress);
    ts.print(", ");
    ts.print_val("Commited Top", _commitedTopAddress);
    ts.print(", ");
    ts.print_val("Reserved Top", _reservedTopAddress);
    ts.print(", ");
    ts.print_val("Entries", _entryCount);
    ts.print(", ");
    ts.print_val("Methods", _methodCount);
    ts.print(", ");
    ts.print_val("Adaptors", _adaptorCount);
    ts.print(", ");
    ts.print_val("Unallocated", _unallocatedCapacity);
    ts.print(", ");
    ts.print_val("Full Count", _fullCount);
    ts.print("]\n");
  }

 public:
  void set_codeBlobType(u8 value) { this->_codeBlobType = value; }
  void set_startAddress(u8 value) { this->_startAddress = value; }
  void set_commitedTopAddress(u8 value) { this->_commitedTopAddress = value; }
  void set_reservedTopAddress(u8 value) { this->_reservedTopAddress = value; }
  void set_entryCount(s4 value) { this->_entryCount = value; }
  void set_methodCount(s4 value) { this->_methodCount = value; }
  void set_adaptorCount(s4 value) { this->_adaptorCount = value; }
  void set_unallocatedCapacity(u8 value) { this->_unallocatedCapacity = value; }
  void set_fullCount(s4 value) { this->_fullCount = value; }

  bool should_write(void) {
    return true;
  }


  EventCodeCacheFull(EventStartTime timing=TIMED) : TraceEvent<EventCodeCacheFull>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventSafepointBegin : public TraceEvent<EventSafepointBegin>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceSafepointBeginEvent;

 private:
  s4 _safepointId; 
  s4 _totalThreadCount; 
  s4 _jniCriticalThreadCount;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Safepoint Begin: [");
    ts.print_val("Safepoint Identifier", _safepointId);
    ts.print(", ");
    ts.print_val("Total Threads", _totalThreadCount);
    ts.print(", ");
    ts.print_val("JNI Critical Threads", _jniCriticalThreadCount);
    ts.print("]\n");
  }

 public:
  void set_safepointId(s4 value) { this->_safepointId = value; }
  void set_totalThreadCount(s4 value) { this->_totalThreadCount = value; }
  void set_jniCriticalThreadCount(s4 value) { this->_jniCriticalThreadCount = value; }

  bool should_write(void) {
    return true;
  }


  EventSafepointBegin(EventStartTime timing=TIMED) : TraceEvent<EventSafepointBegin>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventSafepointStateSynchronization : public TraceEvent<EventSafepointStateSynchronization>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceSafepointStateSynchronizationEvent;

 private:
  s4 _safepointId; 
  s4 _initialThreadCount; 
  s4 _runningThreadCount; 
  s4 _iterations;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Safepoint State Synchronization: [");
    ts.print_val("Safepoint Identifier", _safepointId);
    ts.print(", ");
    ts.print_val("Initial Threads", _initialThreadCount);
    ts.print(", ");
    ts.print_val("Running Threads", _runningThreadCount);
    ts.print(", ");
    ts.print_val("Iterations", _iterations);
    ts.print("]\n");
  }

 public:
  void set_safepointId(s4 value) { this->_safepointId = value; }
  void set_initialThreadCount(s4 value) { this->_initialThreadCount = value; }
  void set_runningThreadCount(s4 value) { this->_runningThreadCount = value; }
  void set_iterations(s4 value) { this->_iterations = value; }

  bool should_write(void) {
    return true;
  }


  EventSafepointStateSynchronization(EventStartTime timing=TIMED) : TraceEvent<EventSafepointStateSynchronization>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventSafepointWaitBlocked : public TraceEvent<EventSafepointWaitBlocked>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceSafepointWaitBlockedEvent;

 private:
  s4 _safepointId; 
  s4 _runningThreadCount;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Safepoint Wait Blocked: [");
    ts.print_val("Safepoint Identifier", _safepointId);
    ts.print(", ");
    ts.print_val("Running Threads", _runningThreadCount);
    ts.print("]\n");
  }

 public:
  void set_safepointId(s4 value) { this->_safepointId = value; }
  void set_runningThreadCount(s4 value) { this->_runningThreadCount = value; }

  bool should_write(void) {
    return true;
  }


  EventSafepointWaitBlocked(EventStartTime timing=TIMED) : TraceEvent<EventSafepointWaitBlocked>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventSafepointCleanup : public TraceEvent<EventSafepointCleanup>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceSafepointCleanupEvent;

 private:
  s4 _safepointId;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Safepoint Cleanup: [");
    ts.print_val("Safepoint Identifier", _safepointId);
    ts.print("]\n");
  }

 public:
  void set_safepointId(s4 value) { this->_safepointId = value; }

  bool should_write(void) {
    return true;
  }


  EventSafepointCleanup(EventStartTime timing=TIMED) : TraceEvent<EventSafepointCleanup>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventSafepointCleanupTask : public TraceEvent<EventSafepointCleanupTask>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceSafepointCleanupTaskEvent;

 private:
  s4 _safepointId; 
  const char* _name;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Safepoint Cleanup Task: [");
    ts.print_val("Safepoint Identifier", _safepointId);
    ts.print(", ");
    ts.print_val("Task Name", _name);
    ts.print("]\n");
  }

 public:
  void set_safepointId(s4 value) { this->_safepointId = value; }
  void set_name(const char* value) { this->_name = value; }

  bool should_write(void) {
    return true;
  }


  EventSafepointCleanupTask(EventStartTime timing=TIMED) : TraceEvent<EventSafepointCleanupTask>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventSafepointEnd : public TraceEvent<EventSafepointEnd>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceSafepointEndEvent;

 private:
  s4 _safepointId;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Safepoint End: [");
    ts.print_val("Safepoint Identifier", _safepointId);
    ts.print("]\n");
  }

 public:
  void set_safepointId(s4 value) { this->_safepointId = value; }

  bool should_write(void) {
    return true;
  }


  EventSafepointEnd(EventStartTime timing=TIMED) : TraceEvent<EventSafepointEnd>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventExecuteVMOperation : public TraceEvent<EventExecuteVMOperation>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = false;
  static const bool isInstant = false;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceExecuteVMOperationEvent;

 private:
  u8 _operation; 
  bool _safepoint; 
  bool _blocking; 
  u8 _caller; 
  s4 _safepointId;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("VM Operation: [");
    ts.print_val("Operation", _operation);
    ts.print(", ");
    ts.print_val("At Safepoint", _safepoint);
    ts.print(", ");
    ts.print_val("Caller Blocked", _blocking);
    ts.print(", ");
    ts.print_val("Caller", _caller);
    ts.print(", ");
    ts.print_val("Safepoint Identifier", _safepointId);
    ts.print("]\n");
  }

 public:
  void set_operation(u8 value) { this->_operation = value; }
  void set_safepoint(bool value) { this->_safepoint = value; }
  void set_blocking(bool value) { this->_blocking = value; }
  void set_caller(u8 value) { this->_caller = value; }
  void set_safepointId(s4 value) { this->_safepointId = value; }

  bool should_write(void) {
    return true;
  }


  EventExecuteVMOperation(EventStartTime timing=TIMED) : TraceEvent<EventExecuteVMOperation>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventObjectAllocationInNewTLAB : public TraceEvent<EventObjectAllocationInNewTLAB>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceObjectAllocationInNewTLABEvent;

 private:
  const Klass* _objectClass; 
  u8 _allocationSize; 
  u8 _tlabSize;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Allocation in new TLAB: [");
    ts.print_val("Object Class", _objectClass);
    ts.print(", ");
    ts.print_val("Allocation Size", _allocationSize);
    ts.print(", ");
    ts.print_val("TLAB Size", _tlabSize);
    ts.print("]\n");
  }

 public:
  void set_objectClass(const Klass* value) { this->_objectClass = value; }
  void set_allocationSize(u8 value) { this->_allocationSize = value; }
  void set_tlabSize(u8 value) { this->_tlabSize = value; }

  bool should_write(void) {
    return true;
  }


  EventObjectAllocationInNewTLAB(EventStartTime timing=TIMED) : TraceEvent<EventObjectAllocationInNewTLAB>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};

class EventObjectAllocationOutsideTLAB : public TraceEvent<EventObjectAllocationOutsideTLAB>
{
 public:
  static const bool hasThread = true;
  static const bool hasStackTrace = true;
  static const bool isInstant = true;
  static const bool isRequestable = false;
  static const TraceEventId eventId = TraceObjectAllocationOutsideTLABEvent;

 private:
  const Klass* _objectClass; 
  u8 _allocationSize;

  void writeEventContent(void) {
    TraceStream ts;
    ts.print("Allocation outside TLAB: [");
    ts.print_val("Object Class", _objectClass);
    ts.print(", ");
    ts.print_val("Allocation Size", _allocationSize);
    ts.print("]\n");
  }

 public:
  void set_objectClass(const Klass* value) { this->_objectClass = value; }
  void set_allocationSize(u8 value) { this->_allocationSize = value; }

  bool should_write(void) {
    return true;
  }


  EventObjectAllocationOutsideTLAB(EventStartTime timing=TIMED) : TraceEvent<EventObjectAllocationOutsideTLAB>(timing) {}

  void writeEvent(void) {
    if (UseLockedTracing) {
      ttyLocker lock;
      writeEventContent();
    } else {
      writeEventContent();
    }
  }
};



#else // !INCLUDE_TRACE

class TraceEvent {
public:
  TraceEvent() {}
  void set_starttime(const Ticks& ignore) {}
  void set_endtime(const Ticks& ignore) {}
  bool should_commit() const { return false; }
  static bool is_enabled() { return false; }
  void commit() {}
  void cancel() {}
};

  
struct TraceStructVirtualSpace 
{
public:
  void set_start(u8 value) { }
  void set_committedEnd(u8 value) { }
  void set_committedSize(u8 value) { }
  void set_reservedEnd(u8 value) { }
  void set_reservedSize(u8 value) { }
};

struct TraceStructObjectSpace 
{
public:
  void set_start(u8 value) { }
  void set_end(u8 value) { }
  void set_used(u8 value) { }
  void set_size(u8 value) { }
};

struct TraceStructMetaspaceSizes 
{
public:
  void set_committed(u8 value) { }
  void set_used(u8 value) { }
  void set_reserved(u8 value) { }
};

struct TraceStructCopyFailed 
{
public:
  void set_objectCount(u8 value) { }
  void set_firstSize(u8 value) { }
  void set_smallestSize(u8 value) { }
  void set_totalSize(u8 value) { }
};

struct TraceStructG1EvacuationStatistics 
{
public:
  void set_gcId(unsigned value) { }
  void set_allocated(u8 value) { }
  void set_wasted(u8 value) { }
  void set_used(u8 value) { }
  void set_undoWaste(u8 value) { }
  void set_regionEndWaste(u8 value) { }
  void set_regionsRefilled(unsigned value) { }
  void set_directAllocated(u8 value) { }
  void set_failureUsed(u8 value) { }
  void set_failureWaste(u8 value) { }
};

struct TraceStructCalleeMethod 
{
public:
  void set_type(const char* value) { }
  void set_name(const char* value) { }
  void set_descriptor(const char* value) { }
};
class EventThreadStart : public TraceEvent
{
 public:
  EventThreadStart(bool ignore=true) {}
  void set_thread(u8 value) { }
};

class EventThreadEnd : public TraceEvent
{
 public:
  EventThreadEnd(bool ignore=true) {}
  void set_thread(u8 value) { }
};

class EventThreadSleep : public TraceEvent
{
 public:
  EventThreadSleep(bool ignore=true) {}
  void set_time(s8 value) { }
};

class EventThreadPark : public TraceEvent
{
 public:
  EventThreadPark(bool ignore=true) {}
  void set_parkedClass(const Klass* value) { }
  void set_timeout(s8 value) { }
  void set_address(u8 value) { }
};

class EventJavaMonitorEnter : public TraceEvent
{
 public:
  EventJavaMonitorEnter(bool ignore=true) {}
  void set_monitorClass(const Klass* value) { }
  void set_previousOwner(u8 value) { }
  void set_address(u8 value) { }
};

class EventJavaMonitorWait : public TraceEvent
{
 public:
  EventJavaMonitorWait(bool ignore=true) {}
  void set_monitorClass(const Klass* value) { }
  void set_notifier(u8 value) { }
  void set_timeout(s8 value) { }
  void set_timedOut(bool value) { }
  void set_address(u8 value) { }
};

class EventJavaMonitorInflate : public TraceEvent
{
 public:
  EventJavaMonitorInflate(bool ignore=true) {}
  void set_monitorClass(const Klass* value) { }
  void set_address(u8 value) { }
  void set_cause(u8 value) { }
};

class EventReservedStackActivation : public TraceEvent
{
 public:
  EventReservedStackActivation(bool ignore=true) {}
  void set_method(const Method* value) { }
};

class EventClassLoad : public TraceEvent
{
 public:
  EventClassLoad(bool ignore=true) {}
  void set_loadedClass(const Klass* value) { }
  void set_definingClassLoader(const ClassLoaderData* value) { }
  void set_initiatingClassLoader(const ClassLoaderData* value) { }
};

class EventClassDefine : public TraceEvent
{
 public:
  EventClassDefine(bool ignore=true) {}
  void set_definedClass(const Klass* value) { }
  void set_definingClassLoader(const ClassLoaderData* value) { }
};

class EventClassUnload : public TraceEvent
{
 public:
  EventClassUnload(bool ignore=true) {}
  void set_unloadedClass(const Klass* value) { }
  void set_definingClassLoader(const ClassLoaderData* value) { }
};

class EventIntFlagChanged : public TraceEvent
{
 public:
  EventIntFlagChanged(bool ignore=true) {}
  void set_name(const char* value) { }
  void set_oldValue(s4 value) { }
  void set_newValue(s4 value) { }
  void set_origin(u8 value) { }
};

class EventUnsignedIntFlagChanged : public TraceEvent
{
 public:
  EventUnsignedIntFlagChanged(bool ignore=true) {}
  void set_name(const char* value) { }
  void set_oldValue(unsigned value) { }
  void set_newValue(unsigned value) { }
  void set_origin(u8 value) { }
};

class EventLongFlagChanged : public TraceEvent
{
 public:
  EventLongFlagChanged(bool ignore=true) {}
  void set_name(const char* value) { }
  void set_oldValue(s8 value) { }
  void set_newValue(s8 value) { }
  void set_origin(u8 value) { }
};

class EventUnsignedLongFlagChanged : public TraceEvent
{
 public:
  EventUnsignedLongFlagChanged(bool ignore=true) {}
  void set_name(const char* value) { }
  void set_oldValue(u8 value) { }
  void set_newValue(u8 value) { }
  void set_origin(u8 value) { }
};

class EventDoubleFlagChanged : public TraceEvent
{
 public:
  EventDoubleFlagChanged(bool ignore=true) {}
  void set_name(const char* value) { }
  void set_oldValue(double value) { }
  void set_newValue(double value) { }
  void set_origin(u8 value) { }
};

class EventBooleanFlagChanged : public TraceEvent
{
 public:
  EventBooleanFlagChanged(bool ignore=true) {}
  void set_name(const char* value) { }
  void set_oldValue(bool value) { }
  void set_newValue(bool value) { }
  void set_origin(u8 value) { }
};

class EventStringFlagChanged : public TraceEvent
{
 public:
  EventStringFlagChanged(bool ignore=true) {}
  void set_name(const char* value) { }
  void set_oldValue(const char* value) { }
  void set_newValue(const char* value) { }
  void set_origin(u8 value) { }
};

class EventGCHeapSummary : public TraceEvent
{
 public:
  EventGCHeapSummary(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_when(u8 value) { }
  void set_heapSpace(const TraceStructVirtualSpace& value) { }
  void set_heapUsed(u8 value) { }
};

class EventMetaspaceSummary : public TraceEvent
{
 public:
  EventMetaspaceSummary(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_when(u8 value) { }
  void set_gcThreshold(u8 value) { }
  void set_metaspace(const TraceStructMetaspaceSizes& value) { }
  void set_dataSpace(const TraceStructMetaspaceSizes& value) { }
  void set_classSpace(const TraceStructMetaspaceSizes& value) { }
};

class EventMetaspaceGCThreshold : public TraceEvent
{
 public:
  EventMetaspaceGCThreshold(bool ignore=true) {}
  void set_oldValue(u8 value) { }
  void set_newValue(u8 value) { }
  void set_updater(u8 value) { }
};

class EventMetaspaceAllocationFailure : public TraceEvent
{
 public:
  EventMetaspaceAllocationFailure(bool ignore=true) {}
  void set_classLoader(const ClassLoaderData* value) { }
  void set_anonymousClassLoader(bool value) { }
  void set_size(u8 value) { }
  void set_metadataType(u8 value) { }
  void set_metaspaceObjectType(u8 value) { }
};

class EventMetaspaceOOM : public TraceEvent
{
 public:
  EventMetaspaceOOM(bool ignore=true) {}
  void set_classLoader(const ClassLoaderData* value) { }
  void set_anonymousClassLoader(bool value) { }
  void set_size(u8 value) { }
  void set_metadataType(u8 value) { }
  void set_metaspaceObjectType(u8 value) { }
};

class EventMetaspaceChunkFreeListSummary : public TraceEvent
{
 public:
  EventMetaspaceChunkFreeListSummary(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_when(u8 value) { }
  void set_metadataType(u8 value) { }
  void set_specializedChunks(u8 value) { }
  void set_specializedChunksTotalSize(u8 value) { }
  void set_smallChunks(u8 value) { }
  void set_smallChunksTotalSize(u8 value) { }
  void set_mediumChunks(u8 value) { }
  void set_mediumChunksTotalSize(u8 value) { }
  void set_humongousChunks(u8 value) { }
  void set_humongousChunksTotalSize(u8 value) { }
};

class EventPSHeapSummary : public TraceEvent
{
 public:
  EventPSHeapSummary(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_when(u8 value) { }
  void set_oldSpace(const TraceStructVirtualSpace& value) { }
  void set_oldObjectSpace(const TraceStructObjectSpace& value) { }
  void set_youngSpace(const TraceStructVirtualSpace& value) { }
  void set_edenSpace(const TraceStructObjectSpace& value) { }
  void set_fromSpace(const TraceStructObjectSpace& value) { }
  void set_toSpace(const TraceStructObjectSpace& value) { }
};

class EventG1HeapSummary : public TraceEvent
{
 public:
  EventG1HeapSummary(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_when(u8 value) { }
  void set_edenUsedSize(u8 value) { }
  void set_edenTotalSize(u8 value) { }
  void set_survivorUsedSize(u8 value) { }
  void set_numberOfRegions(unsigned value) { }
};

class EventGarbageCollection : public TraceEvent
{
 public:
  EventGarbageCollection(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_name(u8 value) { }
  void set_cause(u8 value) { }
  void set_sumOfPauses(Tickspan value) { }
  void set_longestPause(Tickspan value) { }
};

class EventParallelOldGarbageCollection : public TraceEvent
{
 public:
  EventParallelOldGarbageCollection(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_densePrefix(u8 value) { }
};

class EventYoungGarbageCollection : public TraceEvent
{
 public:
  EventYoungGarbageCollection(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_tenuringThreshold(unsigned value) { }
};

class EventOldGarbageCollection : public TraceEvent
{
 public:
  EventOldGarbageCollection(bool ignore=true) {}
  void set_gcId(unsigned value) { }
};

class EventG1GarbageCollection : public TraceEvent
{
 public:
  EventG1GarbageCollection(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_type(u8 value) { }
};

class EventG1MMU : public TraceEvent
{
 public:
  EventG1MMU(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_timeSlice(s8 value) { }
  void set_gcTime(s8 value) { }
  void set_pauseTarget(s8 value) { }
};

class EventEvacuationInformation : public TraceEvent
{
 public:
  EventEvacuationInformation(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_cSetRegions(unsigned value) { }
  void set_cSetUsedBefore(u8 value) { }
  void set_cSetUsedAfter(u8 value) { }
  void set_allocationRegions(unsigned value) { }
  void set_allocationRegionsUsedBefore(u8 value) { }
  void set_allocationRegionsUsedAfter(u8 value) { }
  void set_bytesCopied(u8 value) { }
  void set_regionsFreed(unsigned value) { }
};

class EventGCReferenceStatistics : public TraceEvent
{
 public:
  EventGCReferenceStatistics(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_type(u8 value) { }
  void set_count(u8 value) { }
};

class EventObjectCountAfterGC : public TraceEvent
{
 public:
  EventObjectCountAfterGC(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_objectClass(const Klass* value) { }
  void set_count(s8 value) { }
  void set_totalSize(u8 value) { }
};

class EventG1EvacuationYoungStatistics : public TraceEvent
{
 public:
  EventG1EvacuationYoungStatistics(bool ignore=true) {}
  void set_statistics(const TraceStructG1EvacuationStatistics& value) { }
};

class EventG1EvacuationOldStatistics : public TraceEvent
{
 public:
  EventG1EvacuationOldStatistics(bool ignore=true) {}
  void set_statistics(const TraceStructG1EvacuationStatistics& value) { }
};

class EventG1BasicIHOP : public TraceEvent
{
 public:
  EventG1BasicIHOP(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_threshold(u8 value) { }
  void set_thresholdPercentage(float value) { }
  void set_targetOccupancy(u8 value) { }
  void set_currentOccupancy(u8 value) { }
  void set_recentMutatorAllocationSize(u8 value) { }
  void set_recentMutatorDuration(s8 value) { }
  void set_recentAllocationRate(double value) { }
  void set_lastMarkingDuration(s8 value) { }
};

class EventG1AdaptiveIHOP : public TraceEvent
{
 public:
  EventG1AdaptiveIHOP(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_threshold(u8 value) { }
  void set_thresholdPercentage(float value) { }
  void set_ihopTargetOccupancy(u8 value) { }
  void set_currentOccupancy(u8 value) { }
  void set_additionalBufferSize(u8 value) { }
  void set_predictedAllocationRate(double value) { }
  void set_predictedMarkingDuration(s8 value) { }
  void set_predictionActive(bool value) { }
};

class EventPromoteObjectInNewPLAB : public TraceEvent
{
 public:
  EventPromoteObjectInNewPLAB(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_objectClass(const Klass* value) { }
  void set_objectSize(u8 value) { }
  void set_tenuringAge(unsigned value) { }
  void set_tenured(bool value) { }
  void set_plabSize(u8 value) { }
};

class EventPromoteObjectOutsidePLAB : public TraceEvent
{
 public:
  EventPromoteObjectOutsidePLAB(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_objectClass(const Klass* value) { }
  void set_objectSize(u8 value) { }
  void set_tenuringAge(unsigned value) { }
  void set_tenured(bool value) { }
};

class EventPromotionFailed : public TraceEvent
{
 public:
  EventPromotionFailed(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_promotionFailed(const TraceStructCopyFailed& value) { }
  void set_thread(u8 value) { }
};

class EventEvacuationFailed : public TraceEvent
{
 public:
  EventEvacuationFailed(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_evacuationFailed(const TraceStructCopyFailed& value) { }
};

class EventConcurrentModeFailure : public TraceEvent
{
 public:
  EventConcurrentModeFailure(bool ignore=true) {}
  void set_gcId(unsigned value) { }
};

class EventGCPhasePause : public TraceEvent
{
 public:
  EventGCPhasePause(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_name(const char* value) { }
};

class EventGCPhasePauseLevel1 : public TraceEvent
{
 public:
  EventGCPhasePauseLevel1(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_name(const char* value) { }
};

class EventGCPhasePauseLevel2 : public TraceEvent
{
 public:
  EventGCPhasePauseLevel2(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_name(const char* value) { }
};

class EventGCPhasePauseLevel3 : public TraceEvent
{
 public:
  EventGCPhasePauseLevel3(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_name(const char* value) { }
};

class EventGCPhaseConcurrent : public TraceEvent
{
 public:
  EventGCPhaseConcurrent(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_name(const char* value) { }
};

class EventAllocationRequiringGC : public TraceEvent
{
 public:
  EventAllocationRequiringGC(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_size(u8 value) { }
};

class EventTenuringDistribution : public TraceEvent
{
 public:
  EventTenuringDistribution(bool ignore=true) {}
  void set_gcId(unsigned value) { }
  void set_age(unsigned value) { }
  void set_size(u8 value) { }
};

class EventG1HeapRegionTypeChange : public TraceEvent
{
 public:
  EventG1HeapRegionTypeChange(bool ignore=true) {}
  void set_index(unsigned value) { }
  void set_from(u8 value) { }
  void set_to(u8 value) { }
  void set_start(u8 value) { }
  void set_used(u8 value) { }
  void set_allocationContext(unsigned value) { }
};

class EventCompilation : public TraceEvent
{
 public:
  EventCompilation(bool ignore=true) {}
  void set_method(const Method* value) { }
  void set_compileId(unsigned value) { }
  void set_compileLevel(u2 value) { }
  void set_succeded(bool value) { }
  void set_isOsr(bool value) { }
  void set_codeSize(u8 value) { }
  void set_inlinedBytes(u8 value) { }
};

class EventCompilerPhase : public TraceEvent
{
 public:
  EventCompilerPhase(bool ignore=true) {}
  void set_phase(u8 value) { }
  void set_compileId(unsigned value) { }
  void set_phaseLevel(u2 value) { }
};

class EventCompilationFailure : public TraceEvent
{
 public:
  EventCompilationFailure(bool ignore=true) {}
  void set_failureMessage(const char* value) { }
  void set_compileId(unsigned value) { }
};

class EventCompilerInlining : public TraceEvent
{
 public:
  EventCompilerInlining(bool ignore=true) {}
  void set_compileId(unsigned value) { }
  void set_caller(const Method* value) { }
  void set_callee(const TraceStructCalleeMethod& value) { }
  void set_succeeded(bool value) { }
  void set_message(const char* value) { }
  void set_bci(s4 value) { }
};

class EventSweepCodeCache : public TraceEvent
{
 public:
  EventSweepCodeCache(bool ignore=true) {}
  void set_sweepId(s4 value) { }
  void set_sweptCount(unsigned value) { }
  void set_flushedCount(unsigned value) { }
  void set_zombifiedCount(unsigned value) { }
};

class EventCodeCacheFull : public TraceEvent
{
 public:
  EventCodeCacheFull(bool ignore=true) {}
  void set_codeBlobType(u8 value) { }
  void set_startAddress(u8 value) { }
  void set_commitedTopAddress(u8 value) { }
  void set_reservedTopAddress(u8 value) { }
  void set_entryCount(s4 value) { }
  void set_methodCount(s4 value) { }
  void set_adaptorCount(s4 value) { }
  void set_unallocatedCapacity(u8 value) { }
  void set_fullCount(s4 value) { }
};

class EventSafepointBegin : public TraceEvent
{
 public:
  EventSafepointBegin(bool ignore=true) {}
  void set_safepointId(s4 value) { }
  void set_totalThreadCount(s4 value) { }
  void set_jniCriticalThreadCount(s4 value) { }
};

class EventSafepointStateSynchronization : public TraceEvent
{
 public:
  EventSafepointStateSynchronization(bool ignore=true) {}
  void set_safepointId(s4 value) { }
  void set_initialThreadCount(s4 value) { }
  void set_runningThreadCount(s4 value) { }
  void set_iterations(s4 value) { }
};

class EventSafepointWaitBlocked : public TraceEvent
{
 public:
  EventSafepointWaitBlocked(bool ignore=true) {}
  void set_safepointId(s4 value) { }
  void set_runningThreadCount(s4 value) { }
};

class EventSafepointCleanup : public TraceEvent
{
 public:
  EventSafepointCleanup(bool ignore=true) {}
  void set_safepointId(s4 value) { }
};

class EventSafepointCleanupTask : public TraceEvent
{
 public:
  EventSafepointCleanupTask(bool ignore=true) {}
  void set_safepointId(s4 value) { }
  void set_name(const char* value) { }
};

class EventSafepointEnd : public TraceEvent
{
 public:
  EventSafepointEnd(bool ignore=true) {}
  void set_safepointId(s4 value) { }
};

class EventExecuteVMOperation : public TraceEvent
{
 public:
  EventExecuteVMOperation(bool ignore=true) {}
  void set_operation(u8 value) { }
  void set_safepoint(bool value) { }
  void set_blocking(bool value) { }
  void set_caller(u8 value) { }
  void set_safepointId(s4 value) { }
};

class EventObjectAllocationInNewTLAB : public TraceEvent
{
 public:
  EventObjectAllocationInNewTLAB(bool ignore=true) {}
  void set_objectClass(const Klass* value) { }
  void set_allocationSize(u8 value) { }
  void set_tlabSize(u8 value) { }
};

class EventObjectAllocationOutsideTLAB : public TraceEvent
{
 public:
  EventObjectAllocationOutsideTLAB(bool ignore=true) {}
  void set_objectClass(const Klass* value) { }
  void set_allocationSize(u8 value) { }
};



#endif // INCLUDE_TRACE
#endif // TRACEFILES_TRACEEVENTCLASSES_HPP
