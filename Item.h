///
/// Represent created item (file or folder).
///
class Item
{
	public:
		char* _path;
		bool _isFile;
		Item(char *path, bool isFile);
};