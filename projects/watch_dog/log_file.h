#ifndef __LOG_FILE_H__
#define __LOG_FILE_H__





/*Description: the function write an event to LOG.txt including detail, time stamp and pid.
@return: 0 if succeded.
@errors: openfile, write to file etc. return 1 if any error occurred.
*/
int WriteToLog(int event, int pid);


/*Description: This function read from config file the kind of data specified in data_to_fetch.
@return: return the data or NULL if data_to_fetch isn't found.
@errors: NULL if any error occurred.
*/
char *ReadFromConfigFile(char *data_to_fetch);



#endif /* __LOG_FILE_H__ */
