#include <Arduino.h>
#define FLOAT_PRECISION 6
static String PACKAGE;
static float sim_altitude;

void uart_init(long);
void set_package(void);
void make_package(String, int, int, double, double);
void post_package(void);