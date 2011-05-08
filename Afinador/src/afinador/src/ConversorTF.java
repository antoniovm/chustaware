package afinador.src;



public class ConversorTF extends Thread{
	//Esta clase convertira los datos del array del dominio del tiempo al dominio de la frecuencia
	
	byte [] tiempo, freq;
	
	public ConversorTF(byte [] tiempo, byte [] freq) {
		this.tiempo=tiempo;
		this.freq=freq;
	}
	
	private void convertir() {
		double[][] buffer = new double[tiempo.length][2];

		for (int i = 0; i < tiempo.length; i++) {
			// System.err.print(".");
			/* Parte real, muestra izquierda. */
			buffer[i][0] = (double) (tiempo[4 * i + 1] * 256 + tiempo[4 * i]);
			/* Parte imaginaria, muestra izquierda. */
			buffer[i][1] = 0.0;
		}

		/* Transformada de Fourier del canal izquierdo. */
		FFT.direct(buffer);
		

	}
}
