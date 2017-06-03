M561                         ; clear any existing bed transform
G30 P0 X30 Y20 Z-99999       ; define 4 points in a clockwise direction around the bed, starting near (0,0)
G30 P1 X30 Y145 Z-99999
G30 P2 X110 Y145 Z-99999
G30 P3 X110 Y20 Z-99999
G30 P4 X71 Y82.5 Z-99999 S0  ; finally probe bed centre, and calculate compensation
