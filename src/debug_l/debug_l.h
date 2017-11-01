#ifndef DEBUG_L_HEADER
#define DEBUG_L_HEADER
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

typedef unsigned int uint;

/**
  * TODO:
  * Dodac poziomy debugu
  */

#define COLOR_INFO_START      "\e[1;37m"
#define COLOR_WARNING_START   "\e[1;33m"
#define COLOR_ERROR_START     "\e[1;31m"
#define COLOR_FUNCTION_START  "\e[0m"
//#define COLOR_FUNCTION_START  "\e[1;30m"
#define COLOR_DATA_START      "\e[0;36m"
#define COLOR_UNKNOWN_START   "\e[0m"

#define COLOR_INFO_END        "\e[0m"
#define COLOR_WARNING_END     "\e[0m" 
#define COLOR_ERROR_END       "\e[0m" 
#define COLOR_FUNCTION_END    "\e[0m" 
#define COLOR_DATA_END        "\e[0m" 
#define COLOR_UNKNOWN_END     "\e[0m" 

#ifdef DEBUG_L
  
  #define LEV_UP debug_l::debug_recorder->inc_lev();
  #define LEV_DOWN debug_l::debug_recorder->dec_lev();
  //#define MKLEV debug_l::debug_recorder->mklev()
  #define MKLEV debug_l::debug_recorder->format(__FILE__, __LINE__, debug_l::lData, "", false)
  
  #define FO(X) static uint __local_guardian_ref_counter = 0; \
    debug_l::guardian __local_guardian(__local_guardian_ref_counter, __FILE__, __LINE__, (debug_l::soss(true) << X, debug_l::soss().str()));
    
  //#define FILE_INFO(VER,DESC) static int __file_info_dummy_var = debug_l::debug_recorder->set_file_info(__FILE__, __DATE__, __TIME__, VER, DESC);
  
  #define DEBUG_L_FILTER(X) debug_l::debug_recorder->verbose(X);
  #define DEBUG_L_OUTPUT_FORMAT(X) debug_l::debug_recorder->format(X);
  #define DEBUG_L_RECORD_TO_CONSOLE() debug_l::debug_recorder = debug_l::use_console_recorder();
  #define DEBUG_L_RECORD_TO_FILE(FILE) debug_l::debug_recorder = debug_l::use_file_recorder(FILE);
  #define DEBUG_L_USE_RECORDER(RECORDER) debug_l::debug_recorder = RECORDER;
  #define DEBUG_L_ACTIVE_RECORDER debug_l::debug_recorder
  #define DEBUG_L_RECORDER_TYPE debug_l::recorder
  
  #define MSG(X) debug_l::debug_recorder->record(__FILE__, __LINE__, debug_l::lInfo, (debug_l::soss(true) << X, debug_l::soss().str()));
  #define WARN(X) debug_l::debug_recorder->record(__FILE__, __LINE__, debug_l::lWarning, (debug_l::soss(true) << X, debug_l::soss().str()));
  #define ERR(X) debug_l::debug_recorder->record(__FILE__, __LINE__, debug_l::lError, (debug_l::soss(true) << X, debug_l::soss().str()));
  #define DATA(X) debug_l::debug_recorder->record(__FILE__, __LINE__, debug_l::lData, (debug_l::soss(true) << (X), debug_l::soss().str()));
  #define VAL(X) debug_l::debug_recorder->record(__FILE__, __LINE__, debug_l::lData, (debug_l::soss(true) << #X " = " << (X), debug_l::soss().str()));
  
  #define O(X) { FO("\""#X"\""); X; }
  
#else // !DEBUG_L
  
  #define LEV_UP ;
  #define LEV_DOWN ;
  #define MKLEV ""
  
  #define FO(X) ;
  #define SFO(X) ;
  
  #define DEBUG_L_FILTER(X) ;
  #define DEBUG_L_OUTPUT_FILTER(X) ;
  #define DEBUG_L_RECORD_TO_CONSOLE() ;
  #define DEBUG_L_RECORD_TO_FILE(FILE) ;
  #define DEBUG_L_OUTPUT_FORMAT(X) ;
  #define DEBUG_L_USE_RECORDER(RECORDER) ;
  #define DEBUG_L_ACTIVE_RECORDER debug_l::debug_recorder
  #define DEBUG_L_RECORDER_TYPE debug_l::recorder
  
  #define MSG(X) ;
  #define WARN(X) ;
  #define ERR(X) ;
  #define DATA(X) ;
  #define VAL(X) ;
  
  #define O(X) {  X; }
  
#endif // DEBUG_L

namespace debug_l {

std::ostringstream& soss(bool reset=false);

void binp(const void* data, int size);
unsigned long from_bin(const char* bin_string);

template<typename TYP> void binp(const TYP* data) {
	if(data==NULL) return;
	int size = sizeof(TYP);
	for(int bytes=size-1; bytes>=0; std::cout << " ", bytes--)
		for(int i=7; i>=0; i--)
			std::cout << (reinterpret_cast<const unsigned char*>(data)[bytes]&(1<<i) ? "1" : "0");
	std::cout << std::endl;
}

template<typename TYP> void binp(const TYP& data) {
	int size = sizeof(TYP);
	for(int bytes=size-1; bytes>=0; std::cout << " ", bytes--)
		for(int i=7; i>=0; i--)
			std::cout << (reinterpret_cast<const unsigned char*>(&data)[bytes]&(1<<i) ? "1" : "0");
	//std::cout << std::endl;
}

enum logType { lInfo=1, lWarning=2, lError=4, lFunction=8, lData=16, lAll=lInfo|lWarning|lError|lFunction|lData };

enum recordOptions { oNone=0, oFile=1, oLine=2, oLevel=4, oLev_indent=8, oTimestamp=16, oSimple=oLine|oLev_indent, 
  oAll=oFile|oLine|oLevel|oLev_indent|oTimestamp };

class recorder {
  protected:
    typedef unsigned int uint;
    uint 
      present_level, //aktualny poziom w drzewie debugu
      verbose_level, //stopien wiadomosci
      record_options, //opcje zapisu
      tab_level, //ilosc spacji na poziom wciecia
      indent_length; //dlugosc informacji poprzedzajacych wiadomosc(nazwapliku,linia,itp)
    std::string 
      pre,
      filename, 
      compile_date, 
      compile_time, 
      version, 
      descr;
    //virtual void record(const std::string& _label) = 0;
    
    recorder(const recorder& _r);
    void color_start(std::stringstream &recs, uint _level);
    void color_end(std::stringstream &recs, uint _level);
  public:
    virtual int set_file_info(const char* _filename, const char* _compile_date, const char* _compile_time, const std::string& _version, const std::string& _descr) = 0;
    recorder(uint _verbose_level=lAll, uint _record_options=oLine|oLev_indent, uint _tab_level=2);
    virtual ~recorder();
    std::string format(const char* _file, uint _line, uint _level, const std::string& _label, bool _eol=true);
    virtual void record(const char* _file, uint _line, uint _level, const std::string& _label) = 0;
    void inc_lev(void);
    void dec_lev(void);
    uint level(uint _new_level);
    uint level(void);
    uint verbose(uint _level);
    uint verbose();
    uint format(uint _new_options);
    const std::string& mklev();
    const std::string& mklev(uint _lev);
};

extern recorder* debug_recorder;

class console_recorder : public recorder {
  public:
    console_recorder(const recorder& _r);
    console_recorder(uint _verbose_level=lAll, uint _record_options=oLine|oLev_indent, uint _tab_level=2);
    ~console_recorder();
    void record(const char* _file, uint _line, uint _level, const std::string& _label);
    int set_file_info(const char* _filename, const char* _compile_date, const char* _compile_time, const std::string& _version, const std::string& _descr);
};
recorder* use_console_recorder();

class file_recorder : public recorder {
  std::ofstream out;
  public:
    file_recorder(const recorder& _r);
    file_recorder(const char* _filename, uint _verbose_level=lAll, uint _record_options=oLine|oLev_indent, uint _tab_level=2);
    ~file_recorder();
    void record(const char* _file, uint _line, uint _level, const std::string& _label);
    int set_file_info(const char* _filename, const char* _compile_date, const char* _compile_time, const std::string& _version, const std::string& _descr);
};
recorder* use_file_recorder(const char* _file="program.log");

/* // TO DO:
class both_recorder : protected console_recorder, protected file_recorder {
  public:
    both_recorder(const recorder& _r);
    both_recorder(const char* _filename, uint _verbose_level=lAll, uint _record_options=oLine|oLev_indent, uint _tab_level=2);
    ~both_recorder();
    void record(const char* _file, uint _line, uint _level, const std::string& _label);
    int set_file_info(const char* _filename, const char* _compile_date, const char* _compile_time, const std::string& _version, const std::string& _descr);
};
recorder* use_both_recorder(const char* _file="program.log");
//*/
class guardian {
  private:
    const char* file;
    uint line;
    uint& ref_counter;
    guardian(const guardian&);
  public:
    guardian(uint& _ref_counter, const char* _file, uint _line, const std::string& _label="");
    ~guardian();
};

} // namespace debug_l

#endif // DEBUG_L_HEADER
