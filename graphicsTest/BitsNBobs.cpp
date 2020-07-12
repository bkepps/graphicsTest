#include "MainHead.h"
/*ideal for getting path of a file, set orgin to SDL_GetBasePath(), and for toAppend give hard coded string*/
const char* BitsNBobs_append(char* orgin, const char* toAppend) {
	int orginSize = strlen(orgin);
	int toAppendSize = strlen(toAppend);
	char* dest = (char*)malloc(sizeof(char) * (orginSize + toAppendSize + 1));
	int i = 0;
	while (orgin[i] != '\0')
		dest[i] = orgin[i++];
	i = 0;
	while(toAppend[i] != '\0')
		dest[orginSize + i] = toAppend[i++];
	dest[orginSize + toAppendSize] = '\0';
	const char* out = dest;
	return out;
}