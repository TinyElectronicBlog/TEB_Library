#include "TEB_Library.h"

void setup () {
#ifdef TEB_DB_DEBUG
  teb.test("WiFi", "WiFi password", 25000); //Enter the parameters of your WiFi connection.
#endif
}

void loop () {
}
