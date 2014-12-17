#define SCPH_OISHOUT_CLASS_H_CXX
#include "Oi.hpp"

#include "Spectrum.hpp"


// =============================================================================
bool OiDebug::output_ = false;
const char* OiDebug::colour_ = spectrum::fore::magenta;
const char* OiDebug::greet_ = "DEBUG   : ";
const char* OiDebug::reset_ = spectrum::reset;
void OiDebug::greet() const {
  std::cout << colour_ << greet_;
}
void OiDebug::bye() const {
  std::cout << reset_ << std::endl;
}


// =============================================================================
bool OiInfo::output_ = true;
const char* OiInfo::colour_ = spectrum::fore::yellow;
const char* OiInfo::greet_ = "SINFO   : ";
const char* OiInfo::reset_ = spectrum::reset;
void OiInfo::greet() const {
  std::cout << colour_ << greet_;
}
void OiInfo::bye() const {
  if (output_) {
    std::cout << reset_ << std::endl;
  }
}


// =============================================================================
bool OiHello::output_ = true;
const char* OiHello::colour_ = spectrum::fore::blue;
const char* OiHello::greet_ = "HELLO   : ";
const char* OiHello::reset_ = spectrum::reset;
void OiHello::greet() const {
  std::cout << colour_ << greet_;
}
void OiHello::bye() const {
  std::cout << reset_ << std::endl;
}


// =============================================================================
bool OiBye::output_ = true;
const char* OiBye::colour_ = spectrum::fore::blue;
const char* OiBye::greet_ = "BYE     : ";
const char* OiBye::reset_ = spectrum::reset;
void OiBye::greet() const {
  std::cout << colour_ << greet_;
}
void OiBye::bye() const {
  std::cout << reset_ << std::endl;
}


// =============================================================================
bool OiError::output_ = true;
const char* OiError::colour_ = spectrum::fore::red;
const char* OiError::greet_ = "ERROR   : ";
const char* OiError::reset_ = spectrum::reset;
void OiError::greet() const {
  std::cout << colour_ << greet_;
}
void OiError::bye() const {
  std::cout << reset_ << std::endl;
}


// =============================================================================
bool OiWarning::output_ = true;
const char* OiWarning::colour_ = spectrum::fore::cyan;
const char* OiWarning::greet_ = "WARNING : ";
const char* OiWarning::reset_ = spectrum::reset;
void OiWarning::greet() const {
  std::cout << colour_ << greet_;
}
void OiWarning::bye() const {
  std::cout << reset_ << std::endl;
}


// =============================================================================
bool OiVerbose::output_ = true;
const char* OiVerbose::colour_ = spectrum::fore::green;
const char* OiVerbose::greet_ = "VERBOSE : ";
const char* OiVerbose::reset_ = spectrum::reset;
void OiVerbose::greet() const {
  std::cout << colour_ << greet_;
}
void OiVerbose::bye() const {
  std::cout << reset_ << std::endl;
}


// =============================================================================
bool OiResult::output_ = true;
const char* OiResult::colour_ = spectrum::fore::green;
const char* OiResult::greet_ = "RESULT  : ";
const char* OiResult::reset_ = spectrum::reset;
void OiResult::greet() const {
  std::cout << colour_ << greet_;
}
void OiResult::bye() const {
  std::cout << reset_ << std::endl;
}


// =============================================================================
bool OiCount::output_ = true;
const char* OiCount::colour_ = spectrum::fore::yellow;
const char* OiCount::greet_ = "COUNT   : ";
const char* OiCount::reset_ = spectrum::reset;
OiCount::OiCount(int& entry, int& entries) {
  getMsg(entry, entries, "Analysing");
}
OiCount::OiCount(int& entry, int& entries, const std::string& msg) {
  getMsg(entry, entries, msg);
}
void OiCount::getMsg(
    int& entry,
    int& entries,
    const std::string& msg) {
  count_out_ = "";
  std::stringstream ss;
  if (entry % 10000 == 0) {
    ss << msg << " " << entry << " of " << entries << "  ("
      << scph::dtos(100. * static_cast<double>(entry) /
          static_cast<double>(entries), 1) << " %)";
  }
  if (entry == entries) {
    ss << "Finished : " << msg << " " << entries << " entries"
      << "         \n";
  }
  count_out_ = ss.str();
  return;
}
void OiCount::greet() const {
  std::cout << colour_ << greet_ << count_out_;
}
void OiCount::bye() const {
  std::cout << "         \r" << spectrum::reset;
  std::cout.flush();
}


// =============================================================================
bool OiEmph::output_ = true;
const char* OiEmph::colour_ = spectrum::fore::white;
const char* OiEmph::greet_ = "EMPH   : ";
OiEmph::OiEmph(const std::string& greet) {
  std::cout << colour_ << greet << std::endl;
}
void OiEmph::greet() const {
  std::cout << colour_ << greet_ << std::endl;
}
void OiEmph::bye() const {;}


// =============================================================================
bool OiReset::output_ = true;
const char* OiReset::reset_ = spectrum::reset;
void OiReset::greet() const {
  std::cout << reset_ << std::endl;
}
void OiReset::bye() const {;}


// =============================================================================
void OiDummy::greet() const {;}
void OiDummy::bye() const {;}


