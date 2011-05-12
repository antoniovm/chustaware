package afinador.src;


public class Principal {


	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		Afinador afinador=new Afinador();
		InterfazGrafica ig=new InterfazGrafica(afinador);
		afinador.start();
		ig.pintar();
		
	}

}
