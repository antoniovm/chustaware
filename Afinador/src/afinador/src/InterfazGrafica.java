package afinador.src;

import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;

public class InterfazGrafica extends JPanel implements ActionListener {
	private Afinador afinador;	//Para mostrar los valores que se manejan en esta clase
	private Captura captura;	//Para configurar los parametros de entrada de audio
	private JComboBox mezcladores;
	private JLabel lNota;
	private boolean inicio;
	
	public InterfazGrafica(Captura captura, Afinador afinador) {
		this.captura = captura;
		this.afinador = afinador;
		inicio = true;
		inicializarPInicio();
		inicializarPPrincipal();
		this.add(mezcladores);
	}

	private void inicializarPInicio(){
		mezcladores = new JComboBox();
		for (int i = 0; i < captura.getEntradas().length; i++) {
			mezcladores.addItem(captura.getEntradas()[i].getMixerInfo().getName());
		}
	}
	
	private void inicializarPPrincipal() {
		lNota = new JLabel(); // Nombre de la nota que esta sonando
	}

	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	public void paint(Graphics g) {
		super.paint(g);
		// Si no estamos en la pantalla inicial, pintamos las luces, etc
		if(!inicio) {
			
		}
	}
}
