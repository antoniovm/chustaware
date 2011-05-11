package afinador.src;



public class ConversorTF{
	//Esta clase convertira los datos del array del dominio del tiempo al dominio de la frecuencia
	

	
	public static void convertir(byte [] tiempo, double [] freq) {
		double[][] buffer = new double[tiempo.length][2];

		for (int i = 0; i < 5000; i++) {
			// System.err.print(".");
			/* Parte real, muestra izquierda. */
			buffer[i][0] = (double) (tiempo[4 * i + 1] * 256 + tiempo[4 * i]);
			/* Parte imaginaria, muestra izquierda. */
			buffer[i][1] = 0.0;
		}

		/* Transformada de Fourier del canal izquierdo. */
		FFT.direct(buffer);
		
		/*Modulo espectral*/
		for(int i=0; i<44100; i++) {
			freq[i]= Math.sqrt(buffer[i][0]*buffer[i][0]+buffer[i][1]*buffer[i][1]);
		}
		

	}
}
