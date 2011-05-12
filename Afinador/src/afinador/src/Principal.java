package afinador.src;

import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class Principal {
	private static final int TAMANO_BUFFER=44100;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		byte [] buffer=new byte[TAMANO_BUFFER];
		
		Afinador afinador=new Afinador();
		//captura.capturar();
		InterfazGrafica ig=new InterfazGrafica(afinador);
		afinador.afinarPitch();
		
	}

}
