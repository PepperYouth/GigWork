#include "head.h"
int TestPrime[302] = { 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 
37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 
103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 
167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 
307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373,
379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 
449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673,
677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757,
761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 
853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929,
937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013,
1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 
1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 
1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 
1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373,
1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 
1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583,
1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 
1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 
1741, 1747, 1753, 1759, 1777, 1783, 1787 ,1789, 1801, 1811,
1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889,
1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999, };
int BitTest[8] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80 };
int RealRand(int range) {
	srand((unsigned)time(0) + rand());
	srand((unsigned)time(0)%10 + rand());
	range = rand() % (range + 1);
	return range;
}
_u8 *Ini(int Len) {
	_u8 *X = (_u8*)malloc(sizeof(_u8));
	X->len = Len;
	X->data = (unsigned char*)malloc(Len * sizeof(unsigned char));
	return X;
}
int Print(_u8 *X) {
	for (int i = 0; i < X->len; i++)
		printf("%d ", X->data[i]);
	putchar('\n');
	return 0;
}
int DelZero(_u8 *X) {
	for (int i = X->len-1; i >= 0; i--) {
		if (X->data[i] == 0)
			X->len--;
		else
			return 0;
	}
}
int NoEqualOne(_u8 *X) {
	if (X->data[0] == 1)
		for (int i = 1; i < X->len; i++)
			if (X->data[i])
				return 1;
	return 0;
}
int NoEqualN_1(_u8 *X, _u8 *N) {
	N->data[0]--;
	for (int i = 0; i < N->len; i++) {
		if (X->data[i] != N->data[i])
			return 1;
	}
	N->data[0]++;
	return 0;
}

_u8 *Odd(int range) {
	_u8 *X = Ini(range);
	X->data[0] = RealRand(127) * 2 + 1;
	for (int i = 1; i < X->len; i++) {
		X->data[i] = RealRand(255);
	}
	return X;
}
int F_P(_u8* X) {
	int rmd;
	for (int j = 0; j < 302; j++) {
		rmd = 0;
		for (int i = X->len - 1; i >= 0; i--)
			rmd = (rmd * 256 + X->data[i]) % TestPrime[j];
		if (rmd == 0) {
			free(X);
			return 1;
		}
	}
	return 0;
}
_u8 *FakePrime() {
	_u8 *X = Odd(32 + RealRand(64));
	while (F_P(X)) {
		X = Odd(32 + RealRand(64));
	}
	return X;
}
_u8 *MR_rand(_u8 *N) {
	_u8 *A = Ini(1 + RealRand(N->len));
	A->data[0] = 1 + RealRand(254);
	for (int i = 1; i < A->len; i++)
		A->data[i] = RealRand(255);
	if (A->len == N->len && A->data[A->len - 1] >= N->data[N->len - 1])
		A->data[A->len - 1] = RealRand(N->data[N->len - 1] - 1);
	return A;
}
int Witness(_u8 *a,_u8 *n) {
	factor *R = RightMove(n);
	_u8 *X = ModExp(a,R->u,n);
	_u8 *Y = Ini(X->len);
	for (int i = 0; i < R->t; i++) {
		Y = Mod(Multiplicate(X, X), n);
		if (!NoEqualOne(Y) && NoEqualOne(X) && NoEqualN_1(X, n))
			return 1;
		DelZero(Y);
		X = Y;
	}
	if (NoEqualOne(Y))
		return 1;
	return 0;
}
int Miler_Rabin(_u8 *n, int s) {
	_u8 *a;
	for (int i = 0; i < s; i++) {
		a = MR_rand(n);
		printf("%d\n",i);
		if (Witness(a, n))
			return 1;
	}
	return 0;
}
_u8 *MRFakePrime(){
	_u8 *X = FakePrime();
	while (Miler_Rabin(X, 19)) {
		X = FakePrime();
	}
	return X;
}

_u8 *Sub(_u8 *A, _u8 *B) {
	//A > B; A - B = R;
	int i, j = 0;
	char flag = 0;
	_u8 *R = Ini(A->len);
	for (i = 0; i < B->len; i++){
		if (A->data[i] < B->data[i] + flag){
			R->data[i] = (256 - B->data[i] - flag) + A->data[i];
			flag = 1;
		}
		else{
			R->data[i] = A->data[i] - B->data[i] - flag;
			flag = 0;
		}
	}
	for (; i < A->len; i++)
		if (A->data[i] < flag){
			R->data[i] = (256 - flag) + A->data[i];
			flag = 1;
		}
		else{
			R->data[i] = A->data[i] - flag;
			flag = 0;
		}
	return R;
}
int Compare(_u8* A, _u8* B)
{
	//if A > B return 1
	//if A == B return 0
	//if A < B return -1
	int i, j;
	//Get the index of biggest bit
	for (i = A->len - 1; i >= 0; i--)
		if (A->data[i] != 0)
			break;
	//Get the index of biggest bit
	for (j = B->len - 1; j >= 0; j--)
		if (B->data[j] != 0)
			break;
	if (i > j)
		return 1;
	else if (i < j)
		return -1;

	for (; j >= 0; j--)
		if (A->data[j] > B->data[j])
			return 1;
		else if (A->data[j] < B->data[j])
			return -1;

	return 0;
}
_u8 *Mod(_u8* A, _u8* B)
{
	//A Mod B
	_u8 *C, *mB, *temp;
	int i, j;
	int Cfirst = A->len - 1, Bfirst = B->len - 1;

	C = Ini(A->len);
	for (i = 0; i < C->len; i++)
		C->data[i] = A->data[i];

	while (C->data[Cfirst--] == 0);
	while (B->data[Bfirst--] == 0);

	Cfirst++, Bfirst++;

	while (Cfirst > Bfirst + 1){
		mB = Ini(Cfirst);
		for (i = 0, j = 0; i < Cfirst; i++){
			if (i < Cfirst - 1 - Bfirst)
				mB->data[i] = 0;
			else{
				mB->data[i] = B->data[j];
				j++;
			}
		}
		temp = mB;
		mB = Mul(mB, C->data[i]);
		free(temp);

		while (Compare(C, mB) != -1){
			temp = Sub(C, mB);
			if (Compare(temp, B) == -1){
				free(temp);
				break;
			}
			else{
				free(C);
				C = temp;
			}
		}
		while (C->data[Cfirst--] == 0);
		Cfirst++;
		free(mB);
	}

	while (Compare(C, B) == 1){
		temp = C;
		C = Sub(C, B);
		free(temp);
	}
	if (Compare(C, B) == 0){
		free(C);
		C = Ini(1);
		C->data[0] = 0;
	}
	return C;
}
_u8 *Multiplicate(_u8 *A, _u8 *B) {
	int r = 0, carry = 0;
	_u8 *R;
	R = Ini(A->len + B->len);
	for (int i = 0; i < R->len; i++)
		R->data[i] = 0;
	for (int i = 0; i < A->len; i++) {
		for (int j = 0; j < B->len; j++) {
			r = R->data[i + j] + A->data[i] * B->data[j];
			carry = r / 256;
			R->data[i + j] = r - carry * 256;
			for (int k = 1; k < R->len - i - j; k++) {
				r = R->data[i + j + k] + carry;
				if (r < 256) {
					R->data[i + j + k] = r;
					break;
				}
				else {
					carry = r / 256;
					R->data[i + j + k] = r - carry * 256;
				}
			}
		}
	}
	return R;
}
_u8 *Mul(_u8* A, unsigned char B)
{
	unsigned char carry = 0;
	unsigned int temp;
	int i;
	_u8 *C = Ini(A->len + 1);
	for (i = 0; i < A->len; i++){
		temp = A->data[i] * B + carry;
		carry = temp / 256;
		C->data[i] = temp % 256;
	}
	C->data[i] = carry;
	return C;
}
factor *RightMove(_u8 *A) {
	int i = 0, j = 0, temp;
	int k = 0, r;
	char copy;
	while(A->data[i++] == 0)
		;
	i--;

	temp = A->data[i];
	while (!(temp & BitTest[j++]))
		;
	j--;
	_u8 *R = Ini(A->len - i);
	r = 8 * i + j;
	for (; i < A->len - 1; i++)
	{
		copy = (A->data[i] >> j) + (A->data[i + 1] << (8 - j));
		R->data[k++] = copy;
	}
	R->data[k] = A->data[i] >> j;
	factor *Rustle = (factor *)malloc(sizeof(factor));
	Rustle->t = r;
	Rustle->u = R;
	return Rustle;
}
_u8 *ModExp(_u8 *a, _u8 *b, _u8 *n) {
	_u8 *d = Ini(n->len);
	int i;
	for (i = 1; i < d->len; i++)
		d->data[i] = 0;
	d->data[0] = 1;
	for (i = b->len -1; i >=0; i--) {
		for (int j = 7; j >= 0; j--) {
			d = Mod(Multiplicate(d, d), n);
			if (b->data[i] & BitTest[j])
				d = Mod(Multiplicate(d, a),n);
			DelZero(d);
		}	
	}
	return d;
}