package afinador.src;



public class ConversorTF{
	//Esta clase convertira los datos del array del dominio del tiempo al dominio de la frecuencia
	

	
	public static void convertir(byte [] tiempo, double [] freq, int nMuestras) {
		double[][] buffer = new double[freq.length][2];

		for (int i = 0; i < nMuestras/2-1; i++) {
			// System.err.print(".");
			/* Parte real, muestra izquierda. */
			buffer[i][0] = (double) (tiempo[2 * i + 1] * 256 + tiempo[2 * i]);
			/* Parte imaginaria, muestra izquierda. */
			buffer[i][1] = 0.0;
		}

		/* Transformada de Fourier del canal izquierdo. */
		FFT.direct(buffer);
		
		/*Modulo espectral*/
		for(int i=0; i<nMuestras; i++) {
			freq[i]= Math.sqrt(buffer[i][0]*buffer[i][0]+buffer[i][1]*buffer[i][1]);
		}
		

	}
}
