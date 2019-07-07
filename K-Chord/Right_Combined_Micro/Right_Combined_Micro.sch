EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:keyboard_parts
LIBS:mkl27z256vfm4
LIBS:Right_Combined_Micro-cache
EELAYER 25 0
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
L TEENSY2.0 U1
U 1 1 5A29D7A6
P 3000 2950
F 0 "U1" V 3050 2950 60  0000 C CNN
F 1 "TEENSY2.0" V 2950 2950 60  0000 C CNN
F 2 "keebs:Pro_Micro" H 3000 2950 60  0001 C CNN
F 3 "" H 3000 2950 60  0000 C CNN
	1    3000 2950
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 5A29D981
P 5150 1650
F 0 "D1" H 5150 1750 50  0000 C CNN
F 1 "D" H 5150 1550 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 5150 1650 50  0001 C CNN
F 3 "" H 5150 1650 50  0001 C CNN
	1    5150 1650
	1    0    0    -1  
$EndComp
$Comp
L D D2
U 1 1 5A29D9AA
P 5150 1950
F 0 "D2" H 5150 2050 50  0000 C CNN
F 1 "D" H 5150 1850 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 5150 1950 50  0001 C CNN
F 3 "" H 5150 1950 50  0001 C CNN
	1    5150 1950
	1    0    0    -1  
$EndComp
$Comp
L D D3
U 1 1 5A29D9CB
P 5150 2250
F 0 "D3" H 5150 2350 50  0000 C CNN
F 1 "D" H 5150 2150 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 5150 2250 50  0001 C CNN
F 3 "" H 5150 2250 50  0001 C CNN
	1    5150 2250
	1    0    0    -1  
$EndComp
$Comp
L D D4
U 1 1 5A29DA06
P 5150 2550
F 0 "D4" H 5150 2650 50  0000 C CNN
F 1 "D" H 5150 2450 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 5150 2550 50  0001 C CNN
F 3 "" H 5150 2550 50  0001 C CNN
	1    5150 2550
	1    0    0    -1  
$EndComp
$Comp
L D D5
U 1 1 5A29DF3E
P 6550 1650
F 0 "D5" H 6550 1750 50  0000 C CNN
F 1 "D" H 6550 1550 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 6550 1650 50  0001 C CNN
F 3 "" H 6550 1650 50  0001 C CNN
	1    6550 1650
	1    0    0    -1  
$EndComp
$Comp
L D D6
U 1 1 5A29DF5F
P 6550 1950
F 0 "D6" H 6550 2050 50  0000 C CNN
F 1 "D" H 6550 1850 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 6550 1950 50  0001 C CNN
F 3 "" H 6550 1950 50  0001 C CNN
	1    6550 1950
	1    0    0    -1  
$EndComp
$Comp
L D D7
U 1 1 5A29DF90
P 6550 2250
F 0 "D7" H 6550 2350 50  0000 C CNN
F 1 "D" H 6550 2150 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 6550 2250 50  0001 C CNN
F 3 "" H 6550 2250 50  0001 C CNN
	1    6550 2250
	1    0    0    -1  
$EndComp
$Comp
L D D8
U 1 1 5A29DFBF
P 6550 2550
F 0 "D8" H 6550 2650 50  0000 C CNN
F 1 "D" H 6550 2450 50  0000 C CNN
F 2 "keyboard_parts:D_SOD123_axial" H 6550 2550 50  0001 C CNN
F 3 "" H 6550 2550 50  0001 C CNN
	1    6550 2550
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K1
U 1 1 5A29E076
P 5600 1650
F 0 "K1" H 5550 1650 60  0000 C CNN
F 1 "KEYSW" H 5600 1550 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 5600 1650 60  0001 C CNN
F 3 "" H 5600 1650 60  0000 C CNN
	1    5600 1650
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K2
U 1 1 5A29E0B1
P 5600 1950
F 0 "K2" H 5550 1950 60  0000 C CNN
F 1 "KEYSW" H 5600 1850 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 5600 1950 60  0001 C CNN
F 3 "" H 5600 1950 60  0000 C CNN
	1    5600 1950
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K3
U 1 1 5A29E0F6
P 5600 2250
F 0 "K3" H 5550 2250 60  0000 C CNN
F 1 "KEYSW" H 5600 2150 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 5600 2250 60  0001 C CNN
F 3 "" H 5600 2250 60  0000 C CNN
	1    5600 2250
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K4
U 1 1 5A29E12F
P 5600 2550
F 0 "K4" H 5550 2550 60  0000 C CNN
F 1 "KEYSW" H 5600 2450 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 5600 2550 60  0001 C CNN
F 3 "" H 5600 2550 60  0000 C CNN
	1    5600 2550
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K5
U 1 1 5A29E1F7
P 7000 1650
F 0 "K5" H 6950 1650 60  0000 C CNN
F 1 "KEYSW" H 7000 1550 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 7000 1650 60  0001 C CNN
F 3 "" H 7000 1650 60  0000 C CNN
	1    7000 1650
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K6
U 1 1 5A29E246
P 7000 1950
F 0 "K6" H 6950 1950 60  0000 C CNN
F 1 "KEYSW" H 7000 1850 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 7000 1950 60  0001 C CNN
F 3 "" H 7000 1950 60  0000 C CNN
	1    7000 1950
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K7
U 1 1 5A29E28B
P 7000 2250
F 0 "K7" H 6950 2250 60  0000 C CNN
F 1 "KEYSW" H 7000 2150 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 7000 2250 60  0001 C CNN
F 3 "" H 7000 2250 60  0000 C CNN
	1    7000 2250
	1    0    0    -1  
$EndComp
$Comp
L KEYSW K8
U 1 1 5A29E2E2
P 7000 2550
F 0 "K8" H 6950 2550 60  0000 C CNN
F 1 "KEYSW" H 7000 2450 60  0001 C CNN
F 2 "keebs:Mx_Alps_100" H 7000 2550 60  0001 C CNN
F 3 "" H 7000 2550 60  0000 C CNN
	1    7000 2550
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x10_Male J1
U 1 1 5A29E5A8
P 3000 5100
F 0 "J1" H 3000 5600 50  0000 C CNN
F 1 "Brd2" H 3000 4500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10_Pitch2.54mm" H 3000 5100 50  0001 C CNN
F 3 "" H 3000 5100 50  0001 C CNN
	1    3000 5100
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x10_Male J2
U 1 1 5A29E695
P 3000 6300
F 0 "J2" H 3000 6800 50  0000 C CNN
F 1 "Brd3" H 3000 5700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10_Pitch2.54mm" H 3000 6300 50  0001 C CNN
F 3 "" H 3000 6300 50  0001 C CNN
	1    3000 6300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5A29FAE5
P 4200 4500
F 0 "R2" V 4280 4500 50  0000 C CNN
F 1 "R" V 4200 4500 50  0000 C CNN
F 2 "Resistors_Universal:Resistor_SMD+THTuniversal_2512_RM10_HandSoldering" V 4130 4500 50  0001 C CNN
F 3 "" H 4200 4500 50  0001 C CNN
	1    4200 4500
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A29FB2E
P 4050 4500
F 0 "R1" V 4130 4500 50  0000 C CNN
F 1 "R" V 4050 4500 50  0000 C CNN
F 2 "Resistors_Universal:Resistor_SMD+THTuniversal_2512_RM10_HandSoldering" V 3980 4500 50  0001 C CNN
F 3 "" H 4050 4500 50  0001 C CNN
	1    4050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2150 4550 2150
Wire Wire Line
	4550 1650 4550 3950
Wire Wire Line
	4550 1650 5000 1650
Wire Wire Line
	3600 2250 4600 2250
Wire Wire Line
	4600 1950 4600 4050
Wire Wire Line
	4600 1950 5000 1950
Wire Wire Line
	3600 4250 6200 4250
Wire Wire Line
	4700 4250 4700 2250
Wire Wire Line
	4700 2250 5000 2250
Wire Wire Line
	3600 4150 6250 4150
Wire Wire Line
	4650 4150 4650 2550
Wire Wire Line
	4650 2550 5000 2550
Wire Wire Line
	4600 4050 6150 4050
Wire Wire Line
	6150 4050 6150 1950
Wire Wire Line
	6150 1950 6400 1950
Connection ~ 4600 2250
Wire Wire Line
	6200 4250 6200 2250
Wire Wire Line
	6200 2250 6400 2250
Connection ~ 4700 4250
Wire Wire Line
	6250 4150 6250 2550
Wire Wire Line
	6250 2550 6400 2550
Connection ~ 4650 4150
Wire Wire Line
	4550 3950 6100 3950
Wire Wire Line
	6100 3950 6100 1650
Wire Wire Line
	6100 1650 6400 1650
Connection ~ 4550 2150
Wire Wire Line
	3600 1950 4500 1950
Wire Wire Line
	4500 1950 4500 1400
Wire Wire Line
	4500 1400 5950 1400
Wire Wire Line
	5950 1400 5950 2550
Wire Wire Line
	5950 1650 5900 1650
Wire Wire Line
	5950 1950 5900 1950
Connection ~ 5950 1650
Wire Wire Line
	5950 2250 5900 2250
Connection ~ 5950 1950
Wire Wire Line
	5950 2550 5900 2550
Connection ~ 5950 2250
Wire Wire Line
	3600 2750 4450 2750
Wire Wire Line
	4450 2750 4450 1300
Wire Wire Line
	4450 1300 7400 1300
Wire Wire Line
	7400 1300 7400 2550
Wire Wire Line
	7400 1650 7300 1650
Wire Wire Line
	7400 1950 7300 1950
Connection ~ 7400 1650
Wire Wire Line
	7400 2250 7300 2250
Connection ~ 7400 1950
Wire Wire Line
	7400 2550 7300 2550
Connection ~ 7400 2250
Wire Wire Line
	3200 4700 4750 4700
Wire Wire Line
	4750 3950 4750 5900
Connection ~ 4750 3950
Wire Wire Line
	3200 4800 4800 4800
Wire Wire Line
	4800 4050 4800 6000
Connection ~ 4800 4050
Wire Wire Line
	4850 4150 4850 6200
Connection ~ 4850 4150
Wire Wire Line
	4900 4250 4900 6100
Connection ~ 4900 4250
Wire Wire Line
	4850 5000 3200 5000
Wire Wire Line
	3200 4900 4900 4900
Connection ~ 4900 4900
Wire Wire Line
	4750 5900 3200 5900
Connection ~ 4750 4700
Wire Wire Line
	4800 6000 3200 6000
Connection ~ 4800 4800
Wire Wire Line
	4900 6100 3200 6100
Wire Wire Line
	4850 6200 3200 6200
Connection ~ 4850 5000
Wire Wire Line
	3600 2350 4500 2350
Wire Wire Line
	4500 2350 4500 5100
Wire Wire Line
	4500 5100 3200 5100
Wire Wire Line
	3600 2850 4450 2850
Wire Wire Line
	3600 2950 4400 2950
Wire Wire Line
	3200 5200 4450 5200
Wire Wire Line
	4450 5200 4450 2850
Wire Wire Line
	4400 2950 4400 6300
Wire Wire Line
	4400 6300 3200 6300
Wire Wire Line
	3600 3050 4350 3050
Wire Wire Line
	4350 3050 4350 6400
Wire Wire Line
	4350 6400 3200 6400
Wire Wire Line
	3600 1750 4300 1750
Wire Wire Line
	4300 5600 3200 5600
Wire Wire Line
	4300 6800 3200 6800
Connection ~ 4300 5600
Wire Wire Line
	3600 1850 4300 1850
Connection ~ 4300 1850
Wire Wire Line
	4050 4650 4050 6700
Wire Wire Line
	4050 6700 3200 6700
Wire Wire Line
	4200 4650 4200 6600
Wire Wire Line
	4200 6600 3200 6600
Wire Wire Line
	4050 4350 4050 2600
Wire Wire Line
	4050 2600 3600 2600
Wire Wire Line
	4200 4350 4200 2500
Wire Wire Line
	4200 2500 3600 2500
Wire Wire Line
	2150 4500 3900 4500
Wire Wire Line
	3900 3500 3900 6500
Wire Wire Line
	3900 5300 3200 5300
Wire Wire Line
	3900 6500 3200 6500
Connection ~ 3900 5300
$Comp
L R R3
U 1 1 5A2A02BA
P 2150 4250
F 0 "R3" V 2230 4250 50  0000 C CNN
F 1 "R" V 2150 4250 50  0000 C CNN
F 2 "Resistors_Universal:Resistor_SMD+THTuniversal_2512_RM10_HandSoldering" V 2080 4250 50  0001 C CNN
F 3 "" H 2150 4250 50  0001 C CNN
	1    2150 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4400 2150 4500
Wire Wire Line
	2150 1150 2150 4100
Wire Wire Line
	3600 3450 3750 3450
Wire Wire Line
	3750 3450 3750 5400
Wire Wire Line
	3750 5400 3200 5400
Wire Wire Line
	3600 2050 3700 2050
Wire Wire Line
	3700 2050 3700 5500
Wire Wire Line
	3700 5500 3200 5500
$Comp
L Conn_01x02_Male J3
U 1 1 5A2A0676
P 2200 1350
F 0 "J3" H 2200 1450 50  0000 C CNN
F 1 "Power" H 2200 1150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2200 1350 50  0001 C CNN
F 3 "" H 2200 1350 50  0001 C CNN
	1    2200 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1450 2400 1650
Wire Wire Line
	3600 3250 3750 3250
Wire Wire Line
	3750 3250 3750 1150
Wire Wire Line
	3750 1150 2150 1150
Wire Wire Line
	2400 1350 2400 1150
Connection ~ 2400 1150
$Comp
L Conn_01x04_Male J4
U 1 1 5A2A093C
P 5150 2950
F 0 "J4" H 5150 3150 50  0000 C CNN
F 1 "PSP Joystick" H 5150 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04_Pitch2.54mm" H 5150 2950 50  0001 C CNN
F 3 "" H 5150 2950 50  0001 C CNN
	1    5150 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3350 5500 3350
Wire Wire Line
	5500 3350 5500 3050
Wire Wire Line
	5500 3050 5350 3050
Wire Wire Line
	3600 3150 4000 3150
Wire Wire Line
	4000 3150 4000 3400
Wire Wire Line
	4000 3400 5550 3400
Wire Wire Line
	5550 3400 5550 2850
Wire Wire Line
	5550 2850 5350 2850
Wire Wire Line
	4300 3450 5450 3450
Wire Wire Line
	5450 3450 5450 3150
Wire Wire Line
	5450 3150 5350 3150
Connection ~ 4300 3450
Wire Wire Line
	3900 3500 5600 3500
Wire Wire Line
	5600 3500 5600 2950
Wire Wire Line
	5600 2950 5350 2950
Connection ~ 3900 4500
$Comp
L Conn_01x02_Male J5
U 1 1 5A2A0ED1
P 2200 2350
F 0 "J5" H 2200 2450 50  0000 C CNN
F 1 "Reset" H 2200 2150 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02_Pitch2.54mm" H 2200 2350 50  0001 C CNN
F 3 "" H 2200 2350 50  0001 C CNN
	1    2200 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2450 2400 2950
Wire Wire Line
	2400 2950 2250 2950
Wire Wire Line
	2250 2950 2250 3900
Wire Wire Line
	2250 3900 2400 3900
Wire Wire Line
	2400 2350 2450 2350
Wire Wire Line
	2450 2350 2450 3000
Wire Wire Line
	2450 3000 2300 3000
Wire Wire Line
	2300 3000 2300 3350
Wire Wire Line
	2300 3350 2400 3350
Wire Wire Line
	4300 1750 4300 6800
$Comp
L Conn_01x01_Male J6
U 1 1 5A2B8EE9
P 3800 1550
F 0 "J6" H 3800 1650 50  0000 C CNN
F 1 "thru" H 3800 1450 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch2.54mm" H 3800 1550 50  0001 C CNN
F 3 "" H 3800 1550 50  0001 C CNN
	1    3800 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1550 4000 2250
Connection ~ 4000 2250
$EndSCHEMATC
