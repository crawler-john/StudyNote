#ifndef __TIMEMATH_H__
#define __TIMEMATH_H__
/*****************************************************************************/
/*                                                                           */
/*    Copyright (C) - LEGATE Intelligent Equipment - All rights reserved     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  Except if expressly provided in a dedicated License Agreement, you are   */
/*  not authorized to:                                                       */
/*                                                                           */
/*  1. Use, copy, modify or transfer this software component, module or      */
/*  product, including any accompanying electronic or paper documentation    */
/*  (together, the "Software").                                              */
/*                                                                           */
/*  2. Remove any product identification, copyright, proprietary notices or  */
/*  labels from the Software.                                                */
/*                                                                           */
/*  3. Modify, reverse engineer, decompile, disassemble or otherwise attempt */
/*  to reconstruct or discover the source code, or any parts of it, from the */
/*  binaries of the Software.                                                */
/*                                                                           */
/*  4. Create derivative works based on the Software (e.g. incorporating the */
/*  Software in another software or commercial product or service without a  */
/*  proper license).                                                         */
/*                                                                           */
/*  By installing or using the "Software", you confirm your acceptance of the*/
/*  hereabove terms and conditions.                                          */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*  History:                                                                 */
/*****************************************************************************/
/*  Date       * Author          * Changes                                   */
/*****************************************************************************/
/*  2012-12-13 * Ricky Gong      * Creation of the file                      */
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/
#include <time.h>


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#if defined(__linux)
// Parameters used to convert the timespec values:
#ifndef MSEC_PER_SEC
#define MSEC_PER_SEC	1000L
#endif
#ifndef USEC_PER_MSEC
#define USEC_PER_MSEC	1000L
#endif
#ifndef NSEC_PER_USEC
#define NSEC_PER_USEC	1000L
#endif
#ifndef NSEC_PER_MSEC
#define NSEC_PER_MSEC	1000000L
#endif
#ifndef USEC_PER_SEC
#define USEC_PER_SEC	1000000L
#endif
#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC	1000000000L
#endif
#ifndef FSEC_PER_SEC
#define FSEC_PER_SEC	1000000000000000L
#endif
#endif


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
#if defined(__linux)

#if defined (__cplusplus)
extern "C"
{
#endif

#ifndef sec_nsec_to_timespec
extern inline struct timespec sec_nsec_to_timespec(time_t sec, long nsec)
{
    timespec res;
    res.tv_sec = sec;
    res.tv_nsec = nsec;
    return res;
}
#endif

#ifndef timespec_to_timespec
extern inline struct timespec timespec_to_timespec(struct timespec a)
{
    timespec res;
    res.tv_sec = a.tv_sec;
    res.tv_nsec = a.tv_nsec;
    return res;
}
#endif

#ifndef timespec_to_timespec
extern inline struct timespec timespec_min(struct timespec a, struct timespec b)
{
    if((a.tv_sec > b.tv_sec) || ((a.tv_sec == b.tv_sec) && (a.tv_nsec > b.tv_nsec)))
    {
        return b;
    }
    else
    {
        return a;
    }
}
#endif

#ifndef timespec_compare
extern inline int timespec_compare(const struct timespec *lhs, const struct timespec *rhs)
{
	if (lhs->tv_sec < rhs->tv_sec)
		return -1;
	if (lhs->tv_sec > rhs->tv_sec)
		return 1;
	return lhs->tv_nsec - rhs->tv_nsec;
}
#endif

#ifndef set_normalized_timespec
extern inline void set_normalized_timespec(struct timespec *ts, time_t sec, long nsec)
{
	while (nsec >= NSEC_PER_SEC) {
		nsec -= NSEC_PER_SEC;
		++sec;
	}
	while (nsec < 0) {
		nsec += NSEC_PER_SEC;
		--sec;
	}
	ts->tv_sec = sec;
	ts->tv_nsec = nsec;
}
#endif

#ifndef timespec_add_sec_nsec
extern inline struct timespec timespec_add_sec_nsec(struct timespec lhs, time_t sec, long nsec)
{
	struct timespec ts_delta;
	set_normalized_timespec(&ts_delta, lhs.tv_sec + sec,
				lhs.tv_nsec + nsec);
	return ts_delta;
}
#endif

#ifndef timespec_add
extern inline struct timespec timespec_add(struct timespec lhs, struct timespec rhs)
{
	struct timespec ts_delta;
	set_normalized_timespec(&ts_delta, lhs.tv_sec + rhs.tv_sec,
				lhs.tv_nsec + rhs.tv_nsec);
	return ts_delta;
}
#endif

#ifndef timespec_sub
extern inline struct timespec timespec_sub(struct timespec lhs, struct timespec rhs)
{
	struct timespec ts_delta;
	set_normalized_timespec(&ts_delta, lhs.tv_sec - rhs.tv_sec,
				lhs.tv_nsec - rhs.tv_nsec);
	return ts_delta;
}
#endif

#if defined (__cplusplus)
} // end of extern "C"
#endif

#endif // end of #if defined(__linux)

#endif //__TIMEMATH_H__

