#include <boost/filesystem.hpp>
#include <boost/version.hpp>

//*
namespace boost {
namespace filesystem {
        using boost::filesystem::path;
        template < >
        path& path::append< typename path::iterator >( typename path::iterator begin, typename path::iterator end, const codecvt_type& cvt)
        { 
                for( ; begin != end ; ++begin )
                        *this /= *begin;
                return *this;
        }
        
        // TODO: inline 
        boost::filesystem::path make_relative( boost::filesystem::path From, boost::filesystem::path To )
        {
                return boost::filesystem::relative(To, From);
        }
}
}
//*/

//namespace boost { namespace filesystem { using filesystem3::make_relative; } }

