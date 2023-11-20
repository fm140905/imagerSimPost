Imager using as reference the CsI crystal 
c CELL CARDS
  c row 1
  30 2 -7.25  -30  IMP:P=1
  32 like 30 but TRCL=2
  34 like 30 but TRCL=3
  36 like 30 but TRCL=4
  38 like 30 but TRCL=5
  40 like 30 but TRCL=6
  42 like 30 but TRCL=7
  c row 2
  70 like 30 but TRCL=8
  72 like 30 but TRCL=9
  74 like 30 but TRCL=10
  76 like 30 but TRCL=11
  78 like 30 but TRCL=12
  80 like 30 but TRCL=13
  82 like 30 but TRCL=14
  c row 3
  200 like 30 but TRCL=15
  202 like 30 but TRCL=16
  204 like 30 but TRCL=17
  206 like 30 but TRCL=18
  208 like 30 but TRCL=19
  210 like 30 but TRCL=20
  212 like 30 but TRCL=21
  c row 4
  400 like 30 but TRCL=22
  402 like 30 but TRCL=23
  404 like 30 but TRCL=24
  406 like 30 but TRCL=25
  408 like 30 but TRCL=26
  410 like 30 but TRCL=27
  412 like 30 but TRCL=28
  c air
  990  0   -10  #30 #32 #34 #36 #38 #40 #42 #70 #72 #74 #76 #78 #80 #82
                #200 #202 #204 #206 #208 #210 #212 
                #400 #402 #404 #406 #408 #410 #412 IMP:P=1
  999  0   10 IMP:P=0
c END CELL CARDS - BLANK LINE FOLLOWS

c SURFACE CARDS
  10  SO  350
  c 3 mm x 3mm x 5cm
  30  RPP -2.1 -1.8 -3.45 -3.15 -2.5 2.5
c END SURFACE CARDS - BLANK LIKE FOLLOWS

c DATA CARDS
c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
c Translations
c ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
c row 1
TR2 0 1.1 0 1 0 0 0 1 0 0 0 1
TR3 0 2.2 0 1 0 0 0 1 0 0 0 1
TR4 0 3.3 0 1 0 0 0 1 0 0 0 1
TR5 0 4.4 0 1 0 0 0 1 0 0 0 1
TR6 0 5.5 0 1 0 0 0 1 0 0 0 1
TR7 0 6.6 0 1 0 0 0 1 0 0 0 1
c row 2
TR8  1.3 0.0 0 1 0 0 0 1 0 0 0 1
TR9  1.3 1.1 0 1 0 0 0 1 0 0 0 1
TR10 1.3 2.2 0 1 0 0 0 1 0 0 0 1
TR11 1.3 3.3 0 1 0 0 0 1 0 0 0 1
TR12 1.3 4.4 0 1 0 0 0 1 0 0 0 1
TR13 1.3 5.5 0 1 0 0 0 1 0 0 0 1
TR14 1.3 6.6 0 1 0 0 0 1 0 0 0 1
c row 3
TR15 2.6 0.0 0 1 0 0 0 1 0 0 0 1
TR16 2.6 1.1 0 1 0 0 0 1 0 0 0 1
TR17 2.6 2.2 0 1 0 0 0 1 0 0 0 1
TR18 2.6 3.3 0 1 0 0 0 1 0 0 0 1
TR19 2.6 4.4 0 1 0 0 0 1 0 0 0 1
TR20 2.6 5.5 0 1 0 0 0 1 0 0 0 1
TR21 2.6 6.6 0 1 0 0 0 1 0 0 0 1
c row 4
TR22 3.9 0.0 0 1 0 0 0 1 0 0 0 1
TR23 3.9 1.1 0 1 0 0 0 1 0 0 0 1
TR24 3.9 2.2 0 1 0 0 0 1 0 0 0 1
TR25 3.9 3.3 0 1 0 0 0 1 0 0 0 1
TR26 3.9 4.4 0 1 0 0 0 1 0 0 0 1
TR27 3.9 5.5 0 1 0 0 0 1 0 0 0 1
TR28 3.9 6.6 0 1 0 0 0 1 0 0 0 1
  MODE  P
  FILES 21 DUMN1
  PRINT 
  DBCN
  PRDMP 4J -1
  NPS 5E7
   c  CUT:P J 0.01
c POLIMI CARDS
  IPOL  0 1 0 0 J 1 28 30 32 34 36 38 40 42 70 72 74 76 78 80 82
        200 202 204 206 208 210 212 400 402 404 406 408 410 412
c 11 AmBe, 1 Cf-252, 13 AmLi
c GEOMETRIC TRANSLATIONS
c SOURCE SPECIFICATION
c   SDEF X=10  Y=d1 Z=d2 PAR=P ERG=0.661 VEC=1 0 0 DIR=-1 TME = d3
c   SI1 -3.5 3.5
c   SP1 0 1
c   SI2 -2.5 2.5
c   SP2 0 1
c   SI3 0 5E10
c   SP3 0 1
   SDEF POS=13.65 0 0 PAR=P ERG=d1 TME=d2
   SI1 L 0.511  1.27
   SP1 D 1.79  1.00
   SI2 0 5E10
   SP2 0 1
c MATERIAL SPECIFICATION
c NaI
  M1  11023.80c -0.15
      53127.80c -0.85
c CsI rho=5.41 g/cm3
c  M2  NLIB=80c PLIB=04p
c      53127  -0.48845
c      55133  -0.51154
c LYSO rho= 7.25 g/cm3
  M2  NLIB=80c PLIB=04p
      8016   -0.175325
      8017   -0.000071
      8018   -0.000405
      14000  -0.06172
      39089  -0.019538
      71175  -0.711469
      71176   -0.019093
      58136   -0.000022
      58138   -0.000031
      58140   -0.010932
      58142   -0.001393
c lead
  M10  NLIB=80c PLIB=04p
       92234  -.001256543
       92235  -.170010846
       92236  -.001668232
       92238  -.672594261
       8016   -.154470118
c TALLY SPECIFICATION 
c  E0     0.021 300i 2
c  F11:N  20.3 
c  F8:P  200
 c FT8 GEB 0.0005 0.007 1
c MPLOT  TALLY=8 LINLOG $ COPLOT TALLY=11
c END OF FILE
