ScaleCA
=======

ScaleCA - a cellular automata simulation intended to scale to many, many cores.

Design
------

Split into components:

 * Master - the process that starts simulation workers and brokers communication.
 * Engine - individual simulation engines.
 * Displays - clients that provide displays of a running simulation.