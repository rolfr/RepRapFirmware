M561                         ; clear any existing bed transform
G30 P0 X10 Y10 Z-99999       ; define 4 points in a clockwise direction around the bed, starting near (0,0)
G30 P1 X10 Y190 Z-99999
G30 P2 X190 Y190 Z-99999
G30 P3 X190 Y10 Z-99999
G30 P4 X100 Y100 Z-99999 S0  ; finally probe bed centre, and calculate compensation
G1 X0 Y0 F5000               ; move the head to the corner (optional)