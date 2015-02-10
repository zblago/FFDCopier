# FFDCopier - File & Folder Copier
After a long time, I decided to go back the roots and make a simple C++ application. First, I read the tutorial on http://www.cplusplus.com/doc/tutorial/, and then started to make FFDcopier (File Folder by Date Copier).

Application can run in two ways from the command line program:
1. name of the application, followed by two parameters - source folder and destination folder, OR
2. writing parameters in the conf.txt file. Conf.txt file consisst of two lines. Each one ends with \n, so hit the ENTER after each line.

FFDCopier makes in destination folder new folder in following format DD-MM-YY (day - month - year). If there is already the same folder, add on the same format HH-MM (hours - minutes).

If something goes wrong, application trigerrs rollback - all the previously copied files and folders are deleted. The code is separeted in cpps and header files.
