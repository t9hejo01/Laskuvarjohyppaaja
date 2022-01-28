#include "mbed.h"
#include "L3G4200D.h"

Timer timer;
Serial pc(USBTX,USBRX);
L3G4200D gyro(D14, D15);
int g[3] = {0, 0, 0};
float kulma[3] = {0.0, 0.0, 0.0};

float kx = 0;
float massa = 80;
float korkeus = 3000;
float ivk1 = 1.8882;
//float ivk2 = 92.0102;
float putoamiskiihtyvyys = -9.81;
float pystNopeus = 0;
float aikasumma = 0;
float nopeudenMuutos = -0.4905;
	
int main()
{
	timer.start();
	timer.reset();
	
	while(true)
	{
		float aika = timer.read_ms();
			timer.reset();
			aikasumma += aika;
			
			gyro.read(g);
			
			g[2] = g[2] - 6;
			kx = (kx - g[2] * (aika / 1000) * 0.07);
			
			ivk1 = 1.8882 * (1 +(kx / 90));
			if(ivk1 < 1.8882)
			{
				ivk1 = 1.8882;	
			}
			
			nopeudenMuutos = (putoamiskiihtyvyys*massa-ivk1*pystNopeus)/massa*(aika/1000);
			
			korkeus += pystNopeus*(aika/1000);
			if (korkeus < 0)
			{
				korkeus = 0;
			}
			
			pystNopeus += nopeudenMuutos;
			
			pc.printf("%f ", aikasumma);
			pc.printf("%f ", ivk1);
			pc.printf("%f ", kx);
			pc.printf("%f ", korkeus);
			
		pc.printf("\r\n");
	}
}
	


