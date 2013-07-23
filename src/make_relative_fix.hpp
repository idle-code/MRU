#include <boost/filesystem.hpp>
#include <boost/version.hpp>

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
        
        // Return path when appended to From will resolve to same as To
        boost::filesystem::path make_relative( boost::filesystem::path From, boost::filesystem::path To )
        {
                From = boost::filesystem::absolute( From ); To = boost::filesystem::absolute( To );
                boost::filesystem::path ret;
                boost::filesystem::path::const_iterator itrFrom( From.begin() ), itrTo( To.begin() );
                // Find common base
                for( boost::filesystem::path::const_iterator toEnd( To.end() ), fromEnd( From.end() ) ; itrFrom != fromEnd && itrTo != toEnd && *itrFrom == *itrTo; ++itrFrom, ++itrTo );
                // Navigate backwards in directory to reach previously found base
                for( boost::filesystem::path::const_iterator fromEnd( From.end() ); itrFrom != fromEnd; ++itrFrom )
                {
                        if( (*itrFrom) != "." )
                                ret /= "..";
                }
                // Now navigate down the directory branch
                ret.append( itrTo, To.end() );
                return ret;
        }
}
}

//namespace boost { namespace filesystem { using filesystem3::make_relative; } }

