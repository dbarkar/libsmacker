/*
	libsmacker - A C library for decoding .smk Smacker Video files
	Copyright (C) 2012-2013 Greg Kennedy

	See smacker.h for more information.

	smk_malloc.h
		"Safe" implementations of malloc and free.
*/

#ifndef SMK_MALLOC_H
#define SMK_MALLOC_H

#include <stdlib.h>
/* fprintf */
#include <stdio.h>

/* Error messages from calloc */
#include <errno.h>
#include <string.h>

/* "safe" null check:
	branches to an error block if pointer is null */
#define smk_null_check(p) \
{ \
	if (!p) \
	{ \
		fprintf(stderr, "libsmacker::smk_null_check(" #p "): ERROR: NULL POINTER at line %lu, file %s\n", (unsigned long)__LINE__, __FILE__); \
		goto error; \
	} \
}

/* Safe free: attempts to prevent double-free by setting pointer to NULL.
	Optionally warns on attempts to free a NULL pointer. */
#define smk_free(p) \
{ \
	if (p) \
	{ \
		free(p); \
		p = NULL; \
	} \
/*	else \
	{ \
		fprintf(stderr, "libsmacker::smk_free(" #p ") - Warning: attempt to free NULL pointer (file: %s, line: %lu)\n", __FILE__, (unsigned long)__LINE__); \
	} */ \
}

/*
	Safe malloc: exits if calloc() returns NULL.
		Also initializes blocks to 0.
	Ideally, one should not exit() in a library. However, if you cannot
		calloc(), you probably have bigger problems.
*/
#define smk_malloc(p, x) \
{ \
	if (p) \
	{ \
		fprintf(stderr, "libsmacker::smk_malloc(" #p ",%lu) - Warning: freeing non-NULL pointer before calloc (file: %s, line: %lu)\n", (unsigned long) x, __FILE__, (unsigned long)__LINE__); \
		smk_free(p); \
	} \
	p = calloc(1, x); \
	if (!p) \
	{ \
		fprintf(stderr, "libsmacker::smk_malloc(" #p ",%lu) - ERROR: calloc() returned NULL (file: %s, line: %lu)\n\tError [%d]: %s\n", (unsigned long) x, __FILE__, (unsigned long)__LINE__, errno, strerror(errno)); \
		exit(EXIT_FAILURE); \
	} \
}

#endif
