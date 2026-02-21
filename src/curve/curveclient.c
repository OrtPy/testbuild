#include "ef2/curve.h"
#include <string.h>

void ef2_CurveClient_init(CurveClient* self)
{
  if (!self) return;
  memset(self, 0, sizeof(*self));
}
