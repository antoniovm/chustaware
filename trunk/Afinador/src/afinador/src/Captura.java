package afinador.src;

import javax.sound.sampled.*;
import javax.sound.sampled.Line.Info;

public class Captura extends Thread {

	private byte[] buffer; // Buffer de datos de audio
	private AudioFormat audioFormat; // Formato de audio de entrada
	private Mixer.Info[] mixerInfo;  //Lista de mezcladores disponibles
	private Mixer mezclador; // Mezclador
	private DataLine.Info linea; // Linea de entrada de captura
	private TargetDataLine tarjetaSonido; // Puente entre la zona de memoria
											// donde escribe la tarjeta de
											// sonido y memoria principal
											// manejable por nosotros

	public Captura(byte[] buffer) {
		this.buffer=buffer;
		/*Peticion al sistema de audio para obtener un listado de mezcladores disponibles*/
		mixerInfo = AudioSystem.getMixerInfo();
	}

	public void setBuffer(byte[] buffer) {
		this.buffer = buffer;
	}

	public byte[] getBuffer() {
		return buffer;
	}

	public synchronized void start() {
		super.start();

	}

	public void formatoAudioPorDefecto() {
		float frecuenciaMuestreo = 44100;
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

	public void inicializarCaptura() {
		try {
			
			
			/*Construccion de una linea de datos con el formato de audio deseado*/
			DataLine.Info dataLineInfo = new DataLine.Info(
					TargetDataLine.class, audioFormat);
			
			
			
			// Select one of the available
			// mixers.
			Mixer mixer = AudioSystem.getMixer(mixerInfo[2]);
			System.out.println(mixer.getLineInfo());
			// Get a TargetDataLine on the selected
			// mixer.

			tarjetaSonido = (TargetDataLine) mixer.getLine(dataLineInfo);

			// Prepare the line for use.
			tarjetaSonido.open(audioFormat);
			tarjetaSonido.start();
			mixer.isLineSupported((Info) tarjetaSonido);
			// Create a thread to capture the microphone
			// data and start it running. It will run
			// until the Stop button is clicked.
		} catch (LineUnavailableException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
