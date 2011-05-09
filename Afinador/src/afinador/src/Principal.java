package afinador.src;

import javax.swing.JFrame;

public class Principal {
	private static final int TAMANO_BUFFER=44100;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		byte [] buffer=new byte[TAMANO_BUFFER];
		Captura captura = new Captura(buffer);
		//captura.capturar();
		JFrame f = new JFrame();
		f.setContentPane(new InterfazGrafica(captura, null));
		f.pack();
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.setVisible(true);
	}

}
