/* 
 *  The Chronus Quantum (ChronusQ) software package is high-performace 
 *  computational chemistry software with a strong emphasis on explicitly 
 *  time-dependent and post-SCF quantum mechanical methods.
 *  
 *  Copyright (C) 2014-2015 Li Research Group (University of Washington)
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *  
 *  Contact the Developers:
 *    E-Mail: xsli@uw.edu
 *  
 */
#ifndef INCLUDED_ATOMS
#define INCLUDED_ATOMS 
#include <global.h>
 
/* Atomic Information*/ 
namespace ChronusQ {
struct Atoms { 
  int    atomicNumber;
  std::string symbol;
  int    massNumber; 
  double mass; 
  std::string stable;
  int defaultMult;
  double sradius;   //<< Atomic Radius (Ang) according Slater, J. Chem. Phys. 41, pg 3199 (1964)
 // Note for Hydrogen is already multiplied by 2 (to prevent the scaling later on) 
 // all noble gasses values are computed values from Reinhardt J. Chem. Phys. 47, pg 1300 (1967)
 // after Am all set to 2.01 (Ang)
}; 

static const Atoms elements[] = { 
  {1  ,"H" ,1  ,1.0078250321,"Y",2,1.058}, // 0 
  {1  ,"D" ,2  ,2.0141017780,"N",2,1.058}, // 1
  {1  ,"T" ,3  ,3.0160492675,"N",2,1.058}, // 2
  {2  ,"He",3  ,3.0160293097,"N",1,0.31}, // 3
  {2  ,"He",4  ,4.0026032497,"Y",1,0.31}, // 4
  {3  ,"Li",6  ,6.0151223,"N",2,1.45},    // 5 
  {3  ,"Li",7  ,7.0160040,"Y",2,1.45},    // 6
  {4  ,"Be",9  ,9.0121821,"Y",1,1.05},    // 7
  {5  ,"B" ,10 ,10.012937,"Y",2,0.85},    // 8
  {5  ,"B" ,11 ,11.0093055,"N",2,0.85},   // 9
  {6  ,"C" ,12 ,12.0000000,"Y",3,0.70},   // 10
  {6  ,"C" ,13 ,13.0033548378,"N",3,0.70},// 11 
  {6  ,"C" ,14 ,14.003241988,"N",3,0.70}, // 12
  {7  ,"N" ,14 ,14.0030740052,"Y",4,0.65},// 13 
  {7  ,"N" ,15 ,15.0001088984,"N",4,0.65},// 14 
  {8  ,"O" ,16 ,15.9949146221,"Y",3,0.60},// 15 
  {8  ,"O" ,17 ,16.99913150,"N",3,0.60},  // 16 
  {8  ,"O" ,18 ,17.9991604,"N",3,0.60},   // 17
  {9  ,"F" ,19 ,18.9984032,"Y",2,0.50},   // 18
  {10 ,"Ne",20 ,19.9924401759,"Y",1,0.38},// 19 
  {10 ,"Ne",21 ,20.99384674,"N",1,0.38},  // 20 
  {10 ,"Ne",22 ,21.99138551,"N",1,0.38},  // 21 
  {11 ,"Na",23 ,22.98976967,"Y",2,1.80},  // 22 
  {12 ,"Mg",24 ,23.98504190,"Y",1,1.50},  // 23  
  {12 ,"Mg",25 ,24.98583702,"N",1,1.50},  // 24 
  {12 ,"Mg",26 ,25.98259304,"N",1,1.50},  // 25 
  {13 ,"Al",27 ,26.98153844,"Y",2,1.25},  // 26 
  {14 ,"Si",28 ,27.9769265327,"Y",4,1.10},// 27  
  {14 ,"Si",29 ,28.97649472,"N",4,1.10},  // 28    
  {14 ,"Si",30 ,29.97377022,"N",4,1.10},  // 29  
  {15 ,"P" ,31 ,30.97376151,"Y",6,1.00},  // 30 
  {16 ,"S" ,32 ,31.97207069,"Y",3,1.00},  // 31 
  {16 ,"S" ,33 ,32.97145850,"N",3,1.00},  // 32 
  {16 ,"S" ,34 ,33.96786683,"N",3,1.00},  // 33 
  {16 ,"S" ,36 ,35.96708088,"N",3,1.00},  // 34 
  {17 ,"Cl",35 ,34.96885271,"Y",2,1.00},  // 35 
  {17 ,"Cl",37 ,36.96590260,"N",2,1.00},  // 36 
  {18 ,"Ar",36 ,35.96754628,"N",1,0.71},  // 37 
  {18 ,"Ar",38 ,37.9627322,"N",1,0.71},   // 38
  {18 ,"Ar",40 ,39.962383123,"Y",1,0.71}, // 39
  {19 ,"K" ,39, 38.9637069,"Y",-1,2.20},  // 40 
  {19 ,"K" ,40, 39.96399867,"N",-1,2.20}, // 41
  {19 ,"K" ,41, 40.96182597,"N",-1,2.20}, // 42
  {20 ,"Ca",40, 39.9625912,"Y",-1,1.80},  // 43
  {20 ,"Ca",42, 41.9586183,"N",-1,1.80},  // 44
  {20 ,"Ca",43, 42.9587668,"N",-1,1.80},  // 45
  {20 ,"Ca",44, 43.9554811,"N",-1,1.80},  // 46
  {20 ,"Ca",46, 45.9536928,"N",-1,1.80},  // 47
  {20 ,"Ca",48, 47.952534,"N",-1,1.80},   // 48
  {21 ,"Sc",45, 44.9559102,"Y",-1,1.60},  // 49
  {22 ,"Ti",46, 45.9526295,"N",-1,1.40},  // 50
  {22 ,"Ti",47, 46.9517638,"N",-1,1.40},  // 51
  {22 ,"Ti",48, 47.9479471,"Y",-1,1.40},  // 52
  {22 ,"Ti",49, 48.9478708,"N",-1,1.40},  // 53
  {22 ,"Ti",50, 49.9447921,"N",-1,1.40},  // 54
  {23 ,"V" ,50, 49.9471628,"N",-1,1.35},  // 55
  {23 ,"V" ,51, 50.9439637,"Y",-1,1.35},  // 56
  {24 ,"Cr",50, 49.9460496,"N",-1,1.40},  // 57
  {24 ,"Cr",52, 51.9405119,"Y",-1,1.40},  // 58
  {24 ,"Cr",53, 52.9406538,"N",-1,1.40},  // 59
  {24 ,"Cr",54, 53.9388849,"N",-1,1.40},  // 60
  {25 ,"Mn",55, 54.9380496,"Y",-1,1.40},  // 61
  {26 ,"Fe",54, 53.9396148,"N",-1,1.40},  // 62
  {26 ,"Fe",56, 55.9349421,"Y",-1,1.40},  // 63
  {26 ,"Fe",57, 56.9353987,"N",-1,1.40},  // 64
  {26 ,"Fe",58, 57.9332805,"N",-1,1.40},  // 65
  {27 ,"Co",59, 58.9332002,"Y",-1,1.35},  // 66
  {28 ,"Ni",58, 57.9353479,"Y",-1,1.35},  // 67
  {28 ,"Ni",60, 59.9307906,"N",-1,1.35},  // 68
  {28 ,"Ni",61, 60.9310604,"N",-1,1.35},  // 69
  {28 ,"Ni",62, 61.9283488,"N",-1,1.35},  // 70 
  {28 ,"Ni",64, 63.9279696,"N",-1,1.35},  // 71 
  {29 ,"Cu",63, 62.9296011,"Y",-1,1.35},  // 72 
  {29 ,"Cu",65, 64.9277937,"N",-1,1.35},  // 73 
  {30 ,"Zn",64, 63.9291466,"Y",-1,1.35},  // 74 
  {30 ,"Zn",66, 65.9260368,"N",-1,1.35},  // 75 
  {30 ,"Zn",67, 66.9271309,"N",-1,1.35},  // 76 
  {30 ,"Zn",68, 67.9248476,"N",-1,1.35},  // 77 
  {30 ,"Zn",70, 69.925325,"N",-1,1.35},   // 78
  {31 ,"Ga",69, 68.925581,"Y",-1,1.30},   // 79
  {31 ,"Ga",71, 70.9247050,"N",-1,1.30},  // 80
  {32 ,"Ge",70, 69.9242504,"N",-1,1.25},  // 81
  {32 ,"Ge",72, 71.9220762,"N",-1,1.25},  // 82
  {32 ,"Ge",73, 72.9234594,"N",-1,1.25},  // 83
  {32 ,"Ge",74, 73.9211782,"Y",-1,1.25},  // 84
  {32 ,"Ge",76, 75.9214027,"N",-1,1.25},  // 85
  {33 ,"As",75, 74.9215964,"Y",-1,1.15},  // 86
  {34 ,"Se",74, 73.9224766,"N",-1,1.15},  // 87
  {34 ,"Se",76, 75.9192141,"N",-1,1.15},  // 88
  {34 ,"Se",77, 76.9199146,"N",-1,1.15},  // 89
  {34 ,"Se",78, 77.9173095,"N",-1,1.15},  // 90 
  {34 ,"Se",80, 79.9165218,"Y",-1,1.15},  // 91 
  {34 ,"Se",82, 81.9167000,"N",-1,1.15},  // 92 
  {35 ,"Br",79, 78.9183376,"Y",-1,1.15},  // 93 
  {35 ,"Br",81, 80.916291,"N",-1,1.15},   // 94
  {36 ,"Kr",78, 77.920386,"N",-1,0.88},   // 95
  {36 ,"Kr",80, 79.916378,"N",-1,0.88},   // 96
  {36 ,"Kr",82, 81.9134846,"N",-1,0.88},  // 97 
  {36 ,"Kr",83, 82.914136,"N",-1,0.88},   // 98
  {36 ,"Kr",84, 83.911507,"Y",-1,0.88},   // 99
  {36 ,"Kr",86, 85.9106103,"N",-1,0.88},  // 100 
  {37 ,"Rb",85, 84.9117893,"Y",-1,2.35},  // 101 
  {37 ,"Rb",87, 86.9091835,"N",-1,2.35},  // 102 
  {38 ,"Sr",84, 83.913425,"N",-1,2.00},   // 103
  {38 ,"Sr",86, 85.9092624,"N",-1,2.00},  // 104 
  {38 ,"Sr",87, 86.9088793,"N",-1,2.00},  // 105 
  {38 ,"Sr",88, 87.9056143,"Y",-1,2.00},  // 106 
  {39 ,"Y" ,89, 88.9058479,"Y",-1,1.80},  // 107 
  {40 ,"Zr",90, 89.9047037,"Y",-1,1.55},  // 108 
  {40 ,"Zr",91, 90.9056450,"N",-1,1.55},  // 109 
  {40 ,"Zr",92, 91.9050401,"N",-1,1.55},  // 110 
  {40 ,"Zr",94, 93.9063158,"N",-1,1.55},  // 111 
  {40 ,"Zr",96, 95.908276,"N",-1,1.55},   // 112
  {41 ,"Nb",93, 92.9063775,"Y",-1,1.45},  // 113 
  {42 ,"Mo",92, 91.906810,"N",-1,1.45},   // 114
  {42 ,"Mo",94, 93.9050876,"N",-1,1.45},  // 115 
  {42 ,"Mo",95, 94.9058415,"N",-1,1.45},  // 116 
  {42 ,"Mo",96, 95.9046789,"N",-1,1.45},  // 117 
  {42 ,"Mo",97, 96.9060210,"N",-1,1.45},  // 118  
  {42 ,"Mo",98, 97.9054078,"Y",-1,1.45},  // 119
  {42 ,"Mo",100,99.907477,"N",-1,1.45},   // 120 
  {43 ,"Tc",97, 96.906365,"N",-1,1.35},   // 121 
  {43 ,"Tc",98, 97.907216,"Y",-1,1.35},   // 122 
  {43 ,"Tc",99, 98.9062546,"N",-1,1.35},  // 123
  {44 ,"Ru",96, 95.907598,"N",-1,1.30},   // 124 
  {44 ,"Ru",98, 97.905287,"N",-1,1.30},   // 125 
  {44 ,"Ru",99, 98.9059393,"N",-1,1.30},  // 126
  {44 ,"Ru",100,99.9042197,"N",-1,1.30},  // 127
  {44 ,"Ru",101,100.9055822,"N",-1,1.30}, // 128
  {44 ,"Ru",102,101.9043495,"Y",-1,1.30}, // 129
  {44 ,"Ru",104,103.905430,"N",-1,1.30},  // 130 
  {45 ,"Rh",103,102.905504,"Y",-1,1.35},  // 131 
  {46 ,"Pd",102,101.905608,"N",-1,1.40},  // 132 
  {46 ,"Pd",104,103.904035,"N",-1,1.40},  // 133 
  {46 ,"Pd",105,104.905084,"N",-1,1.40},  // 134 
  {46 ,"Pd",106,105.903483,"Y",-1,1.40},  // 135 
  {46 ,"Pd",108,107.903894,"N",-1,1.40},  // 136 
  {46 ,"Pd",110,109.905152,"N",-1,1.40},  // 137 
  {47 ,"Ag",107,106.905093,"Y",-1,1.60},  // 138 
  {47 ,"Ag",109,108.904756,"N",-1,1.60},  // 139 
  {48 ,"Cd",106,105.906458,"N",-1,1.55},  // 140 
  {48 ,"Cd",108,107.904183,"N",-1,1.55},  // 141 
  {48 ,"Cd",110,109.903006,"N",-1,1.55},  // 142 
  {48 ,"Cd",111,110.904182,"N",-1,1.55},  // 143 
  {48 ,"Cd",112,111.9027572,"N",-1,1.55}, // 144
  {48 ,"Cd",113,112.9044009,"N",-1,1.55}, // 145
  {48 ,"Cd",114,113.9033581,"Y",-1,1.55}, // 146
  {48 ,"Cd",116,115.904755,"N",-1,1.55},  // 147 
  {49 ,"In",113,112.904061,"N",-1,1.55},  // 148 
  {49 ,"In",115,114.903878,"Y",-1,1.55},  // 149 
  {50 ,"Sn",112,111.904821,"N",-1,1.45},  // 150 
  {50 ,"Sn",114,113.902782,"N",-1,1.45},  // 151 
  {50 ,"Sn",115,114.903346,"N",-1,1.45},  // 152 
  {50 ,"Sn",116,115.901744,"N",-1,1.45},  // 153 
  {50 ,"Sn",117,116.902954,"N",-1,1.45},  // 154 
  {50 ,"Sn",118,117.901606,"N",-1,1.45},  // 155 
  {50 ,"Sn",119,118.903309,"N",-1,1.45},  // 156 
  {50 ,"Sn",120,119.9021966,"Y",-1,1.45}, // 157
  {50 ,"Sn",122,121.9034401,"N",-1,1.45}, // 158
  {50 ,"Sn",124,123.9052746,"N",-1,1.45}, // 159
  {51 ,"Sb",121,120.9038180,"Y",-1,1.45}, // 160 
  {51 ,"Sb",123,122.9042157,"N",-1,1.45}, // 161
  {52 ,"Te",120,119.904020,"N",-1,1.40},  // 162 
  {52 ,"Te",122,121.9030471,"N",-1,1.40}, // 163
  {52 ,"Te",123,122.9042730,"N",-1,1.40}, // 164
  {52 ,"Te",124,123.9028195,"N",-1,1.40}, // 165
  {52 ,"Te",125,124.9044247,"N",-1,1.40}, // 166
  {52 ,"Te",126,125.9033055,"N",-1,1.40}, // 167
  {52 ,"Te",128,127.9044614,"N",-1,1.40}, // 168
  {52 ,"Te",130,129.9062228,"Y",-1,1.40}, // 169
  {53 ,"I" ,127,126.904468,"Y",-1,1.40},  // 170 
  {54 ,"Xe",124,123.9058958,"N",-1,1.08}, // 171
  {54 ,"Xe",126,125.904269,"N",-1,1.08},  // 172
  {54 ,"Xe",128,127.9035304,"N",-1,1.08}, // 173
  {54 ,"Xe",129,128.9047795,"N",-1,1.08}, // 174
  {54 ,"Xe",130,129.9035079,"N",-1,1.08}, // 175
  {54 ,"Xe",131,130.9050819,"N",-1,1.08}, // 176
  {54 ,"Xe",132,131.9041545,"Y",-1,1.08}, // 177
  {54 ,"Xe",134,133.9053945,"N",-1,1.08}, // 178
  {54 ,"Xe",136,135.907220,"N",-1,1.08},  // 179 
  {55 ,"Cs",133,132.905447,"Y",-1,2.60},  // 180 
  {56 ,"Ba",130,129.906310,"N",-1,2.15},  // 181 
  {56 ,"Ba",132,131.905056,"N",-1,2.15},  // 182 
  {56 ,"Ba",134,133.904503,"N",-1,2.15},  // 183 
  {56 ,"Ba",135,134.905683,"N",-1,2.15},  // 184 
  {56 ,"Ba",136,135.904570,"N",-1,2.15},  // 185 
  {56 ,"Ba",137,136.905821,"N",-1,2.15},  // 186 
  {56 ,"Ba",138,137.905241,"Y",-1,2.15},  // 187 
  {57 ,"La",138,137.907107,"N",-1,1.95},  // 188 
  {57 ,"La",139,138.906348,"Y",-1,1.95},  // 189 
  {58 ,"Ce",136,135.907140,"N",-1,1.85},  // 190 
  {58 ,"Ce",138,137.905986,"N",-1,1.85},  // 191 
  {58 ,"Ce",140,139.905434,"Y",-1,1.85},  // 192 
  {58 ,"Ce",142,141.909240,"N",-1,1.85},  // 193 
  {59 ,"Pr",141,140.907648,"Y",-1,1.85},  // 194 
  {60 ,"Nd",142,141.907719,"Y",-1,1.85},  // 195 
  {60 ,"Nd",143,142.909810,"N",-1,1.85},  // 196 
  {60 ,"Nd",144,143.910083,"N",-1,1.85},  // 197 
  {60 ,"Nd",145,144.912569,"N",-1,1.85},  // 198 
  {60 ,"Nd",146,145.913112,"N",-1,1.85},  // 199 
  {60 ,"Nd",148,147.916889,"N",-1,1.85},  // 200 
  {60 ,"Nd",150,149.920887,"N",-1,1.85},  // 201 
  {61 ,"Pm",145,144.912744,"Y",-1,1.85},  // 202 
  {61 ,"Pm",147,146.915134,"N",-1,1.85},  // 203 
  {62 ,"Sm",144,143.911995,"N",-1,1.85},  // 204 
  {62 ,"Sm",147,146.914893,"N",-1,1.85},  // 205 
  {62 ,"Sm",148,147.914818,"N",-1,1.85},  // 206 
  {62 ,"Sm",149,148.917180,"N",-1,1.85},  // 207 
  {62 ,"Sm",150,149.917271,"N",-1,1.85},  // 208 
  {62 ,"Sm",152,151.919728,"Y",-1,1.85},  // 209 
  {62 ,"Sm",154,153.922205,"N",-1,1.85},  // 210 
  {63 ,"Eu",151,150.919846,"N",-1,1.85},  // 211 
  {63 ,"Eu",153,152.921226,"Y",-1,1.85},  // 212 
  {64 ,"Gd",152,151.919788,"N",-1,1.80},  // 213 
  {64 ,"Gd",154,153.920862,"N",-1,1.80},  // 214 
  {64 ,"Gd",155,154.922619,"N",-1,1.80},  // 215 
  {64 ,"Gd",156,155.922120,"N",-1,1.80},  // 216 
  {64 ,"Gd",157,156.923957,"N",-1,1.80},  // 217 
  {64 ,"Gd",158,157.924101,"Y",-1,1.80},  // 218 
  {64 ,"Gd",160,159.927051,"N",-1,1.80},  // 219 
  {65 ,"Tb",159,158.925343,"Y",-1,1.75},  // 220 
  {66 ,"Dy",156,155.924278,"N",-1,1.75},  // 221 
  {66 ,"Dy",158,157.924405,"N",-1,1.75},  // 222 
  {66 ,"Dy",160,159.925194,"N",-1,1.75},  // 223 
  {66 ,"Dy",161,160.926930,"N",-1,1.75},  // 224 
  {66 ,"Dy",162,161.926795,"Y",-1,1.75},  // 225 
  {66 ,"Dy",163,162.928728,"N",-1,1.75},  // 226 
  {66 ,"Dy",164,163.929171,"N",-1,1.75},  // 227 
  {67 ,"Ho",165,164.930319,"Y",-1,1.75},  // 228 
  {68 ,"Er",162,161.928775,"N",-1,1.75},  // 229 
  {68 ,"Er",164,163.929197,"N",-1,1.75},  // 230 
  {68 ,"Er",166,165.930290,"N",-1,1.75},  // 231 
  {68 ,"Er",167,166.932045,"N",-1,1.75},  // 232 
  {68 ,"Er",168,167.932368,"Y",-1,1.75},  // 233 
  {68 ,"Er",170,169.935460,"N",-1,1.75},  // 234 
  {69 ,"Tm",169,168.934211,"Y",-1,1.75},  // 235 
  {70 ,"Yb",168,167.933894,"N",-1,1.75},  // 236 
  {70 ,"Yb",170,169.934759,"N",-1,1.75},  // 237 
  {70 ,"Yb",171,170.936322,"N",-1,1.75},  // 238 
  {70 ,"Yb",172,171.9363777,"N",-1,1.75}, // 239
  {70 ,"Yb",173,172.9382068,"N",-1,1.75}, // 240 
  {70 ,"Yb",174,173.9388581,"Y",-1,1.75}, // 241
  {70 ,"Yb",176,175.942568,"N",-1,1.75},  // 242
  {71 ,"Lu",175,174.9407679,"Y",-1,1.75}, // 243
  {71 ,"Lu",176,175.9426824,"N",-1,1.75}, // 244
  {72 ,"Hf",174,173.940040,"N",-1,1.55},  // 245
  {72 ,"Hf",176,175.9414018,"N",-1,1.55}, // 246
  {72 ,"Hf",177,176.9432200,"N",-1,1.55}, // 247
  {72 ,"Hf",178,177.9436977,"Y",-1,1.55}, // 248
  {72 ,"Hf",179,178.9458151,"N",-1,1.55}, // 249
  {72 ,"Hf",180,179.9465488,"N",-1,1.55}, // 250 
  {73 ,"Ta",180,179.947466,"N",-1,1.45},  // 251
  {73 ,"Ta",181,180.947996,"Y",-1,1.45},  // 252
  {74 ,"W" ,180,179.946706,"N",-1,1.35},  // 253
  {74 ,"W" ,182,181.948206,"Y",-1,1.35},  // 254
  {74 ,"W" ,183,182.9502245,"N",-1,1.35}, // 255
  {74 ,"W" ,184,183.9509326,"N",-1,1.35}, // 256
  {74 ,"W" ,186,185.954362,"N",-1,1.35},  // 257
  {75 ,"Re",185,184.9529557,"N",-1,1.35}, // 258
  {75 ,"Re",187,186.9557508,"Y",-1,1.35}, // 259
  {76 ,"Os",184,183.952491,"N",-1,1.30},  // 260 
  {76 ,"Os",186,185.953838,"N",-1,1.30},  // 261
  {76 ,"Os",187,186.9557479,"N",-1,1.30}, // 262
  {76 ,"Os",188,187.9558360,"N",-1,1.30}, // 263
  {76 ,"Os",189,188.9581449,"N",-1,1.30}, // 264
  {76 ,"Os",190,189.958445,"N",-1,1.30},  // 265 
  {76 ,"Os",192,191.961479,"Y",-1,1.30},  // 266 
  {77 ,"Ir",191,190.960591,"N",-1,1.35},  // 267 
  {77 ,"Ir",193,192.962924,"Y",-1,1.35},  // 268 
  {78 ,"Pt",190,189.959930,"N",-1,1.35},  // 269 
  {78 ,"Pt",192,191.961035,"N",-1,1.35},  // 270 
  {78 ,"Pt",194,193.962664,"N",-1,1.35},  // 271 
  {78 ,"Pt",195,194.964774,"Y",-1,1.35},  // 272 
  {78 ,"Pt",196,195.964935,"N",-1,1.35},  // 273 
  {78 ,"Pt",198,197.967876,"N",-1,1.35},  // 274 
  {79 ,"Au",197,196.966552,"Y",-1,1.35},  // 275 
  {80 ,"Hg",196,195.965815,"N",-1,1.50},  // 276 
  {80 ,"Hg",198,197.966752,"N",-1,1.50},  // 277 
  {80 ,"Hg",199,198.968262,"N",-1,1.50},  // 278 
  {80 ,"Hg",200,199.968309,"N",-1,1.50},  // 279 
  {80 ,"Hg",201,200.970285,"N",-1,1.50},  // 280 
  {80 ,"Hg",202,201.970626,"Y",-1,1.50},  // 281 
  {80 ,"Hg",204,203.973476,"N",-1,1.50},  // 282 
  {81 ,"Tl",203,202.972329,"N",-1,1.90},  // 283 
  {81 ,"Tl",205,204.974412,"Y",-1,1.90},  // 284 
  {82 ,"Pb",204,203.973029,"N",-1,1.90},  // 285 
  {82 ,"Pb",206,205.974449,"N",-1,1.90},  // 286 
  {82 ,"Pb",207,206.975881,"N",-1,1.90},  // 287 
  {82 ,"Pb",208,207.976636,"Y",-1,1.90},  // 288 
  {83 ,"Bi",209,208.980383,"Y",-1,1.60},  // 289 
  {84 ,"Po",209,208.982416,"Y",-1,1.90},  // 290 
  {84 ,"Po",210,209.982857,"N",-1,1.90},  // 291 
  {85 ,"At",210,209.987131,"Y",-1,1.90},  // 292 
  {85 ,"At",211,210.987481,"N",-1,1.90},  // 293 
  {86 ,"Rn",211,210.990585,"N",-1,2.01},  // 294 
  {86 ,"Rn",220,220.0113841,"N",-1,2.01}, // 295
  {86 ,"Rn",222,222.0175705,"Y",-1,2.01}, // 296
  {87 ,"Fr",223,223.0197307,"Y",-1,1.90}, // 297
  {88 ,"Ra",223,223.018497,"N",-1,1.90},  // 298 
  {88 ,"Ra",224,224.0202020,"N",-1,1.90}, // 299
  {88 ,"Ra",226,226.0254026,"Y",-1,2.15}, // 300 
  {88 ,"Ra",228,228.0310641,"N",-1,2.15}, // 301
  {89 ,"Ac",227,227.0277470,"Y",-1,1.95}, // 302
  {90 ,"Th",230,230.0331266,"N",-1,1.80}, // 303
  {90 ,"Th",232,232.0380504,"Y",-1,1.80}, // 304
  {91 ,"Pa",231,231.0358789,"Y",-1,1.80}, // 305
  {92 ,"U" ,233,233.039628,"N",-1,1.75},  // 306
  {92 ,"U" ,234,234.0409456,"N",-1,1.75}, // 307
  {92 ,"U" ,235,235.0439231,"N",-1,1.75}, // 308
  {92 ,"U" ,236,236.0455619,"N",-1,1.75}, // 309
  {92 ,"U" ,238,238.0507826,"Y",-1,1.75}, // 310 
  {93 ,"Np",237,237.0481673,"Y",-1,1.75}, // 311
  {93 ,"Np",239,239.0529314,"N",-1,1.75}, // 312
  {94 ,"Pu",238,238.0495534,"N",-1,1.75}, // 313
  {94 ,"Pu",239,239.0521565,"N",-1,1.75}, // 314
  {94 ,"Pu",240,240.0538075,"N",-1,1.75}, // 315
  {94 ,"Pu",241,241.0568453,"N",-1,1.75}, // 316
  {94 ,"Pu",242,242.0587368,"N",-1,1.75}, // 317
  {94 ,"Pu",244,244.064198,"Y",-1,1.75},  // 318
  {95 ,"Am",241,241.0568229,"N",-1,1.75}, // 319
  {95 ,"Am",243,243.0613727,"Y",-1,1.75}, // 320 
  {96 ,"Cm",243,243.0613822,"N",-1,2.01}, // 321
  {96 ,"Cm",244,244.0627463,"N",-1,2.01}, // 322
  {96 ,"Cm",245,245.0654856,"N",-1,2.01}, // 323
  {96 ,"Cm",246,246.0672176,"N",-1,2.01}, // 324
  {96 ,"Cm",247,247.070347,"Y",-1,2.01},  // 325 
  {96 ,"Cm",248,248.072342,"N",-1,2.01},  // 326 
  {97 ,"Bk",247,247.070299,"Y",-1,2.01},  // 327 
  {97 ,"Bk",249,249.074980,"N",-1,2.01},  // 328 
  {98 ,"Cf",249,249.074847,"N",-1,2.01},  // 329 
  {98 ,"Cf",250,250.0764000,"N",-1,2.01}, // 330 
  {98 ,"Cf",251,251.079580,"Y",-1,2.01},  // 331 
  {98 ,"Cf",252,252.081620,"N",-1,2.01},  // 332 
  {99 ,"Es",252,252.082970,"Y",-1,2.01},  // 333 
  {100,"Fm",257,257.095099,"Y",-1,2.01},  // 334 
  {101,"Md",256,256.094050,"N",-1,2.01},  // 335 
  {101,"Md",258,258.098425,"Y",-1,2.01},  // 336 
  {102,"No",259,259.10102,"Y",-1,2.01},   // 337 
  {103,"Lr",262,262.10969,"Y",-1,2.01},   // 338 
  {104,"Rf",261,261.10875,"Y",-1,2.01},   // 339 
  {105,"Db",262,262.11415,"Y",-1,2.01},   // 340
  {106,"Sg",266,266.12193,"Y",-1,2.01},   // 341
  {107,"Bh",264,264.12473,"Y",-1,2.01},   // 342
  {109,"Mt",268,268.13882,"Y",-1,2.01}    // 343
};  

static std::vector<Atoms> atom(elements,elements+sizeof(elements)/sizeof(elements[0])); 
} // namespace ChronusQ
#endif 
