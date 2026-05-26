enum Result { OK, ERROR };
enum CompResult { DIFFERENT, EQUAL };

enum CompResult eCompareString(char cStr1[], char cStr2[]);
enum Result eHexStringToUInt(char cStr[], unsigned int *puiValue);
void ReplaceCharactersInString(char cString[], char OldChar, char NewChar);
