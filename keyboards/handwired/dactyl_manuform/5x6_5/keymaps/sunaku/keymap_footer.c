#include "features/select_word.h"

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  if (!process_select_word(keycode, record, SELWORD)) { return false; }
  // Your macros ...

  return true;
}
