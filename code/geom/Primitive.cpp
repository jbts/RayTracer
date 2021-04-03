#include "geom/Primitive.h"

unsigned long Primitive::curr_id_ = 0;

Primitive::Primitive() {
  id_ = curr_id_;
  ++curr_id_;
}
