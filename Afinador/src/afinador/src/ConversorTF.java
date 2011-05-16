package afinador.src;



public class ConversorTF{
	//Esta clase convertira los datos del array del dominio del tiempo al dominio de la frecuencia
	

	
	public static void convertir(byte [] tiempo, double [][] freq, double [] ventana) {
		double[][] bufferL = new double[freq[0].length][2];
		double[][] bufferR = new double[freq[1].length][2];

		for (int i = 0; i < freq[0].length/2-1; i++) {
			// System.err.print(".");
			/* Parte real, muestra izquierda. */
			bufferL[i][0] = (double) (tiempo[4 * i + 1] * 256 + tiempo[4 * i])*ventana[i];
			/* Parte imaginaria, muestra izquierda. */
			bufferL[i][1] = 0.0;
			
			/* Parte real, muestra derecha. */
			bufferR[i][0] = (double) (tiempo[4 * i + 3] * 256 + tiempo[4 * i + 2])*ventana[i];
			/* Parte imaginaria, muestra derecha. */
			bufferR[i][1] = 0.0;
		}

		/* Transformada de Fourier del canal izquierdo. */
		FFT.direct(bufferL);
		/* Transformada de Fourier del canal derecho. */
		FFT.direct(bufferR);
		
		/*Modulo espectral*/
		for(int i=0; i<freq[0].length; i++) {
			freq[0][i]= Math.sqrt(bufferL[i][0]*bufferL[i][0]+bufferL[i][1]*bufferL[i][1]);
			freq[1][i]= Math.sqrt(bufferR[i][0]*bufferR[i][0]+bufferR[i][1]*bufferR[i][1]);
		}
		

	}
}
