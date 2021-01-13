EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5FF3751F
P 5400 2650
F 0 "J2" H 5480 2642 50  0000 L CNN
F 1 "Screw_Terminal_01x02" H 5480 2551 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 5400 2650 50  0001 C CNN
F 3 "~" H 5400 2650 50  0001 C CNN
	1    5400 2650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack J1
U 1 1 5FF37F96
P 3800 4350
F 0 "J1" H 3857 4675 50  0000 C CNN
F 1 "Barrel_Jack" H 3857 4584 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 3850 4310 50  0001 C CNN
F 3 "~" H 3850 4310 50  0001 C CNN
	1    3800 4350
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR05
U 1 1 5FF3889B
P 5200 2500
F 0 "#PWR05" H 5200 2350 50  0001 C CNN
F 1 "VDD" H 5215 2673 50  0000 C CNN
F 2 "" H 5200 2500 50  0001 C CNN
F 3 "" H 5200 2500 50  0001 C CNN
	1    5200 2500
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR03
U 1 1 5FF38E28
P 4100 4100
F 0 "#PWR03" H 4100 3950 50  0001 C CNN
F 1 "VDD" H 4115 4273 50  0000 C CNN
F 2 "" H 4100 4100 50  0001 C CNN
F 3 "" H 4100 4100 50  0001 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4100 4100 4250
$Comp
L power:GND #PWR04
U 1 1 5FF390DB
P 4100 4600
F 0 "#PWR04" H 4100 4350 50  0001 C CNN
F 1 "GND" H 4105 4427 50  0000 C CNN
F 2 "" H 4100 4600 50  0001 C CNN
F 3 "" H 4100 4600 50  0001 C CNN
	1    4100 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4600 4100 4450
$Comp
L Device:R_US R2
U 1 1 5FF397B3
P 5200 3450
F 0 "R2" H 5268 3496 50  0000 L CNN
F 1 "200m" H 5268 3405 50  0000 L CNN
F 2 "my_library_foot:TO-220_resistor" V 5240 3440 50  0001 C CNN
F 3 "~" H 5200 3450 50  0001 C CNN
	1    5200 3450
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5FF3DC63
P 5200 4500
F 0 "#PWR06" H 5200 4250 50  0001 C CNN
F 1 "GND" H 5205 4327 50  0000 C CNN
F 2 "" H 5200 4500 50  0001 C CNN
F 3 "" H 5200 4500 50  0001 C CNN
	1    5200 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 3850 5200 3800
Wire Wire Line
	5200 2500 5200 2650
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5FF3EADF
P 8900 3500
F 0 "A1" H 8900 2411 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 8450 2550 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 8900 3500 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 8900 3500 50  0001 C CNN
	1    8900 3500
	1    0    0    -1  
$EndComp
Text Label 8050 3400 0    50   ~ 0
VDRIVE
Wire Wire Line
	9100 2500 9100 2250
$Comp
L power:VDD #PWR014
U 1 1 5FF49832
P 9100 2250
F 0 "#PWR014" H 9100 2100 50  0001 C CNN
F 1 "VDD" H 9115 2423 50  0000 C CNN
F 2 "" H 9100 2250 50  0001 C CNN
F 3 "" H 9100 2250 50  0001 C CNN
	1    9100 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5FF4A077
P 9050 4750
F 0 "#PWR013" H 9050 4500 50  0001 C CNN
F 1 "GND" H 9055 4577 50  0000 C CNN
F 2 "" H 9050 4750 50  0001 C CNN
F 3 "" H 9050 4750 50  0001 C CNN
	1    9050 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5FF4ABC9
P 8850 4750
F 0 "#PWR012" H 8850 4500 50  0001 C CNN
F 1 "GND" H 8855 4577 50  0000 C CNN
F 2 "" H 8850 4750 50  0001 C CNN
F 3 "" H 8850 4750 50  0001 C CNN
	1    8850 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 4750 8850 4500
Wire Wire Line
	8850 4500 8900 4500
Wire Wire Line
	9000 4500 9000 4750
Wire Wire Line
	9000 4750 9050 4750
Wire Wire Line
	7750 3400 7800 3400
Text Label 9500 3900 0    50   ~ 0
SDA
Text Label 9500 4000 0    50   ~ 0
SCL
$Comp
L LTC4724:LTC-4724JR LED1
U 1 1 5FF54690
P 1300 2000
F 0 "LED1" H 2100 2293 60  0000 C CNN
F 1 "LTC-4724JR" H 2100 2187 60  0000 C CNN
F 2 "LTC4724:LTC-4724JR" H 2100 2140 60  0001 C CNN
F 3 "" H 1300 2000 60  0000 C CNN
	1    1300 2000
	1    0    0    -1  
$EndComp
$Comp
L LTC4724:LTC-4724JR LED2
U 1 1 5FF73F6C
P 1350 5100
F 0 "LED2" H 2150 5393 60  0000 C CNN
F 1 "LTC-4724JR" H 2150 5287 60  0000 C CNN
F 2 "LTC4724:LTC-4724JR" H 2150 5240 60  0001 C CNN
F 3 "" H 1350 5100 60  0000 C CNN
	1    1350 5100
	1    0    0    -1  
$EndComp
$Comp
L Driver_LED:MAX7219 U1
U 1 1 5FF8E408
P 3850 1950
F 0 "U1" H 3500 3100 50  0000 C CNN
F 1 "MAX7219" H 3650 3000 50  0000 C CNN
F 2 "Package_SO:SOIC-24W_7.5x15.4mm_P1.27mm" H 3800 2000 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX7219-MAX7221.pdf" H 3900 1800 50  0001 C CNN
	1    3850 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1150 4650 1150
Text Label 4350 1150 0    50   ~ 0
SEGA
Wire Wire Line
	4250 1250 4650 1250
Wire Wire Line
	4250 1350 4650 1350
Wire Wire Line
	4250 1450 4650 1450
Wire Wire Line
	4250 1550 4650 1550
Wire Wire Line
	4250 1650 4650 1650
Wire Wire Line
	4250 1750 4650 1750
Wire Wire Line
	4250 1850 4650 1850
Wire Wire Line
	4250 1950 4650 1950
Wire Wire Line
	4250 2050 4650 2050
Wire Wire Line
	4250 2150 4650 2150
Wire Wire Line
	4250 2250 4650 2250
Wire Wire Line
	4250 2350 4650 2350
Text Label 4350 1250 0    50   ~ 0
SEGB
Text Label 4350 1350 0    50   ~ 0
SEGC
Text Label 4350 1450 0    50   ~ 0
SEGD
Text Label 4350 1550 0    50   ~ 0
SEGE
Text Label 4350 1650 0    50   ~ 0
SEGF
Text Label 4350 1750 0    50   ~ 0
SEGG
Text Label 4350 1850 0    50   ~ 0
SEGDP
Text Label 4350 1950 0    50   ~ 0
DIG0
Text Label 4350 2050 0    50   ~ 0
DIG1
Text Label 4350 2150 0    50   ~ 0
DIG2
Text Label 4350 2250 0    50   ~ 0
DIG3
Text Label 4350 2350 0    50   ~ 0
DIG4
Wire Wire Line
	4250 2450 4650 2450
Text Label 4350 2450 0    50   ~ 0
DIG5
Wire Wire Line
	1350 5100 950  5100
Text Label 1250 5100 2    50   ~ 0
SEGA
Wire Wire Line
	1350 5200 950  5200
Wire Wire Line
	1350 5300 950  5300
Wire Wire Line
	1350 5400 950  5400
Wire Wire Line
	1350 5500 950  5500
Wire Wire Line
	1350 5600 950  5600
Wire Wire Line
	1350 5700 950  5700
Wire Wire Line
	1350 5800 950  5800
Text Label 1250 5200 2    50   ~ 0
SEGB
Text Label 1250 5300 2    50   ~ 0
SEGC
Text Label 1250 5400 2    50   ~ 0
SEGD
Text Label 1250 5500 2    50   ~ 0
SEGE
Text Label 1250 5600 2    50   ~ 0
SEGF
Text Label 1250 5700 2    50   ~ 0
SEGG
Text Label 1250 5800 2    50   ~ 0
SEGDP
Wire Wire Line
	1300 2000 900  2000
Text Label 1200 2000 2    50   ~ 0
SEGA
Wire Wire Line
	1300 2100 900  2100
Wire Wire Line
	1300 2200 900  2200
Wire Wire Line
	1300 2300 900  2300
Wire Wire Line
	1300 2400 900  2400
Wire Wire Line
	1300 2500 900  2500
Wire Wire Line
	1300 2600 900  2600
Wire Wire Line
	1300 2700 900  2700
Text Label 1200 2100 2    50   ~ 0
SEGB
Text Label 1200 2200 2    50   ~ 0
SEGC
Text Label 1200 2300 2    50   ~ 0
SEGD
Text Label 1200 2400 2    50   ~ 0
SEGE
Text Label 1200 2500 2    50   ~ 0
SEGF
Text Label 1200 2600 2    50   ~ 0
SEGG
Text Label 1200 2700 2    50   ~ 0
SEGDP
Wire Wire Line
	2900 2300 3200 2300
Wire Wire Line
	2900 4200 3300 4200
Wire Wire Line
	2900 3400 3250 3400
Wire Wire Line
	2900 2900 3250 2900
Wire Wire Line
	4250 2550 4650 2550
Wire Wire Line
	4250 2650 4650 2650
Text Label 4350 2550 0    50   ~ 0
DIG6_D
Text Label 4350 2650 0    50   ~ 0
DIG7_D
Text Label 3000 2300 0    50   ~ 0
DIG0
Text Label 3000 3400 0    50   ~ 0
DIG1
Text Label 3000 4200 0    50   ~ 0
DIG2
Wire Wire Line
	2950 5400 3450 5400
Text Label 3100 5400 0    50   ~ 0
DIG3
Wire Wire Line
	2950 6500 3500 6500
Text Label 3150 6500 0    50   ~ 0
DIG4
Wire Wire Line
	2950 7300 3450 7300
Text Label 3100 7300 0    50   ~ 0
DIG5
Text Label 2950 2900 0    50   ~ 0
DIG6_D
Wire Wire Line
	2950 6000 3450 6000
Text Label 3100 6000 0    50   ~ 0
DIG7_D
Wire Wire Line
	3450 2550 3150 2550
Text Label 3200 2550 0    50   ~ 0
SS
Wire Wire Line
	3150 2650 3450 2650
Wire Wire Line
	3450 2750 3150 2750
Text Label 3200 2650 0    50   ~ 0
SCK
Text Label 3200 2750 0    50   ~ 0
MOSI
Wire Wire Line
	8400 4000 8050 4000
Text Label 8150 4000 0    50   ~ 0
MOSI
Wire Wire Line
	8400 4200 8050 4200
Text Label 8150 4200 0    50   ~ 0
SCK
Wire Wire Line
	8400 3900 8050 3900
Text Label 8150 3900 0    50   ~ 0
SS
$Comp
L Device:R_US R1
U 1 1 5FFDFCD7
P 2900 900
F 0 "R1" H 2968 946 50  0000 L CNN
F 1 "30k" H 2968 855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2940 890 50  0001 C CNN
F 3 "~" H 2900 900 50  0001 C CNN
	1    2900 900 
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR01
U 1 1 5FFE521D
P 2900 700
F 0 "#PWR01" H 2900 550 50  0001 C CNN
F 1 "VDD" H 2915 873 50  0000 C CNN
F 2 "" H 2900 700 50  0001 C CNN
F 3 "" H 2900 700 50  0001 C CNN
	1    2900 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 700  2900 750 
Wire Wire Line
	2900 1050 2900 1150
Wire Wire Line
	2900 1150 3450 1150
Text Label 3150 1150 0    50   ~ 0
ISET
$Comp
L power:GND #PWR02
U 1 1 5FFECFF1
P 3850 3050
F 0 "#PWR02" H 3850 2800 50  0001 C CNN
F 1 "GND" H 3855 2877 50  0000 C CNN
F 2 "" H 3850 3050 50  0001 C CNN
F 3 "" H 3850 3050 50  0001 C CNN
	1    3850 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3050 3850 2950
Connection ~ 5200 3800
Text Label 7100 3800 0    50   ~ 0
VSNSL_F
Wire Wire Line
	9400 3500 9750 3500
Text Label 9500 3500 0    50   ~ 0
VSNSH_F
Text Label 5200 2900 0    50   ~ 0
VSNSH
$Comp
L Device:C C1
U 1 1 5FFF8980
P 8650 1600
F 0 "C1" H 8765 1646 50  0000 L CNN
F 1 "C" H 8765 1555 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 8688 1450 50  0001 C CNN
F 3 "~" H 8650 1600 50  0001 C CNN
	1    8650 1600
	1    0    0    -1  
$EndComp
$Comp
L power:VDD #PWR09
U 1 1 5FFFB1EE
P 8650 1350
F 0 "#PWR09" H 8650 1200 50  0001 C CNN
F 1 "VDD" H 8665 1523 50  0000 C CNN
F 2 "" H 8650 1350 50  0001 C CNN
F 3 "" H 8650 1350 50  0001 C CNN
	1    8650 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5FFFBEDA
P 8650 1900
F 0 "#PWR010" H 8650 1650 50  0001 C CNN
F 1 "GND" H 8655 1727 50  0000 C CNN
F 2 "" H 8650 1900 50  0001 C CNN
F 3 "" H 8650 1900 50  0001 C CNN
	1    8650 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 1900 8650 1750
Wire Wire Line
	8650 1450 8650 1350
$Comp
L Device:R_POT RV1
U 1 1 6000242B
P 9650 5350
F 0 "RV1" H 9581 5396 50  0000 R CNN
F 1 "R_POT" H 9581 5305 50  0000 R CNN
F 2 "my_library_foot:P120PK_Potentiometer" H 9650 5350 50  0001 C CNN
F 3 "~" H 9650 5350 50  0001 C CNN
	1    9650 5350
	1    0    0    -1  
$EndComp
Text Label 9900 5350 0    50   ~ 0
TSET
$Comp
L power:GND #PWR08
U 1 1 60006A2C
P 9650 5750
F 0 "#PWR08" H 9650 5500 50  0001 C CNN
F 1 "GND" H 9655 5577 50  0000 C CNN
F 2 "" H 9650 5750 50  0001 C CNN
F 3 "" H 9650 5750 50  0001 C CNN
	1    9650 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 5750 9650 5500
$Comp
L power:VDD #PWR07
U 1 1 6000A2FD
P 9650 4900
F 0 "#PWR07" H 9650 4750 50  0001 C CNN
F 1 "VDD" H 9665 5073 50  0000 C CNN
F 2 "" H 9650 4900 50  0001 C CNN
F 3 "" H 9650 4900 50  0001 C CNN
	1    9650 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 4900 9650 5200
Wire Wire Line
	9400 3600 9750 3600
Text Label 9500 3600 0    50   ~ 0
TSET
Wire Wire Line
	8400 2900 8150 2900
Wire Wire Line
	8400 3000 8150 3000
Wire Wire Line
	8400 3100 8150 3100
Wire Wire Line
	8400 3200 8150 3200
Wire Wire Line
	9400 3700 9750 3700
Wire Wire Line
	9400 3800 9750 3800
Wire Wire Line
	9400 4100 9750 4100
Wire Wire Line
	9400 4200 9750 4200
Text Label 8250 2900 0    50   ~ 0
D0
Text Label 8250 3000 0    50   ~ 0
D1
Text Label 8250 3100 0    50   ~ 0
D2
Text Label 8250 3200 0    50   ~ 0
D3
Text Label 9500 3700 0    50   ~ 0
VSNSL_F
Text Label 9500 3800 0    50   ~ 0
A3
Text Label 9500 4100 0    50   ~ 0
A6
Text Label 9500 4200 0    50   ~ 0
A7
$Comp
L Connector:Conn_01x08_Male J4
U 1 1 60034037
P 10500 3100
F 0 "J4" H 10472 3074 50  0000 R CNN
F 1 "Conn_01x08_Male" H 10472 2983 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 10500 3100 50  0001 C CNN
F 3 "~" H 10500 3100 50  0001 C CNN
	1    10500 3100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10300 2800 10050 2800
Text Label 10150 2800 0    50   ~ 0
D0
Wire Wire Line
	10300 2900 10050 2900
Text Label 10150 2900 0    50   ~ 0
D1
Wire Wire Line
	10300 3000 10050 3000
Text Label 10150 3000 0    50   ~ 0
D2
Wire Wire Line
	10300 3100 10050 3100
Text Label 10150 3100 0    50   ~ 0
D3
Wire Wire Line
	10300 3200 10050 3200
Wire Wire Line
	10300 3300 10050 3300
Text Label 10150 3300 0    50   ~ 0
A3
Wire Wire Line
	10300 3400 10050 3400
Text Label 10150 3400 0    50   ~ 0
A6
Wire Wire Line
	10300 3500 10050 3500
Text Label 10150 3500 0    50   ~ 0
A7
NoConn ~ 9400 2900
NoConn ~ 9400 3000
NoConn ~ 9400 3300
NoConn ~ 8400 3600
NoConn ~ 8400 3700
NoConn ~ 8400 3800
NoConn ~ 8800 2500
NoConn ~ 9000 2500
Wire Wire Line
	4250 2750 4650 2750
Text Label 4400 2750 0    50   ~ 0
MISO
Wire Wire Line
	8400 4100 8050 4100
Text Label 8150 4100 0    50   ~ 0
MISO
$Comp
L power:VDD #PWR0101
U 1 1 60085531
P 3850 700
F 0 "#PWR0101" H 3850 550 50  0001 C CNN
F 1 "VDD" H 3865 873 50  0000 C CNN
F 2 "" H 3850 700 50  0001 C CNN
F 3 "" H 3850 700 50  0001 C CNN
	1    3850 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 700  3850 950 
$Comp
L Mechanical:MountingHole H1
U 1 1 601BBFEE
P 4100 5050
F 0 "H1" H 4200 5096 50  0000 L CNN
F 1 "MountingHole" H 4200 5005 50  0000 L CNN
F 2 "my_library_foot:m3_mounting_hole" H 4100 5050 50  0001 C CNN
F 3 "~" H 4100 5050 50  0001 C CNN
	1    4100 5050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 601BC2CA
P 4100 5250
F 0 "H2" H 4200 5296 50  0000 L CNN
F 1 "MountingHole" H 4200 5205 50  0000 L CNN
F 2 "my_library_foot:m3_mounting_hole" H 4100 5250 50  0001 C CNN
F 3 "~" H 4100 5250 50  0001 C CNN
	1    4100 5250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 601BC424
P 4400 5250
F 0 "H4" H 4500 5296 50  0000 L CNN
F 1 "MountingHole" H 4500 5205 50  0000 L CNN
F 2 "my_library_foot:m3_mounting_hole" H 4400 5250 50  0001 C CNN
F 3 "~" H 4400 5250 50  0001 C CNN
	1    4400 5250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 601BC5F5
P 4350 5450
F 0 "H3" H 4450 5496 50  0000 L CNN
F 1 "MountingHole" H 4450 5405 50  0000 L CNN
F 2 "my_library_foot:m3_mounting_hole" H 4350 5450 50  0001 C CNN
F 3 "~" H 4350 5450 50  0001 C CNN
	1    4350 5450
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP4
U 1 1 60270DAB
P 7700 3000
F 0 "TP4" H 7758 3118 50  0000 L CNN
F 1 "VDRIVE" H 7758 3027 50  0000 L CNN
F 2 "my_library_foot:TestPoint_Keystone_5000-5004_Miniature" H 7900 3000 50  0001 C CNN
F 3 "~" H 7900 3000 50  0001 C CNN
	1    7700 3000
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP1
U 1 1 6027345E
P 5800 3750
F 0 "TP1" H 5858 3868 50  0000 L CNN
F 1 "VSNSL" H 5858 3777 50  0000 L CNN
F 2 "my_library_foot:TestPoint_Keystone_5000-5004_Miniature" H 6000 3750 50  0001 C CNN
F 3 "~" H 6000 3750 50  0001 C CNN
	1    5800 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP3
U 1 1 60274362
P 10250 5100
F 0 "TP3" H 10308 5218 50  0000 L CNN
F 1 "TSET" H 10308 5127 50  0000 L CNN
F 2 "my_library_foot:TestPoint_Keystone_5000-5004_Miniature" H 10450 5100 50  0001 C CNN
F 3 "~" H 10450 5100 50  0001 C CNN
	1    10250 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10250 5100 10250 5350
Wire Wire Line
	9800 5350 10250 5350
Wire Wire Line
	5800 3800 5800 3750
Wire Wire Line
	5200 3800 5800 3800
Wire Wire Line
	7700 3000 7700 3100
Wire Wire Line
	7700 3100 7800 3100
Wire Wire Line
	7800 3100 7800 3400
Connection ~ 7800 3400
Wire Wire Line
	7800 3400 8400 3400
Wire Wire Line
	5200 3600 5200 3800
Wire Wire Line
	5200 4250 5200 4500
Text Label 10150 3200 0    50   ~ 0
D4
Wire Wire Line
	8400 3300 8150 3300
Text Label 8250 3300 0    50   ~ 0
D4
$Comp
L Device:Q_NPN_Darlington_BCE Q1
U 1 1 60077757
P 5100 4050
F 0 "Q1" H 5290 4096 50  0000 L CNN
F 1 "Q_NPN_Darlington_BCE" H 5290 4005 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5300 4150 50  0001 C CNN
F 3 "~" H 5100 4050 50  0001 C CNN
	1    5100 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R4
U 1 1 60079E2C
P 4650 4050
F 0 "R4" V 4445 4050 50  0000 C CNN
F 1 "R_US" V 4536 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4690 4040 50  0001 C CNN
F 3 "~" H 4650 4050 50  0001 C CNN
	1    4650 4050
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 4050 4900 4050
Text Label 4350 4050 0    50   ~ 0
VDRIVE
$Comp
L Connector_Generic:Conn_01x06 J3
U 1 1 600AFD95
P 10400 3900
F 0 "J3" H 10480 3892 50  0000 L CNN
F 1 "Conn_01x06" H 10480 3801 50  0000 L CNN
F 2 "my_library_foot:S6B-XH-SM4-TB" H 10400 3900 50  0001 C CNN
F 3 "~" H 10400 3900 50  0001 C CNN
	1    10400 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 3700 10050 3700
$Comp
L power:VDD #PWR0102
U 1 1 600B7079
P 10050 3700
F 0 "#PWR0102" H 10050 3550 50  0001 C CNN
F 1 "VDD" H 10065 3873 50  0000 C CNN
F 2 "" H 10050 3700 50  0001 C CNN
F 3 "" H 10050 3700 50  0001 C CNN
	1    10050 3700
	1    0    0    -1  
$EndComp
Connection ~ 10050 3700
Wire Wire Line
	10050 3700 10000 3700
Wire Wire Line
	10200 3800 10050 3800
$Comp
L power:GND #PWR0103
U 1 1 600BC6AA
P 10050 3800
F 0 "#PWR0103" H 10050 3550 50  0001 C CNN
F 1 "GND" H 10055 3627 50  0000 C CNN
F 2 "" H 10050 3800 50  0001 C CNN
F 3 "" H 10050 3800 50  0001 C CNN
	1    10050 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3900 10200 3900
Wire Wire Line
	9400 4000 10200 4000
Wire Wire Line
	10200 4100 10000 4100
Wire Wire Line
	8400 3500 8050 3500
Text Label 8050 3500 0    50   ~ 0
ALT
Text Label 10050 4100 0    50   ~ 0
ALT
NoConn ~ 10200 4200
$Comp
L Device:R_US R5
U 1 1 6013AD36
P 6300 3800
F 0 "R5" V 6095 3800 50  0000 C CNN
F 1 "R_US" V 6186 3800 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6340 3790 50  0001 C CNN
F 3 "~" H 6300 3800 50  0001 C CNN
	1    6300 3800
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 6013C162
P 6650 4150
F 0 "C3" H 6765 4196 50  0000 L CNN
F 1 "C" H 6765 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6688 4000 50  0001 C CNN
F 3 "~" H 6650 4150 50  0001 C CNN
	1    6650 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3800 5800 3800
Connection ~ 5800 3800
Wire Wire Line
	6650 3800 6650 4000
$Comp
L power:GND #PWR015
U 1 1 6014B451
P 6650 4300
F 0 "#PWR015" H 6650 4050 50  0001 C CNN
F 1 "GND" H 6655 4127 50  0000 C CNN
F 2 "" H 6650 4300 50  0001 C CNN
F 3 "" H 6650 4300 50  0001 C CNN
	1    6650 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R3
U 1 1 60150252
P 6250 3000
F 0 "R3" V 6045 3000 50  0000 C CNN
F 1 "R_US" V 6136 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6290 2990 50  0001 C CNN
F 3 "~" H 6250 3000 50  0001 C CNN
	1    6250 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 3000 6650 3000
Wire Wire Line
	6650 3000 6650 3050
$Comp
L Device:C C2
U 1 1 60155CC5
P 6650 3200
F 0 "C2" H 6765 3246 50  0000 L CNN
F 1 "C" H 6765 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6688 3050 50  0001 C CNN
F 3 "~" H 6650 3200 50  0001 C CNN
	1    6650 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 60156CDB
P 6650 3350
F 0 "#PWR011" H 6650 3100 50  0001 C CNN
F 1 "GND" H 6655 3177 50  0000 C CNN
F 2 "" H 6650 3350 50  0001 C CNN
F 3 "" H 6650 3350 50  0001 C CNN
	1    6650 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:TestPoint TP5
U 1 1 6015A6C7
P 6650 3000
F 0 "TP5" H 6708 3118 50  0000 L CNN
F 1 "VSNSH_F" H 6708 3027 50  0000 L CNN
F 2 "my_library_foot:TestPoint_Keystone_5000-5004_Miniature" H 6850 3000 50  0001 C CNN
F 3 "~" H 6850 3000 50  0001 C CNN
	1    6650 3000
	1    0    0    -1  
$EndComp
Connection ~ 6650 3000
$Comp
L Connector:TestPoint TP2
U 1 1 6015B4EB
P 6650 3800
F 0 "TP2" H 6708 3918 50  0000 L CNN
F 1 "VSNSL_F" H 6708 3827 50  0000 L CNN
F 2 "my_library_foot:TestPoint_Keystone_5000-5004_Miniature" H 6850 3800 50  0001 C CNN
F 3 "~" H 6850 3800 50  0001 C CNN
	1    6650 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3000 6100 3000
Wire Wire Line
	6450 3800 6650 3800
Text Label 7100 3000 0    50   ~ 0
VSNSH_F
Connection ~ 6650 3800
Wire Wire Line
	6650 3800 7150 3800
Wire Wire Line
	6650 3000 7200 3000
$Comp
L Connector:TestPoint TP6
U 1 1 601835FC
P 5800 3000
F 0 "TP6" H 5858 3118 50  0000 L CNN
F 1 "VSNSH" H 5858 3027 50  0000 L CNN
F 2 "my_library_foot:TestPoint_Keystone_5000-5004_Miniature" H 6000 3000 50  0001 C CNN
F 3 "~" H 6000 3000 50  0001 C CNN
	1    5800 3000
	1    0    0    -1  
$EndComp
Connection ~ 5800 3000
Text Label 5400 3800 0    50   ~ 0
VSNSL
Wire Wire Line
	5200 2750 5200 3000
Wire Wire Line
	5800 3000 5200 3000
Connection ~ 5200 3000
Wire Wire Line
	5200 3000 5200 3300
Wire Wire Line
	4500 4050 4350 4050
$EndSCHEMATC
