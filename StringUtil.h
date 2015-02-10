#include <string.h>

///
/// Use for join two char arrays.
///
class StringUtil
{
	public:
		static char *Join(const char *string1, const char *string2);
		static char *Join(const char *string1, const char delimiter, const char *string2);
};