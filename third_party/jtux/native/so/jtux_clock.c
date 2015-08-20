/*
	Copyright 2003 by Marc J. Rochkind. All rights reserved.
	May be copied only for purposes and under conditions described
	on the Web page www.basepath.com/aup/copyright.htm.

	The Example Files are provided "as is," without any warranty;
	without even the implied warranty of merchantability or fitness
	for a particular purpose. The author and his publisher are not
	responsible for any damages, direct or incidental, resulting
	from the use or non-use of these Example Files.

	The Example Files may contain defects, and some contain deliberate
	coding mistakes that were included for educational reasons.
	You are responsible for determining if and how the Example Files
	are to be used.

*/

#include "defs.h"
#include "JtuxClock.h" // generated by javah
#include "jtux_util.h"
#include "JNI_macros.h"

JNIEXPORT jint JNICALL Java_jtux_UClock_alarm(JNIEnv *env, jclass obj,
  jint secs)
{
	return alarm(secs);
}

JNIEXPORT void JNICALL Java_jtux_UClock_nanosleep(JNIEnv *env, jclass obj,
  jobject nsecs, jobject remain)
{
	jclass cls_timespec = (*env)->FindClass(env, "jtux/UProcess$s_timespec");
	struct timespec nsecs_c, remain_buf, *remain_c = &remain_buf;
	int r;
	long sec;

	if (remain == NULL)
		remain_c = NULL;
	if (!field_jtoc_long(env, cls_timespec, "tv_sec", nsecs, &sec))
		return;
	nsecs_c.tv_sec = (time_t)sec;
	if (!field_jtoc_long(env, cls_timespec, "tv_nsec", nsecs, &nsecs_c.tv_nsec))
		return;
	r = nanosleep(&nsecs_c, remain_c);
	if (r != 0 && remain_c != NULL) {
		if (!field_ctoj_long(env, cls_timespec, "tv_sec", remain, remain_c->tv_sec))
			return;
		if (!field_ctoj_long(env, cls_timespec, "tv_nsec", remain, remain_c->tv_nsec))
			return;
	}
	if (r == -1)
		JTHROW_neg1(-1);
}

JNIEXPORT jint JNICALL Java_jtux_UClock_sleep(JNIEnv *env, jclass obj,
  jint secs)
{
	return sleep(secs);
}


JNIEXPORT void JNICALL Java_jtux_UClock_usleep(JNIEnv *env, jclass obj,
  jint usecs)
{
	JTHROW_neg1(usleep(usecs))
}
