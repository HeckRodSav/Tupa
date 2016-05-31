// Classes.h

#ifndef _CLASSES_h
#define _CLASSES_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <Wire.h>


class Helpful
{
private:
	unsigned long conEach = 0;
	unsigned long timerEach = 0;
	unsigned long lapseT = 0;
	unsigned long T0 = 0;
	bool one = 0;
	long count = 0;
public:
	bool mem;
	void begin();
	long counter();
	long getCount();
	bool eachN(unsigned int N);
	bool eachT(float T);
	float lapse();
	float sinceBegin();
	bool oneTime();
	void oneTimeReset();
};

class MediaMovel
{
public:	//Inicializadores
	MediaMovel(int n);
private:
	const unsigned int N;
	float* Vals = new float[N];
	float media, max = 0, min;
public:
	float addValor(float valor);
	float getMedia();
	float getMax();
	float getMin();
	operator float();
};

class Baro  //BMP085
{
public:	//Inicializadores
	Baro(float Tzero = 1);
private:
	const long recalibrateT;
	const int BMP085_Address = 0x77;
	const int OSS = 0;	//Oversampling Setting

	unsigned int ut = 0;
	unsigned long up = 0;

	int b1, b2;
	long b3, b6, p;
	long b5;
	unsigned long b4, b7;
	long x1, x2, x3;
	unsigned char msb, lsb, xlsb;

	int ac1, ac2, ac3;	//Calibration values
	unsigned int ac4, ac5, ac6;
	int mb, mc, md;

	float celcius, meters, base = 0;//Bmp
	long pascal;

	unsigned long thisReadT = 0;
	unsigned long lastReadT = 0;
	unsigned long lastWorkT = 0;
	bool state = 1;

	char ReadChar(unsigned char address);
	int ReadInt(unsigned char address);
	float readTemperature();
	long readPressure();
	float readAltitude(float sealevelP = 101325);
public:
	void begin();
	long getTimeLapse();
	bool readAll(float sealevelP = 101325);
	float readZero(unsigned int I);
	long readSealevel(float altitude);
	float getZero();
	float getTemperature();
	long getPressure();
	float getAltitude(int Base);
	float getAltitude();
	operator bool();
};

class Mag //HMC5883
{
public: //Inicializadores
	Mag(float Tzero = 1);
private:
	const long recalibrateT;
	const uint8_t HMC5883_Address = 0x1E;
	const int Mag_Xmsb = 0x03;
	float X, Y, Z;
	unsigned long thisReadT = 0;
	unsigned long lastReadT = 0;
	unsigned long lastWorkT = 0;
	bool state = 1;
public:
	void begin();
	long getTimeLapse();
	bool readAll();
	float getX();
	float getY();
	float getZ();
	operator bool();
};

class Giro  //L3G4200D
{
public: //Inicializadores
	Giro(int sc, float Tzero = 1);
private:
	const long scale, recalibrateT;
	const uint8_t L3G4200D_Address = 0x69;
	const uint8_t Gyro_Xlsb = 0x28;
	const uint8_t CTRL_REG1 = 0x20;
	const uint8_t CTRL_REG2 = 0x21;
	const uint8_t CTRL_REG3 = 0x22;
	const uint8_t CTRL_REG4 = 0x23;
	const uint8_t CTRL_REG5 = 0x24;
	float X, Y, Z;
	unsigned long thisReadT = 0;
	unsigned long lastReadT = 0;
	unsigned long lastWorkT = 0;
	bool state = 1;
public:
	void begin();
	long getTimeLapse();
	bool readAll();
	float getX();
	float getY();
	float getZ();
	operator bool();
};

class Acel  //ADXL345
{
public:  //Inicializadores
	Acel(float Tzero = 1);
private:
	const long recalibrateT;
	const uint8_t ADXL345_Address = 0x53;
	const uint8_t Acel_Xlsb = 0x32;
	const uint8_t Register_ID = 0;
	const uint8_t Register_2D = 0x2D;
	const uint8_t Register_31 = 0x31;
	float X, Y, Z;
	unsigned long thisReadT = 0;
	unsigned long lastReadT = 0;
	unsigned long lastWorkT = 0;
	bool state = 0;
public:
	void begin();
	long getTimeLapse();
	bool readAll();
	float getX();
	float getY();
	float getZ();
	operator bool();
};

class Apogeu
{
public:
	Apogeu(unsigned int n, unsigned int r, float s);
private:
	const unsigned int N, R, Rl1;
	const float S;
	float Rf;

	bool Alpha = 0;
	bool Beta = 0;
	bool Gamma = 0;
	float Sigma = 0;

	long  apgTm = 0;
	float apgPt = 0;
	float maxH = 0;
	float minH = 0;
	long TimeZero = 0;
	bool apg_A = 0;
	bool *cond = new bool[Rl1];
	float* Alt = new float[N];
	float* altMed = new float[Rl1];
public:
	void resetTimer();
	float addAltitude(float H);
	void setOmega(bool apgE);

	bool apgAlpha();
	bool apgBeta();
	bool apgGamma();
	float apgSigma(bool serial = 0);

	bool getApogeu(float percent = 0.9f, bool type = 1);
	bool getAlpha();
	bool getBeta();
	bool getGamma();
	float getSigma();

	float getAltutude();
	float getApgPt();
	float getApgTm();
	float getMaxH();
	float getMinH();
};

class DuDeploy
{
public:
	DuDeploy(unsigned int paraPin1, unsigned int paraPin2, unsigned int infPin1, unsigned int infPin2, float ignT, float delay);

private:
	const unsigned int P1, P2;	//Pinos de comando
	const unsigned int I1, I2;	//Pinos de verifica��o
	const unsigned long Tign;	//Tempo de comando ativo
	const unsigned long Delay;	//Tempo de atraso dentre comando ( caso altura n�o determinada)
	unsigned long P1T = 0, P2T = 0;	//Momento que o ignitor ligou
	unsigned long TimeZero = 0;	//Momento zero
	unsigned long Tmax = 0;	//Tempo m�ximo para segunran�a
	unsigned long Tnow = 0;	//Tempo atual (com zeragem)
	float P1H = 0, P2H = 0;	//Altura de comando
	bool P1S = 0, P2S = 0;
	bool P1S_A = 0, P2S_A = 0;	//Estado atual do comando
	bool P1H_A = 0, P2H_A = 0;	//Condicional para comando em altura
	bool apogee = 0;	//Representante interno do apogeu
	bool TmaxAux = 0;	//Condicional para verificar tempo de seguran�a
	bool P1T_A = 0, P2T_A = 0;	//Condicional para momento do ignitor
	bool P1seal = 0, P2seal = 0;	//Selo de comando
	bool emer = 0, P1H_Am = 0, P2H_Am = 0;
public:
	void resetTimer();
	bool info1();	//Retorna informa��o sobre estado do ignitor de acionamento 1
	bool info2();//Retorna informa��o sobre estado do ignitor de acionamento 2
	bool begin();
	void setTmax(float Time);
	void setP1height(float H);
	void setP2height(float H);
	void sealApogee(bool apg);
	bool getApogee();
	bool getP1S(bool type = 1);
	bool getP2S(bool type = 1);
	bool getSysState(bool type = 1);
	void refresh(float height);
	void emergency(bool state = 1);
};

#endif

