package afinador.src;

import javax.sound.sampled.*;

public class Captura extends Thread {

	private final static int SOLAPAMIENTOS=16;
	public static final int NUMERO_DE_MUESTRAS = SOLAPAMIENTOS * 1024;
	private byte[] tiempo; // Buffer de datos de audio en el dominio del tiempo
	private double[][] frecuencia; // Buffer de datos de audio en el dominio del
									// tiempo
	private double[] enventanado;
	private AudioFormat audioFormat; // Formato de audio de entrada
	private Mixer.Info[] mixerInfo; // Lista de mezcladores disponibles
	private Mixer mezclador; // Mezclador
	private DataLine.Info linea; // Linea de entrada de captura
	private TargetDataLine tarjetaSonido; // Puente entre la zona de memoria
	private boolean stopCapture;
	

	// donde escribe la tarjeta de
	// sonido y memoria principal
	// manejable por nosotros

	public Captura() {
		formatoAudioPorDefecto();
		tiempo = new byte[NUMERO_DE_MUESTRAS * audioFormat.getChannels()
				* (audioFormat.getSampleSizeInBits() / 8)];
		frecuencia = new double[2][NUMERO_DE_MUESTRAS];
		enventanado = new double[NUMERO_DE_MUESTRAS];
		
		/*
		 * Peticion al sistema de audio para obtener un listado de mezcladores
		 * disponibles
		 */
		mixerInfo = AudioSystem.getMixerInfo();
		linea = new DataLine.Info(TargetDataLine.class, audioFormat);
		Window.computeCoefficients(1, enventanado);	//Ventana temporal de tipo 1 (Hamming)
		inicializarCaptura();

	}

	// donde escribe la tarjeta de
	// sonido y memoria principal
	// manejable por nosotros

	public Captura(byte[] buffer) {
		this.tiempo = buffer;
		/*
		 * Peticion al sistema de audio para obtener un listado de mezcladores
		 * disponibles
		 */
		mixerInfo = AudioSystem.getMixerInfo();
		formatoAudioPorDefecto();
		linea = new DataLine.Info(TargetDataLine.class, audioFormat);
		inicializarCaptura();
	}

	public double[][] getFrecuencia() {
		return frecuencia;
	}

	public void setFrecuencia(double[][] frecuencia) {
		this.frecuencia = frecuencia;
	}

	public void setBuffer(byte[] buffer) {
		this.tiempo = buffer;
	}

	public byte[] getBuffer() {
		return tiempo;
	}

	public void run() {
		/* Variable para dejar de capturar */
		long time = 0;
		byte[]buffer = new byte[tiempo.length/SOLAPAMIENTOS];
		stopCapture = false;
		try {
			tarjetaSonido.read(tiempo, 0,	tiempo.length);
			while (!stopCapture) {
				
				int cnt = tarjetaSonido.read(buffer, 0, buffer.length);
				
				System.arraycopy(tiempo, buffer.length, tiempo, 0, tiempo.length-buffer.length);
				System.arraycopy(buffer, 0, tiempo, tiempo.length-buffer.length, buffer.length);
				
				ConversorTF.convertir(tiempo, frecuencia, enventanado);
			}
			tarjetaSonido.stop();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(0);
		}
	}

	private void formatoAudioPorDefecto() {
		float frecuenciaMuestreo = 8000;
		// 8000,11025,16000,22050,44100
		int tamanoMuestraBits = 16;
		// 8,16
		int canales = 2;
		// 1,2
		boolean signo = true;
		// true,false
		boolean bigEndian = false;
		// true,false
		audioFormat = new AudioFormat(frecuenciaMuestreo, tamanoMuestraBits,
				canales, signo, bigEndian);

	}

	public void setAudioFormat(AudioFormat audioFormat) {
		this.audioFormat = audioFormat;
	}

	public AudioFormat getAudioFormat() {
		return audioFormat;
	}

	public void capturar() {
		tarjetaSonido.start();
		this.start();
	}

	private void inicializarCaptura() {
		/* Construccion de una linea de datos con el formato de audio deseado */
		linea = new DataLine.Info(TargetDataLine.class, audioFormat);

		try {
			/* Bucle para buscar un mezclador compatible con la linea de datos */
			for (int i = 0; i < mixerInfo.length; i++) {
				mezclador = AudioSystem.getMixer(mixerInfo[i]);
				if (mezclador.isLineSupported(linea)) {
					break;
				}

			}

			tarjetaSonido = (TargetDataLine) mezclador.getLine(linea);

			// Prepare the line for use.
			tarjetaSonido.open(audioFormat);

			// Create a thread to capture the microphone
			// data and start it running. It will run
			// until the Stop button is clicked.
		} catch (LineUnavailableException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public Mixer[] getEntradas() {
		Mixer[] aux;
		int nMezcladoresSoportados = 0;
		/* Bucle para buscar un mezclador compatible con la linea de datos */
		for (int i = 0; i < mixerInfo.length; i++) {
			if (AudioSystem.getMixer(mixerInfo[i]).isLineSupported(linea)) {
				nMezcladoresSoportados++;
			}
		}
		aux = new Mixer[nMezcladoresSoportados];
		nMezcladoresSoportados = 0;
		for (int i = 0; i < mixerInfo.length; i++) {
			if (AudioSystem.getMixer(mixerInfo[i]).isLineSupported(linea)) {
				aux[nMezcladoresSoportados++] = AudioSystem
						.getMixer(mixerInfo[i]);
			}
		}
		return aux;
	}

	public Mixer.Info[] getMixerInfo() {
		return mixerInfo;
	}

	public void setMixerInfo(Mixer.Info[] mixerInfo) {
		this.mixerInfo = mixerInfo;
	}

	public Mixer getMezclador() {
		return mezclador;
	}

	public void setMezclador(Mixer mezclador) {
		this.mezclador = mezclador;
	}

	public DataLine.Info getLinea() {
		return linea;
	}

	public void setLinea(DataLine.Info linea) {
		this.linea = linea;
	}

	public TargetDataLine getTarjetaSonido() {
		return tarjetaSonido;
	}

	public void setTarjetaSonido(TargetDataLine tarjetaSonido) {
		this.tarjetaSonido = tarjetaSonido;
	}

	public boolean isStopCapture() {
		return stopCapture;
	}

	public void setStopCapture(boolean stopCapture) {
		this.stopCapture = stopCapture;
	}

	public void buscarMezclador(String nombre) {
		try {
			for (int i = 0; i < mixerInfo.length; i++) {
				if (mixerInfo[i].getName().equals(nombre)) {
					this.mezclador = AudioSystem.getMixer(mixerInfo[i]);

					tarjetaSonido = (TargetDataLine) mezclador.getLine(linea);

					tarjetaSonido.open(audioFormat);
				}

			}
		} catch (LineUnavailableException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
