/*
 * Ryan Symington
 * 11/28/16
*/

#ifndef __FILEHANDLING_H__
#define	__FILEHANDLING_H__

#include "avl.h"

Tree * readFiles(Tree *tree, char *folderName);

//mallocs
Tree * readFile(Tree *tree, char *filename);

#endif
