#define DEBUG_L 1
#include "debug_l.h"

unsigned short log_level = 0;
const short space_num = 2;

namespace debug_l {

std::ostringstream& soss(bool reset) {
  static std::ostringstream oss("");
  if(reset)
    oss.str("");
  return oss;
}

void binp(const void* data, int size) {
  if(size<1 || data==NULL) return;
  for(int bytes=size-1; bytes>=0; std::cout << " ", bytes--)
    for(int i=7; i>=0; i--)
      std::cout << (reinterpret_cast<const unsigned char*>(data)[bytes]&(1<<i) ? "1" : "0");
  std::cout << std::endl;
}

unsigned long from_bin(const char* bin_string) {
  unsigned long buf=0;
  int i=0, shift=0;
  while(bin_string[i+1]!='\0')
    i++;
  shift=(sizeof(unsigned long)*8)-1-i;
  for(; i>=0; i--)
    buf |= (bin_string[i]=='1' ? (1<<(((sizeof(unsigned long)*8)-1)-i)) : 0);
  return buf>>shift;
}

/* <recorder> */
recorder::recorder(uint _verbose_level, uint _record_options, uint _tab_level) : 
  present_level(0), verbose_level(_verbose_level), record_options(_record_options), tab_level(_tab_level) { 
  mklev(present_level);
}
recorder::recorder(const recorder& _r) {
  present_level = _r.present_level;
  verbose_level = _r.verbose_level;
  record_options = _r.record_options;
  tab_level = _r.tab_level;
  indent_length = _r.indent_length;
  pre = _r.pre;
}
recorder::~recorder() {
}
uint recorder::level(uint _new_level) {
  uint old_lev=present_level;
  present_level=_new_level;
  mklev(present_level);
  return old_lev;
}
uint recorder::level(void) {
  return present_level;
}

void recorder::inc_lev(void) { ++present_level; mklev(present_level); }
void recorder::dec_lev(void) { if(present_level != 0) --present_level; mklev(present_level); }

uint recorder::verbose(uint _new_level) {
  uint old_lev = verbose_level;
  verbose_level = _new_level;
  return old_lev;
}
uint recorder::verbose(void) {
  return verbose_level;
}

uint recorder::format(uint _new_options) {
  uint old_options = record_options;
  record_options = _new_options;
  return old_options;
}

const std::string& recorder::mklev() {
  return pre;
}
const std::string& recorder::mklev(uint _lev) {
  std::string tmp("");
  for(uint i=0; i< (_lev*tab_level); i++)
    tmp +=  ' ';
  pre = tmp;
  return pre;
}

void recorder::color_start(std::stringstream &recs, uint _level)
{
  if(true) {
    switch(_level) {
      case lInfo:
        recs << COLOR_INFO_START;
        break;
      case lWarning:
        recs << COLOR_WARNING_START;
        break;
      case lError:
        recs << COLOR_ERROR_START;
        break;
      case lFunction:
        recs << COLOR_FUNCTION_START; 
        break;
      case lData:
        recs << COLOR_DATA_START;
        break;
      default:
        recs << COLOR_UNKNOWN_START;
    }
  }
}

void recorder::color_end(std::stringstream &recs, uint _level)
{
  if(true) {
    switch(_level) {
      case lInfo:
        recs << COLOR_INFO_END;
        break;
      case lWarning:
        recs << COLOR_WARNING_END;
        break;
      case lError:
        recs << COLOR_ERROR_END;
        break;
      case lFunction:
        recs << COLOR_FUNCTION_END; 
        break;
      case lData:
        recs << COLOR_DATA_END;
        break;
      default:
        recs << COLOR_UNKNOWN_END;
    }
  }
}

std::string recorder::format(const char* _file, uint _line, uint _level, const std::string& _label, bool _eol) {
  std::stringstream recs;
  if(record_options != oNone) {
    if(!(verbose_level & _level))
      return std::string("");
    if(record_options & oFile) {
      recs << _file;
      if(record_options & oLine)
        recs << ':';
    }
    
    // if using colors:
    color_start(recs, _level);

    if(record_options & oLine) {
      recs << std::setfill('.') << std::setw(3) << _line;
      if(record_options & oLevel)
        recs << ':';
    }
    if(record_options & oLevel)
      if(verbose_level & _level)
        switch(_level) {
          case lInfo:
            recs << "**"; 
            break;
          case lWarning:
            recs << "WW"; 
            break;
          case lError:
            recs << "EE"; 
            break;
          case lFunction:
            recs << "FO";  
            break;
          case lData:
            recs << "DT"; 
            break;
          default:
            recs << "??"; 
        }
    recs <<  ": ";
  }
  color_end(recs, _level);
  
  indent_length = recs.str().length();
  if(record_options & oLev_indent)
    recs << mklev();
  
  color_start(recs, _level);
  recs << _label;
  color_end(recs, _level);
  if(_eol)
    recs << std::endl;
  return recs.str();
}

/* 
  </recorder> 
  <console_recorder> 
*/
console_recorder::console_recorder(uint _verbose_level, uint _record_options, uint _tab_level) : recorder(_verbose_level, _record_options, _tab_level) {
  present_level = 0;
  indent_length = 7;
}
console_recorder::console_recorder(const recorder& _r) : recorder(_r) {

}
console_recorder::~console_recorder() {

}

void console_recorder::record(const char* _file, uint _line, uint _level, const std::string& _label) {
  std::cout << format(_file, _line, _level, _label);
}

int console_recorder::set_file_info(const char* _filename, const char* _compile_date, const char* _compile_time, const std::string& _version, const std::string& _descr) {
  filename = _filename;
  compile_date = _compile_date;
  compile_time = _compile_time;
  version = _version;
  descr = _descr;
  
  std::cout << "Filename:\t" << filename << std::endl
    << "Compile date:\t" << compile_date << std::endl
    << "Compile time:\t" << compile_time << std::endl
    << "Version:\t" << version << std::endl
    << "Descryption:\t" << descr << std::endl << std::endl;
  return 0;
}

recorder* use_console_recorder() {
  static console_recorder rec;
  return &rec;
}

/* 
  </console_recorder> 
  <file_recorder> 
*/
file_recorder::file_recorder(const char* _filename, uint _verbose_level, uint _record_options, uint _tab_level) : recorder(_verbose_level, _record_options, _tab_level) {
  out.open(_filename, std::ios_base::out|std::ios_base::trunc);
  present_level = 0;
  indent_length = 7;
}
file_recorder::file_recorder(const recorder& _r) : recorder(_r) {

}
file_recorder::~file_recorder() {
  out.close();
}

void file_recorder::record(const char* _file, uint _line, uint _level, const std::string& _label) {
  out << format(_file, _line, _level, _label);
}

int file_recorder::set_file_info(const char* _filename, const char* _compile_date, const char* _compile_time, const std::string& _version, const std::string& _descr) {
  filename = _filename;
  compile_date = _compile_date;
  compile_time = _compile_time;
  version = _version;
  descr = _descr;
  
  out << "Filename:\t" << filename << std::endl
    << "Compile date:\t" << compile_date << std::endl
    << "Compile time:\t" << compile_time << std::endl
    << "Version:\t" << version << std::endl
    << "Descryption:\t" << descr << std::endl << std::endl;
  return 0;
}

recorder* use_file_recorder(const char* _file) {
  static file_recorder rec(_file);
  return &rec;
}

/* 
  </file_recorder> 
  <both_recorder> 
*/

/*
both_recorder::both_recorder(const char* _filename, uint _verbose_level, uint _record_options, uint _tab_level) : recorder(_verbose_level, _record_options, _tab_level) {
  out.open(_filename, std::ios_base::out|std::ios_base::trunc);
  
}
both_recorder::both_recorder(const recorder& _r) : recorder(_r) {

}
both_recorder::~both_recorder() {
  out.close();
}

void both_recorder::record(const char* _file, uint _line, uint _level, const std::string& _label) {
  std::string fout = format(_file, _line, _level, _label);
  if(fout!="")
    out << fout << std::endl;
}

int both_recorder::set_file_info(const char* _filename, const char* _compile_date, const char* _compile_time, const std::string& _version, const std::string& _descr) {
  filename = _filename;
  compile_date = _compile_date;
  compile_time = _compile_time;
  version = _version;
  descr = _descr;
  
  out << "Filename:\t" << filename << std::endl
    << "Compile date:\t" << compile_date << std::endl
    << "Compile time:\t" << compile_time << std::endl
    << "Version:\t" << version << std::endl
    << "Descryption:\t" << descr << std::endl << std::endl;
  return 0;
}

recorder* use_both_recorder(const char* _file) {
  static both_recorder rec(_file);
  return &rec;
}
//*/
/* 
  </both_recorder> 
  <guardian>
*/

guardian::guardian(uint& _ref_counter, const char* _file, uint _line, const std::string& _label) : 
  ref_counter(_ref_counter) {
  if(ref_counter==0) {
    file = _file;
    line = _line;
    debug_recorder->record(_file, _line, lFunction, _label + " {");
    debug_recorder->inc_lev();
  } else {
    std::ostringstream t;
    t << "Requrence call LEV#" << ref_counter;
    debug_recorder->dec_lev();
    debug_recorder->record(_file, _line, lFunction, t.str().c_str());
    debug_recorder->inc_lev();
  }
  ++ref_counter;
}
guardian::~guardian() {
  if(ref_counter==1) {
    debug_recorder->dec_lev();
    debug_recorder->record(file, line, lFunction, "}");
  }
  --ref_counter;
}
/* </guardian> */

recorder* debug_recorder = use_console_recorder();

} // namespace debug_l
