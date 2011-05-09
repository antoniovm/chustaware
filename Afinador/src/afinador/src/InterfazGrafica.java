package afinador.src;

import javax.swing.JComboBox;
import javax.swing.JPanel;

public class InterfazGrafica extends JPanel{
	private Afinador afinador;	//Para mostrar los valores que se manejan en esta clase
	private Captura captura;	//Para configurar los parametros de entrada de audio
	private JPanel pInicio;
	private JComboBox mezcladores;
	
	public InterfazGrafica() {
		pInicio = new JPanel();
		mezcladores = new JComboBox();
		for (int i = 0; i < captura.getMixerInfo().length; i++) {
			mezcladores.addItem(captura.getMixerInfo()[i].getName());
		}
		add(mezcladores);
	}
}
