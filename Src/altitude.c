static const short minAltP=6;
static const short maxAltP=1037;
static const int altTable [];

int pToAlt(int p) {
	if(p < minAltP) return 39999;
	if(p > maxAltP) return -1000;
	return altTable[p - minAltP];
}
static const int altTable [] = {
34508,
33452,
32546,
31756,
31054,
30420,
29842,
29312,
28822,
28368,
27942,
27544,
27170,
26816,
26480,
26162,
25858,
25570,
25292,
25028,
24774,
24528,
24294,
24066,
23848,
23636,
23432,
23234,
23042,
22854,
22674,
22498,
22328,
22160,
21998,
21840,
21686,
21536,
21390,
21246,
21106,
20968,
20834,
20704,
20576,
20450,
20326,
20204,
20086,
19970,
19856,
19744,
19634,
19524,
19418,
19314,
19210,
19108,
19008,
18910,
18814,
18718,
18624,
18532,
18440,
18350,
18262,
18174,
18088,
18004,
17920,
17836,
17754,
17674,
17594,
17516,
17438,
17360,
17284,
17210,
17136,
17062,
16990,
16918,
16846,
16776,
16708,
16638,
16572,
16504,
16438,
16372,
16306,
16242,
16178,
16116,
16054,
15992,
15930,
15870,
15810,
15750,
15690,
15632,
15574,
15516,
15460,
15404,
15348,
15292,
15238,
15184,
15130,
15076,
15022,
14970,
14918,
14866,
14814,
14764,
14714,
14662,
14614,
14564,
14514,
14466,
14418,
14370,
14322,
14276,
14228,
14182,
14136,
14090,
14044,
14000,
13956,
13910,
13866,
13822,
13778,
13736,
13692,
13650,
13608,
13566,
13524,
13482,
13440,
13400,
13358,
13318,
13278,
13238,
13198,
13158,
13120,
13080,
13042,
13004,
12964,
12926,
12888,
12852,
12814,
12776,
12740,
12702,
12666,
12630,
12594,
12558,
12522,
12486,
12452,
12416,
12382,
12346,
12312,
12278,
12244,
12210,
12176,
12142,
12108,
12076,
12042,
12008,
11976,
11944,
11912,
11878,
11846,
11814,
11784,
11752,
11720,
11688,
11658,
11626,
11596,
11564,
11534,
11504,
11474,
11444,
11414,
11384,
11354,
11324,
11296,
11266,
11236,
11208,
11178,
11150,
11122,
11092,
11064,
11036,
11008,
10980,
10952,
10924,
10896,
10868,
10842,
10814,
10786,
10760,
10732,
10706,
10678,
10652,
10624,
10598,
10572,
10546,
10518,
10492,
10466,
10440,
10414,
10388,
10362,
10336,
10310,
10284,
10260,
10234,
10208,
10184,
10158,
10132,
10108,
10082,
10058,
10032,
10008,
9984,
9958,
9934,
9910,
9886,
9860,
9836,
9812,
9788,
9764,
9740,
9716,
9692,
9668,
9646,
9622,
9598,
9574,
9552,
9528,
9504,
9482,
9458,
9436,
9412,
9390,
9366,
9344,
9320,
9298,
9276,
9252,
9230,
9208,
9186,
9162,
9140,
9118,
9096,
9074,
9052,
9030,
9008,
8986,
8964,
8942,
8922,
8900,
8878,
8856,
8834,
8814,
8792,
8770,
8750,
8728,
8708,
8686,
8666,
8644,
8624,
8602,
8582,
8560,
8540,
8520,
8498,
8478,
8458,
8438,
8416,
8396,
8376,
8356,
8336,
8316,
8296,
8276,
8256,
8236,
8216,
8196,
8176,
8156,
8136,
8116,
8096,
8076,
8058,
8038,
8018,
7998,
7980,
7960,
7940,
7922,
7902,
7884,
7864,
7846,
7826,
7806,
7788,
7770,
7750,
7732,
7712,
7694,
7676,
7656,
7638,
7620,
7600,
7582,
7564,
7546,
7526,
7508,
7490,
7472,
7454,
7436,
7418,
7400,
7380,
7362,
7344,
7326,
7310,
7292,
7274,
7256,
7238,
7220,
7202,
7184,
7166,
7150,
7132,
7114,
7096,
7080,
7062,
7044,
7026,
7010,
6992,
6974,
6958,
6940,
6924,
6906,
6890,
6872,
6856,
6838,
6822,
6804,
6788,
6770,
6754,
6736,
6720,
6704,
6686,
6670,
6654,
6636,
6620,
6604,
6586,
6570,
6554,
6538,
6522,
6504,
6488,
6472,
6456,
6440,
6424,
6408,
6390,
6374,
6358,
6342,
6326,
6310,
6294,
6278,
6262,
6246,
6230,
6216,
6200,
6184,
6168,
6152,
6136,
6120,
6104,
6090,
6074,
6058,
6042,
6028,
6012,
5996,
5980,
5966,
5950,
5934,
5920,
5904,
5888,
5874,
5858,
5842,
5828,
5812,
5798,
5782,
5768,
5752,
5738,
5722,
5708,
5692,
5678,
5662,
5648,
5632,
5618,
5602,
5588,
5574,
5558,
5544,
5530,
5514,
5500,
5486,
5470,
5456,
5442,
5428,
5412,
5398,
5384,
5370,
5354,
5340,
5326,
5312,
5298,
5284,
5268,
5254,
5240,
5226,
5212,
5198,
5184,
5170,
5156,
5142,
5128,
5114,
5100,
5086,
5072,
5058,
5044,
5030,
5016,
5002,
4988,
4974,
4960,
4946,
4932,
4918,
4906,
4892,
4878,
4864,
4850,
4836,
4824,
4810,
4796,
4782,
4770,
4756,
4742,
4728,
4716,
4702,
4688,
4676,
4662,
4648,
4634,
4622,
4608,
4596,
4582,
4568,
4556,
4542,
4530,
4516,
4502,
4490,
4476,
4464,
4450,
4438,
4424,
4412,
4398,
4386,
4372,
4360,
4346,
4334,
4320,
4308,
4294,
4282,
4270,
4256,
4244,
4230,
4218,
4206,
4192,
4180,
4168,
4154,
4142,
4130,
4116,
4104,
4092,
4080,
4066,
4054,
4042,
4028,
4016,
4004,
3992,
3980,
3966,
3954,
3942,
3930,
3918,
3904,
3892,
3880,
3868,
3856,
3844,
3832,
3820,
3806,
3794,
3782,
3770,
3758,
3746,
3734,
3722,
3710,
3698,
3686,
3674,
3662,
3650,
3638,
3626,
3614,
3602,
3590,
3578,
3566,
3554,
3542,
3530,
3518,
3506,
3494,
3482,
3472,
3460,
3448,
3436,
3424,
3412,
3400,
3390,
3378,
3366,
3354,
3342,
3330,
3320,
3308,
3296,
3284,
3272,
3262,
3250,
3238,
3226,
3216,
3204,
3192,
3182,
3170,
3158,
3146,
3136,
3124,
3112,
3102,
3090,
3078,
3068,
3056,
3044,
3034,
3022,
3012,
3000,
2988,
2978,
2966,
2956,
2944,
2932,
2922,
2910,
2900,
2888,
2878,
2866,
2856,
2844,
2834,
2822,
2812,
2800,
2790,
2778,
2768,
2756,
2746,
2734,
2724,
2712,
2702,
2690,
2680,
2670,
2658,
2648,
2636,
2626,
2616,
2604,
2594,
2582,
2572,
2562,
2550,
2540,
2530,
2518,
2508,
2498,
2486,
2476,
2466,
2454,
2444,
2434,
2422,
2412,
2402,
2392,
2380,
2370,
2360,
2350,
2338,
2328,
2318,
2308,
2296,
2286,
2276,
2266,
2256,
2244,
2234,
2224,
2214,
2204,
2192,
2182,
2172,
2162,
2152,
2142,
2132,
2120,
2110,
2100,
2090,
2080,
2070,
2060,
2050,
2040,
2028,
2018,
2008,
1998,
1988,
1978,
1968,
1958,
1948,
1938,
1928,
1918,
1908,
1898,
1888,
1878,
1868,
1858,
1848,
1838,
1828,
1818,
1808,
1798,
1788,
1778,
1768,
1758,
1748,
1738,
1728,
1718,
1708,
1700,
1690,
1680,
1670,
1660,
1650,
1640,
1630,
1620,
1612,
1602,
1592,
1582,
1572,
1562,
1552,
1544,
1534,
1524,
1514,
1504,
1494,
1486,
1476,
1466,
1456,
1446,
1438,
1428,
1418,
1408,
1398,
1390,
1380,
1370,
1360,
1352,
1342,
1332,
1322,
1314,
1304,
1294,
1286,
1276,
1266,
1256,
1248,
1238,
1228,
1220,
1210,
1200,
1192,
1182,
1172,
1164,
1154,
1144,
1136,
1126,
1116,
1108,
1098,
1088,
1080,
1070,
1062,
1052,
1042,
1034,
1024,
1016,
1006,
996,
988,
978,
970,
960,
950,
942,
932,
924,
914,
906,
896,
888,
878,
870,
860,
850,
842,
832,
824,
814,
806,
796,
788,
778,
770,
760,
752,
744,
734,
726,
716,
708,
698,
690,
680,
672,
662,
654,
646,
636,
628,
618,
610,
600,
592,
584,
574,
566,
556,
548,
540,
530,
522,
514,
504,
496,
486,
478,
470,
460,
452,
444,
434,
426,
418,
408,
400,
392,
382,
374,
366,
356,
348,
340,
330,
322,
314,
306,
296,
288,
280,
270,
262,
254,
246,
236,
228,
220,
212,
202,
194,
186,
178,
168,
160,
152,
144,
136,
126,
118,
110,
102,
94,
84,
76,
68,
60,
52,
42,
34,
26,
18,
10,
2,
-8,
-16,
-24,
-32,
-40,
-48,
-56,
-66,
-74,
-82,
-90,
-98,
-106,
-114,
-124,
-132,
-140,
-148,
-156,
-164,
-172,
-180,
-188,
-196
};
