/*
 * The average procedure receives an array of real
 * numbers and returns the average of their
 * values. This toy service handles a maximum of
 * 200 numbers.
 * http://www.linuxjournal.com/article/2204?page=0,1
 */

const MAXAVGSIZE  = 2000;

struct input_data {
  char text[MAXAVGSIZE];
};

struct echoed_input_data {
  char text[MAXAVGSIZE];
};

typedef struct input_data input_data;

program AVERAGEPROG {
    version AVERAGEVERS {
        echoed_input_data ECHO(input_data) = 1;
    } = 1;
} = 8276;
