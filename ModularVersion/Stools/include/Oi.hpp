#ifndef SCPH_OISHOUT_CLASS_H
#define SCPH_OISHOUT_CLASS_H
#include "Spectrum.hpp"
#include "Utils.hpp"


// =============================================================================
// Abstract base class to keep everything in order
class OiBase {
 protected:
  bool greeted_;
 public:
  OiBase() {;}
  ~OiBase() {;}
  virtual void greet() const=0;
  virtual void bye() const=0;
  virtual bool output() const {return false;}
  virtual void setOutput(const bool&)=0;
};


// =============================================================================
// Other classes ahead
// =============================================================================
class OiInfo : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiInfo() {;}
  ~OiInfo() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiInfo


// =============================================================================
class OiDebug : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiDebug() {;}
  ~OiDebug() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiDebug


// =============================================================================
class OiHello : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiHello() {;}
  ~OiHello() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiHello


// =============================================================================
class OiBye : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiBye() {;}
  ~OiBye() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiBye


// =============================================================================
class OiError : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiError() {;}
  ~OiError() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiError


// =============================================================================
class OiWarning : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiWarning() {;}
  ~OiWarning() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiWarning


// =============================================================================
class OiResult : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiResult() {;}
  ~OiResult() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiResult


// =============================================================================
class OiEmph : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
 public:
  OiEmph() {;}
  OiEmph(const std::string&);
  ~OiEmph() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiEmph


// =============================================================================
class OiReset : public OiBase {
 protected:
  static bool output_;
  static const char* reset_;
 public:
  OiReset() {;}
  ~OiReset() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiReset


// =============================================================================
class OiVerbose : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
 public:
  OiVerbose() {;}
  ~OiVerbose() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiVerbose


// =============================================================================
class OiDummy : public OiBase {
 public:
  OiDummy() {;}
  ~OiDummy() {;}
  void greet() const;
  void bye() const;
  bool output() const {return false;}
  void setOutput(const bool&) {;}
};  // end class OiDummy


// =============================================================================
class OiCount : public OiBase {
 protected:
  static bool output_;
  static const char* colour_;
  static const char* greet_;
  static const char* reset_;
  std::string count_out_;
  void getMsg(int&, int&, const std::string&);
 public:
  OiCount() {;}
  OiCount(int&, int&);
  OiCount(int&, int&, const std::string&);
  ~OiCount() {;}
  void greet() const;
  void bye() const;
  bool output() const {return output_;}
  void setOutput(const bool& out) {output_ = out;}
};  // end class OiCount


// =============================================================================
// Actual interface class
// =============================================================================
template<class Type>
class Oi {
 protected:
  Type shouter_;
  bool greeted_;
  bool modify_;
  bool counter_;
  int level_;
 public:
  Oi()
    : greeted_(false)
    , modify_(false)
    , counter_(false)
    , level_(1)
  {;}
  ~Oi() {
    if (!modify_ && shouter_.output() && !counter_) {
      shouter_.bye();
    }
  }

  void setOutput(const bool& out) {
    shouter_.setOutput(out);
    modify_ = true;
    return;
  }

  template <typename T>Oi &operator<< (const T& v) {
    if (shouter_.output()) {
      if (!greeted_) {
        shouter_.greet();
        greeted_ = true;
      }
      std::cout << v;
    }
    return *this;
  }

  void count(
      const int& entry,
      const int& entries,
      const std::string& msg="Analysing") {
    counter_ = true;
    if (!shouter_.output() || greeted_) {
      return;
    }
    if (entry % 10000 == 0) {
      shouter_.greet();
      std::cout <<  msg << " " << entry << " of " << entries << "  ("
        << scph::dtos(100. * static_cast<double>(entry) /
            static_cast<double>(entries), 1) << " %)"
        << "               \r";
      std::cout.flush();
    }
    if (entry == entries - 1) {
      shouter_.greet();
      std::cout << "Finished : " << msg << " " << entries << " entries"
        << "                            ";
      shouter_.bye();
    }
    return;
  }

  void setOutputLevel(const int& level) {
    level_ = level;
    OiInfo().setOutput(true);
    OiEmph().setOutput(true);
    OiResult().setOutput(true);
    OiHello().setOutput(true);
    OiBye().setOutput(true);
    OiVerbose().setOutput(false);
    OiDebug().setOutput(false);
    OiError().setOutput(true);
    OiWarning().setOutput(true);
    switch (level) {
      case -2:  // Dead
        OiEmph().setOutput(false);
        OiResult().setOutput(false);
      case -1:  // VERY Quiet
        OiWarning().setOutput(false);
      case 0:  // Quiet
        OiInfo().setOutput(false);
        OiHello().setOutput(false);
        OiBye().setOutput(false);
        break;
      case 1:  // Default, as above
        break;
      case 2:  // Debug mode
        OiDebug().setOutput(true);
        break;
      case 3:  // Verbose
        OiVerbose().setOutput(true);
        break;
      case 4:  // EVERYTHING
        OiVerbose().setOutput(true);
        OiDebug().setOutput(true);
        break;
      default:
        std::cout << spectrum::fore::red << "ERROR   : Oi, no OutputLevel '"
          << level_ << "'!" << std::endl;
        std::cout << "ERROR   :   Using defaults." << std::endl;
        break;
    }
    return;
  }

  void quiet() {
    setOutputLevel(0);
    return;
  }

  void debug() {
    setOutputLevel(2);
    return;
  }

  void verbose() {
    setOutputLevel(3);
    return;
  }

  void vverbose() {
    setOutputLevel(4);
    return;
  }

};



#define oiinfo Oi<OiInfo>()
#define oidebug Oi<OiDebug>()
#define oierror Oi<OiError>()
#define oiwarning Oi<OiWarning>()
#define oiinfo Oi<OiInfo>()
#define oidebug Oi<OiDebug>()
#define oiresult Oi<OiResult>()
#define oihello Oi<OiHello>()
#define oibye Oi<OiBye>()
#define oireset Oi<OiReset>()
#define oiemph Oi<OiEmph>()
#define oiopts Oi<OiDummy>()

#endif
