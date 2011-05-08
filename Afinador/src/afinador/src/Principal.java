package afinador.src;

public class Principal {
	private static final int TAMANO_BUFFER=44100;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		byte [] buffer=new byte[TAMANO_BUFFER];
		Captura captura = new Captura(buffer);
		captura.capturar();

	}

}
