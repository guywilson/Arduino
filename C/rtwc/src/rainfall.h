#include <avr/pgmspace.h>

#ifndef _INCL_RAINFALL
#define _INCL_RAINFALL

#define RAINFALL_LOOKUP_BUFFER_SIZE		400

#define PI								3.14159265

#define TIPPING_BUCKET_VOLUME			1750		// In mm^3 (1 cm^3 | 1 ml = 1000mm^3)
#define COLLECTING_FUNNEL_RADIUS		50			// In mm

#define TIPS_TO_MM_SCALE_FACTOR			(TIPPING_BUCKET_VOLUME / (PI * COLLECTING_FUNNEL_RADIUS * COLLECTING_FUNNEL_RADIUS))


/******************************************************************************
**
** Calculate the rainfall in mm for values of number of tips. This is an
** expensive operation on a microcontroller, hence we calcuate this at 
** compile time and store in flash ROM.
**
** (Tipping bucket volume (mm^3) x # tips) / Collecting funnel area (mm^2)
**
** Tips is measured using a reed switch and a magnet attached to the tipping
** bucket. If the tipping bucket has a volume of 1750 mm^3 and the collecting funnel
** has a radius of 50 mm, then 233 tips per hour (tph) is equivalent to a rate of 
** rainfall of 51.94 mm/hour, which if maintained over a 48 hour period is the 
** highest rainfall ever recorded (Chennai, India - 2493mm).
**
** RAINFALL_LOOKUP_BUFFER_SIZE defines the number of slots in our lookup table, and
** therefore the maximum tph that is supported.
**
** This array of const values uses the PROGMEM modifier, a macro that forces
** the compiler to keep this data within the flash ROM and not take up valuable
** RAM space. To access values in the array, code must use the pgm_read_float()
** macro to get the far pointer to the flash ROM.
**
******************************************************************************/
static const float rainfallLookup[RAINFALL_LOOKUP_BUFFER_SIZE] PROGMEM =
{
	0.0,
	TIPS_TO_MM_SCALE_FACTOR,
	TIPS_TO_MM_SCALE_FACTOR * 2,
	TIPS_TO_MM_SCALE_FACTOR * 3,
	TIPS_TO_MM_SCALE_FACTOR * 4,
	TIPS_TO_MM_SCALE_FACTOR * 5,
	TIPS_TO_MM_SCALE_FACTOR * 6,
	TIPS_TO_MM_SCALE_FACTOR * 7,
	TIPS_TO_MM_SCALE_FACTOR * 8,
	TIPS_TO_MM_SCALE_FACTOR * 9,
	TIPS_TO_MM_SCALE_FACTOR * 10,
	TIPS_TO_MM_SCALE_FACTOR * 11,
	TIPS_TO_MM_SCALE_FACTOR * 12,
	TIPS_TO_MM_SCALE_FACTOR * 13,
	TIPS_TO_MM_SCALE_FACTOR * 14,
	TIPS_TO_MM_SCALE_FACTOR * 15,
	TIPS_TO_MM_SCALE_FACTOR * 16,
	TIPS_TO_MM_SCALE_FACTOR * 17,
	TIPS_TO_MM_SCALE_FACTOR * 18,
	TIPS_TO_MM_SCALE_FACTOR * 19,
	TIPS_TO_MM_SCALE_FACTOR * 20,
	TIPS_TO_MM_SCALE_FACTOR * 21,
	TIPS_TO_MM_SCALE_FACTOR * 22,
	TIPS_TO_MM_SCALE_FACTOR * 23,
	TIPS_TO_MM_SCALE_FACTOR * 24,
	TIPS_TO_MM_SCALE_FACTOR * 25,
	TIPS_TO_MM_SCALE_FACTOR * 26,
	TIPS_TO_MM_SCALE_FACTOR * 27,
	TIPS_TO_MM_SCALE_FACTOR * 28,
	TIPS_TO_MM_SCALE_FACTOR * 29,
	TIPS_TO_MM_SCALE_FACTOR * 30,
	TIPS_TO_MM_SCALE_FACTOR * 31,
	TIPS_TO_MM_SCALE_FACTOR * 32,
	TIPS_TO_MM_SCALE_FACTOR * 33,
	TIPS_TO_MM_SCALE_FACTOR * 34,
	TIPS_TO_MM_SCALE_FACTOR * 35,
	TIPS_TO_MM_SCALE_FACTOR * 36,
	TIPS_TO_MM_SCALE_FACTOR * 37,
	TIPS_TO_MM_SCALE_FACTOR * 38,
	TIPS_TO_MM_SCALE_FACTOR * 39,
	TIPS_TO_MM_SCALE_FACTOR * 40,
	TIPS_TO_MM_SCALE_FACTOR * 41,
	TIPS_TO_MM_SCALE_FACTOR * 42,
	TIPS_TO_MM_SCALE_FACTOR * 43,
	TIPS_TO_MM_SCALE_FACTOR * 44,
	TIPS_TO_MM_SCALE_FACTOR * 45,
	TIPS_TO_MM_SCALE_FACTOR * 46,
	TIPS_TO_MM_SCALE_FACTOR * 47,
	TIPS_TO_MM_SCALE_FACTOR * 48,
	TIPS_TO_MM_SCALE_FACTOR * 49,
	TIPS_TO_MM_SCALE_FACTOR * 50,
	TIPS_TO_MM_SCALE_FACTOR * 51,
	TIPS_TO_MM_SCALE_FACTOR * 52,
	TIPS_TO_MM_SCALE_FACTOR * 53,
	TIPS_TO_MM_SCALE_FACTOR * 54,
	TIPS_TO_MM_SCALE_FACTOR * 55,
	TIPS_TO_MM_SCALE_FACTOR * 56,
	TIPS_TO_MM_SCALE_FACTOR * 57,
	TIPS_TO_MM_SCALE_FACTOR * 58,
	TIPS_TO_MM_SCALE_FACTOR * 59,
	TIPS_TO_MM_SCALE_FACTOR * 60,
	TIPS_TO_MM_SCALE_FACTOR * 61,
	TIPS_TO_MM_SCALE_FACTOR * 62,
	TIPS_TO_MM_SCALE_FACTOR * 63,
	TIPS_TO_MM_SCALE_FACTOR * 64,
	TIPS_TO_MM_SCALE_FACTOR * 65,
	TIPS_TO_MM_SCALE_FACTOR * 66,
	TIPS_TO_MM_SCALE_FACTOR * 67,
	TIPS_TO_MM_SCALE_FACTOR * 68,
	TIPS_TO_MM_SCALE_FACTOR * 69,
	TIPS_TO_MM_SCALE_FACTOR * 70,
	TIPS_TO_MM_SCALE_FACTOR * 71,
	TIPS_TO_MM_SCALE_FACTOR * 72,
	TIPS_TO_MM_SCALE_FACTOR * 73,
	TIPS_TO_MM_SCALE_FACTOR * 74,
	TIPS_TO_MM_SCALE_FACTOR * 75,
	TIPS_TO_MM_SCALE_FACTOR * 76,
	TIPS_TO_MM_SCALE_FACTOR * 77,
	TIPS_TO_MM_SCALE_FACTOR * 78,
	TIPS_TO_MM_SCALE_FACTOR * 79,
	TIPS_TO_MM_SCALE_FACTOR * 80,
	TIPS_TO_MM_SCALE_FACTOR * 81,
	TIPS_TO_MM_SCALE_FACTOR * 82,
	TIPS_TO_MM_SCALE_FACTOR * 83,
	TIPS_TO_MM_SCALE_FACTOR * 84,
	TIPS_TO_MM_SCALE_FACTOR * 85,
	TIPS_TO_MM_SCALE_FACTOR * 86,
	TIPS_TO_MM_SCALE_FACTOR * 87,
	TIPS_TO_MM_SCALE_FACTOR * 88,
	TIPS_TO_MM_SCALE_FACTOR * 89,
	TIPS_TO_MM_SCALE_FACTOR * 90,
	TIPS_TO_MM_SCALE_FACTOR * 91,
	TIPS_TO_MM_SCALE_FACTOR * 92,
	TIPS_TO_MM_SCALE_FACTOR * 93,
	TIPS_TO_MM_SCALE_FACTOR * 94,
	TIPS_TO_MM_SCALE_FACTOR * 95,
	TIPS_TO_MM_SCALE_FACTOR * 96,
	TIPS_TO_MM_SCALE_FACTOR * 97,
	TIPS_TO_MM_SCALE_FACTOR * 98,
	TIPS_TO_MM_SCALE_FACTOR * 99,
	TIPS_TO_MM_SCALE_FACTOR * 100,
	TIPS_TO_MM_SCALE_FACTOR * 101,
	TIPS_TO_MM_SCALE_FACTOR * 102,
	TIPS_TO_MM_SCALE_FACTOR * 103,
	TIPS_TO_MM_SCALE_FACTOR * 104,
	TIPS_TO_MM_SCALE_FACTOR * 105,
	TIPS_TO_MM_SCALE_FACTOR * 106,
	TIPS_TO_MM_SCALE_FACTOR * 107,
	TIPS_TO_MM_SCALE_FACTOR * 108,
	TIPS_TO_MM_SCALE_FACTOR * 109,
	TIPS_TO_MM_SCALE_FACTOR * 110,
	TIPS_TO_MM_SCALE_FACTOR * 111,
	TIPS_TO_MM_SCALE_FACTOR * 112,
	TIPS_TO_MM_SCALE_FACTOR * 113,
	TIPS_TO_MM_SCALE_FACTOR * 114,
	TIPS_TO_MM_SCALE_FACTOR * 115,
	TIPS_TO_MM_SCALE_FACTOR * 116,
	TIPS_TO_MM_SCALE_FACTOR * 117,
	TIPS_TO_MM_SCALE_FACTOR * 118,
	TIPS_TO_MM_SCALE_FACTOR * 119,
	TIPS_TO_MM_SCALE_FACTOR * 120,
	TIPS_TO_MM_SCALE_FACTOR * 121,
	TIPS_TO_MM_SCALE_FACTOR * 122,
	TIPS_TO_MM_SCALE_FACTOR * 123,
	TIPS_TO_MM_SCALE_FACTOR * 124,
	TIPS_TO_MM_SCALE_FACTOR * 125,
	TIPS_TO_MM_SCALE_FACTOR * 126,
	TIPS_TO_MM_SCALE_FACTOR * 127,
	TIPS_TO_MM_SCALE_FACTOR * 128,
	TIPS_TO_MM_SCALE_FACTOR * 129,
	TIPS_TO_MM_SCALE_FACTOR * 130,
	TIPS_TO_MM_SCALE_FACTOR * 131,
	TIPS_TO_MM_SCALE_FACTOR * 132,
	TIPS_TO_MM_SCALE_FACTOR * 133,
	TIPS_TO_MM_SCALE_FACTOR * 134,
	TIPS_TO_MM_SCALE_FACTOR * 135,
	TIPS_TO_MM_SCALE_FACTOR * 136,
	TIPS_TO_MM_SCALE_FACTOR * 137,
	TIPS_TO_MM_SCALE_FACTOR * 138,
	TIPS_TO_MM_SCALE_FACTOR * 139,
	TIPS_TO_MM_SCALE_FACTOR * 140,
	TIPS_TO_MM_SCALE_FACTOR * 141,
	TIPS_TO_MM_SCALE_FACTOR * 142,
	TIPS_TO_MM_SCALE_FACTOR * 143,
	TIPS_TO_MM_SCALE_FACTOR * 144,
	TIPS_TO_MM_SCALE_FACTOR * 145,
	TIPS_TO_MM_SCALE_FACTOR * 146,
	TIPS_TO_MM_SCALE_FACTOR * 147,
	TIPS_TO_MM_SCALE_FACTOR * 148,
	TIPS_TO_MM_SCALE_FACTOR * 149,
	TIPS_TO_MM_SCALE_FACTOR * 150,
	TIPS_TO_MM_SCALE_FACTOR * 151,
	TIPS_TO_MM_SCALE_FACTOR * 152,
	TIPS_TO_MM_SCALE_FACTOR * 153,
	TIPS_TO_MM_SCALE_FACTOR * 154,
	TIPS_TO_MM_SCALE_FACTOR * 155,
	TIPS_TO_MM_SCALE_FACTOR * 156,
	TIPS_TO_MM_SCALE_FACTOR * 157,
	TIPS_TO_MM_SCALE_FACTOR * 158,
	TIPS_TO_MM_SCALE_FACTOR * 159,
	TIPS_TO_MM_SCALE_FACTOR * 160,
	TIPS_TO_MM_SCALE_FACTOR * 161,
	TIPS_TO_MM_SCALE_FACTOR * 162,
	TIPS_TO_MM_SCALE_FACTOR * 163,
	TIPS_TO_MM_SCALE_FACTOR * 164,
	TIPS_TO_MM_SCALE_FACTOR * 165,
	TIPS_TO_MM_SCALE_FACTOR * 166,
	TIPS_TO_MM_SCALE_FACTOR * 167,
	TIPS_TO_MM_SCALE_FACTOR * 168,
	TIPS_TO_MM_SCALE_FACTOR * 169,
	TIPS_TO_MM_SCALE_FACTOR * 170,
	TIPS_TO_MM_SCALE_FACTOR * 171,
	TIPS_TO_MM_SCALE_FACTOR * 172,
	TIPS_TO_MM_SCALE_FACTOR * 173,
	TIPS_TO_MM_SCALE_FACTOR * 174,
	TIPS_TO_MM_SCALE_FACTOR * 175,
	TIPS_TO_MM_SCALE_FACTOR * 176,
	TIPS_TO_MM_SCALE_FACTOR * 177,
	TIPS_TO_MM_SCALE_FACTOR * 178,
	TIPS_TO_MM_SCALE_FACTOR * 179,
	TIPS_TO_MM_SCALE_FACTOR * 180,
	TIPS_TO_MM_SCALE_FACTOR * 181,
	TIPS_TO_MM_SCALE_FACTOR * 182,
	TIPS_TO_MM_SCALE_FACTOR * 183,
	TIPS_TO_MM_SCALE_FACTOR * 184,
	TIPS_TO_MM_SCALE_FACTOR * 185,
	TIPS_TO_MM_SCALE_FACTOR * 186,
	TIPS_TO_MM_SCALE_FACTOR * 187,
	TIPS_TO_MM_SCALE_FACTOR * 188,
	TIPS_TO_MM_SCALE_FACTOR * 189,
	TIPS_TO_MM_SCALE_FACTOR * 190,
	TIPS_TO_MM_SCALE_FACTOR * 191,
	TIPS_TO_MM_SCALE_FACTOR * 192,
	TIPS_TO_MM_SCALE_FACTOR * 193,
	TIPS_TO_MM_SCALE_FACTOR * 194,
	TIPS_TO_MM_SCALE_FACTOR * 195,
	TIPS_TO_MM_SCALE_FACTOR * 196,
	TIPS_TO_MM_SCALE_FACTOR * 197,
	TIPS_TO_MM_SCALE_FACTOR * 198,
	TIPS_TO_MM_SCALE_FACTOR * 199,
	TIPS_TO_MM_SCALE_FACTOR * 200,
	TIPS_TO_MM_SCALE_FACTOR * 201,
	TIPS_TO_MM_SCALE_FACTOR * 202,
	TIPS_TO_MM_SCALE_FACTOR * 203,
	TIPS_TO_MM_SCALE_FACTOR * 204,
	TIPS_TO_MM_SCALE_FACTOR * 205,
	TIPS_TO_MM_SCALE_FACTOR * 206,
	TIPS_TO_MM_SCALE_FACTOR * 207,
	TIPS_TO_MM_SCALE_FACTOR * 208,
	TIPS_TO_MM_SCALE_FACTOR * 209,
	TIPS_TO_MM_SCALE_FACTOR * 210,
	TIPS_TO_MM_SCALE_FACTOR * 211,
	TIPS_TO_MM_SCALE_FACTOR * 212,
	TIPS_TO_MM_SCALE_FACTOR * 213,
	TIPS_TO_MM_SCALE_FACTOR * 214,
	TIPS_TO_MM_SCALE_FACTOR * 215,
	TIPS_TO_MM_SCALE_FACTOR * 216,
	TIPS_TO_MM_SCALE_FACTOR * 217,
	TIPS_TO_MM_SCALE_FACTOR * 218,
	TIPS_TO_MM_SCALE_FACTOR * 219,
	TIPS_TO_MM_SCALE_FACTOR * 220,
	TIPS_TO_MM_SCALE_FACTOR * 221,
	TIPS_TO_MM_SCALE_FACTOR * 222,
	TIPS_TO_MM_SCALE_FACTOR * 223,
	TIPS_TO_MM_SCALE_FACTOR * 224,
	TIPS_TO_MM_SCALE_FACTOR * 225,
	TIPS_TO_MM_SCALE_FACTOR * 226,
	TIPS_TO_MM_SCALE_FACTOR * 227,
	TIPS_TO_MM_SCALE_FACTOR * 228,
	TIPS_TO_MM_SCALE_FACTOR * 229,
	TIPS_TO_MM_SCALE_FACTOR * 230,
	TIPS_TO_MM_SCALE_FACTOR * 231,
	TIPS_TO_MM_SCALE_FACTOR * 232,
	TIPS_TO_MM_SCALE_FACTOR * 233,
	TIPS_TO_MM_SCALE_FACTOR * 234,
	TIPS_TO_MM_SCALE_FACTOR * 235,
	TIPS_TO_MM_SCALE_FACTOR * 236,
	TIPS_TO_MM_SCALE_FACTOR * 237,
	TIPS_TO_MM_SCALE_FACTOR * 238,
	TIPS_TO_MM_SCALE_FACTOR * 239,
	TIPS_TO_MM_SCALE_FACTOR * 240,
	TIPS_TO_MM_SCALE_FACTOR * 241,
	TIPS_TO_MM_SCALE_FACTOR * 242,
	TIPS_TO_MM_SCALE_FACTOR * 243,
	TIPS_TO_MM_SCALE_FACTOR * 244,
	TIPS_TO_MM_SCALE_FACTOR * 245,
	TIPS_TO_MM_SCALE_FACTOR * 246,
	TIPS_TO_MM_SCALE_FACTOR * 247,
	TIPS_TO_MM_SCALE_FACTOR * 248,
	TIPS_TO_MM_SCALE_FACTOR * 249,
	TIPS_TO_MM_SCALE_FACTOR * 250,
	TIPS_TO_MM_SCALE_FACTOR * 251,
	TIPS_TO_MM_SCALE_FACTOR * 252,
	TIPS_TO_MM_SCALE_FACTOR * 253,
	TIPS_TO_MM_SCALE_FACTOR * 254,
	TIPS_TO_MM_SCALE_FACTOR * 255,
	TIPS_TO_MM_SCALE_FACTOR * 256,
	TIPS_TO_MM_SCALE_FACTOR * 257,
	TIPS_TO_MM_SCALE_FACTOR * 258,
	TIPS_TO_MM_SCALE_FACTOR * 259,
	TIPS_TO_MM_SCALE_FACTOR * 260,
	TIPS_TO_MM_SCALE_FACTOR * 261,
	TIPS_TO_MM_SCALE_FACTOR * 262,
	TIPS_TO_MM_SCALE_FACTOR * 263,
	TIPS_TO_MM_SCALE_FACTOR * 264,
	TIPS_TO_MM_SCALE_FACTOR * 265,
	TIPS_TO_MM_SCALE_FACTOR * 266,
	TIPS_TO_MM_SCALE_FACTOR * 267,
	TIPS_TO_MM_SCALE_FACTOR * 268,
	TIPS_TO_MM_SCALE_FACTOR * 269,
	TIPS_TO_MM_SCALE_FACTOR * 270,
	TIPS_TO_MM_SCALE_FACTOR * 271,
	TIPS_TO_MM_SCALE_FACTOR * 272,
	TIPS_TO_MM_SCALE_FACTOR * 273,
	TIPS_TO_MM_SCALE_FACTOR * 274,
	TIPS_TO_MM_SCALE_FACTOR * 275,
	TIPS_TO_MM_SCALE_FACTOR * 276,
	TIPS_TO_MM_SCALE_FACTOR * 277,
	TIPS_TO_MM_SCALE_FACTOR * 278,
	TIPS_TO_MM_SCALE_FACTOR * 279,
	TIPS_TO_MM_SCALE_FACTOR * 280,
	TIPS_TO_MM_SCALE_FACTOR * 281,
	TIPS_TO_MM_SCALE_FACTOR * 282,
	TIPS_TO_MM_SCALE_FACTOR * 283,
	TIPS_TO_MM_SCALE_FACTOR * 284,
	TIPS_TO_MM_SCALE_FACTOR * 285,
	TIPS_TO_MM_SCALE_FACTOR * 286,
	TIPS_TO_MM_SCALE_FACTOR * 287,
	TIPS_TO_MM_SCALE_FACTOR * 288,
	TIPS_TO_MM_SCALE_FACTOR * 289,
	TIPS_TO_MM_SCALE_FACTOR * 290,
	TIPS_TO_MM_SCALE_FACTOR * 291,
	TIPS_TO_MM_SCALE_FACTOR * 292,
	TIPS_TO_MM_SCALE_FACTOR * 293,
	TIPS_TO_MM_SCALE_FACTOR * 294,
	TIPS_TO_MM_SCALE_FACTOR * 295,
	TIPS_TO_MM_SCALE_FACTOR * 296,
	TIPS_TO_MM_SCALE_FACTOR * 297,
	TIPS_TO_MM_SCALE_FACTOR * 298,
	TIPS_TO_MM_SCALE_FACTOR * 299,
	TIPS_TO_MM_SCALE_FACTOR * 300,
	TIPS_TO_MM_SCALE_FACTOR * 301,
	TIPS_TO_MM_SCALE_FACTOR * 302,
	TIPS_TO_MM_SCALE_FACTOR * 303,
	TIPS_TO_MM_SCALE_FACTOR * 304,
	TIPS_TO_MM_SCALE_FACTOR * 305,
	TIPS_TO_MM_SCALE_FACTOR * 306,
	TIPS_TO_MM_SCALE_FACTOR * 307,
	TIPS_TO_MM_SCALE_FACTOR * 308,
	TIPS_TO_MM_SCALE_FACTOR * 309,
	TIPS_TO_MM_SCALE_FACTOR * 310,
	TIPS_TO_MM_SCALE_FACTOR * 311,
	TIPS_TO_MM_SCALE_FACTOR * 312,
	TIPS_TO_MM_SCALE_FACTOR * 313,
	TIPS_TO_MM_SCALE_FACTOR * 314,
	TIPS_TO_MM_SCALE_FACTOR * 315,
	TIPS_TO_MM_SCALE_FACTOR * 316,
	TIPS_TO_MM_SCALE_FACTOR * 317,
	TIPS_TO_MM_SCALE_FACTOR * 318,
	TIPS_TO_MM_SCALE_FACTOR * 319,
	TIPS_TO_MM_SCALE_FACTOR * 320,
	TIPS_TO_MM_SCALE_FACTOR * 321,
	TIPS_TO_MM_SCALE_FACTOR * 322,
	TIPS_TO_MM_SCALE_FACTOR * 323,
	TIPS_TO_MM_SCALE_FACTOR * 324,
	TIPS_TO_MM_SCALE_FACTOR * 325,
	TIPS_TO_MM_SCALE_FACTOR * 326,
	TIPS_TO_MM_SCALE_FACTOR * 327,
	TIPS_TO_MM_SCALE_FACTOR * 328,
	TIPS_TO_MM_SCALE_FACTOR * 329,
	TIPS_TO_MM_SCALE_FACTOR * 330,
	TIPS_TO_MM_SCALE_FACTOR * 331,
	TIPS_TO_MM_SCALE_FACTOR * 332,
	TIPS_TO_MM_SCALE_FACTOR * 333,
	TIPS_TO_MM_SCALE_FACTOR * 334,
	TIPS_TO_MM_SCALE_FACTOR * 335,
	TIPS_TO_MM_SCALE_FACTOR * 336,
	TIPS_TO_MM_SCALE_FACTOR * 337,
	TIPS_TO_MM_SCALE_FACTOR * 338,
	TIPS_TO_MM_SCALE_FACTOR * 339,
	TIPS_TO_MM_SCALE_FACTOR * 340,
	TIPS_TO_MM_SCALE_FACTOR * 341,
	TIPS_TO_MM_SCALE_FACTOR * 342,
	TIPS_TO_MM_SCALE_FACTOR * 343,
	TIPS_TO_MM_SCALE_FACTOR * 344,
	TIPS_TO_MM_SCALE_FACTOR * 345,
	TIPS_TO_MM_SCALE_FACTOR * 346,
	TIPS_TO_MM_SCALE_FACTOR * 347,
	TIPS_TO_MM_SCALE_FACTOR * 348,
	TIPS_TO_MM_SCALE_FACTOR * 349,
	TIPS_TO_MM_SCALE_FACTOR * 350,
	TIPS_TO_MM_SCALE_FACTOR * 351,
	TIPS_TO_MM_SCALE_FACTOR * 352,
	TIPS_TO_MM_SCALE_FACTOR * 353,
	TIPS_TO_MM_SCALE_FACTOR * 354,
	TIPS_TO_MM_SCALE_FACTOR * 355,
	TIPS_TO_MM_SCALE_FACTOR * 356,
	TIPS_TO_MM_SCALE_FACTOR * 357,
	TIPS_TO_MM_SCALE_FACTOR * 358,
	TIPS_TO_MM_SCALE_FACTOR * 359,
	TIPS_TO_MM_SCALE_FACTOR * 360,
	TIPS_TO_MM_SCALE_FACTOR * 361,
	TIPS_TO_MM_SCALE_FACTOR * 362,
	TIPS_TO_MM_SCALE_FACTOR * 363,
	TIPS_TO_MM_SCALE_FACTOR * 364,
	TIPS_TO_MM_SCALE_FACTOR * 365,
	TIPS_TO_MM_SCALE_FACTOR * 366,
	TIPS_TO_MM_SCALE_FACTOR * 367,
	TIPS_TO_MM_SCALE_FACTOR * 368,
	TIPS_TO_MM_SCALE_FACTOR * 369,
	TIPS_TO_MM_SCALE_FACTOR * 370,
	TIPS_TO_MM_SCALE_FACTOR * 371,
	TIPS_TO_MM_SCALE_FACTOR * 372,
	TIPS_TO_MM_SCALE_FACTOR * 373,
	TIPS_TO_MM_SCALE_FACTOR * 374,
	TIPS_TO_MM_SCALE_FACTOR * 375,
	TIPS_TO_MM_SCALE_FACTOR * 376,
	TIPS_TO_MM_SCALE_FACTOR * 377,
	TIPS_TO_MM_SCALE_FACTOR * 378,
	TIPS_TO_MM_SCALE_FACTOR * 379,
	TIPS_TO_MM_SCALE_FACTOR * 380,
	TIPS_TO_MM_SCALE_FACTOR * 381,
	TIPS_TO_MM_SCALE_FACTOR * 382,
	TIPS_TO_MM_SCALE_FACTOR * 383,
	TIPS_TO_MM_SCALE_FACTOR * 384,
	TIPS_TO_MM_SCALE_FACTOR * 385,
	TIPS_TO_MM_SCALE_FACTOR * 386,
	TIPS_TO_MM_SCALE_FACTOR * 387,
	TIPS_TO_MM_SCALE_FACTOR * 388,
	TIPS_TO_MM_SCALE_FACTOR * 389,
	TIPS_TO_MM_SCALE_FACTOR * 390,
	TIPS_TO_MM_SCALE_FACTOR * 391,
	TIPS_TO_MM_SCALE_FACTOR * 392,
	TIPS_TO_MM_SCALE_FACTOR * 393,
	TIPS_TO_MM_SCALE_FACTOR * 394,
	TIPS_TO_MM_SCALE_FACTOR * 395,
	TIPS_TO_MM_SCALE_FACTOR * 396,
	TIPS_TO_MM_SCALE_FACTOR * 397,
	TIPS_TO_MM_SCALE_FACTOR * 398,
	TIPS_TO_MM_SCALE_FACTOR * 399
};

#endif