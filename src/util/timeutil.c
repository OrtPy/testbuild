#include "ef2/timeutil.h"

#include <errno.h>

int ef2_clock_gettime_monotonic32(ef2_timespec32* out)
{
  if (!out) return EINVAL;
  struct timespec ts;
  int rc = ef2_clock_gettime_monotonic(&ts);
  if (rc != 0) {
    out->tv_sec = 0;
    out->tv_nsec = 0;
    return rc;
  }
  out->tv_sec = (int32_t)ts.tv_sec;
  out->tv_nsec = (int32_t)ts.tv_nsec;
  return 0;
}

double timesince(const ef2_timespec32* start, int unused)
{
  (void)unused;
  if (!start) return 0.0;

  ef2_timespec32 now;
  (void)ef2_clock_gettime_monotonic32(&now);

  int32_t dsec = now.tv_sec - start->tv_sec;
  int32_t dnsec = now.tv_nsec - start->tv_nsec;
  return (double)dsec + (double)dnsec / 1000000000.0;
}
