package afinador.src;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.sound.sampled.Mixer;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class InterfazGrafica extends JPanel implements ActionListener {
	private Afinador afinador;	//Para mostrar los valores que se manejan en esta clase
	private Captura captura;	//Para configurar los parametros de entrada de audio
	private JComboBox mezcladores;
	private JLabel lNota;
	private JButton bAceptar;
	private boolean inicio;
	private JFrame ventana;
	private JDialog ventanaInicio;
	
	public InterfazGrafica(Afinador afinador) {
		this.afinador = afinador;
		this.captura = afinador.getCaptura();
		inicio = true;
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e) {e.printStackTrace();}
		inicializarPPrincipal();
		inicializarFrame();
		inicializarDialog();
		
	}
	
	private void inicializarDialog() {
		Dimension dPantalla, dVentana;
		JPanel p = new JPanel();
		ventanaInicio = new JDialog(ventana, true);
		mezcladores = new JComboBox();
		bAceptar = new JButton("Aceptar");
		
		for (int i = 0; i < captura.getEntradas().length; i++) {
			mezcladores.addItem(captura.getEntradas()[i].getMixerInfo().getName());
		}
		bAceptar.addActionListener(new ActionListener() {
			
			public void actionPerformed(ActionEvent e) {
				captura.buscarMezclador((String) mezcladores.getSelectedItem());
				ventanaInicio.dispose();
			}
		});
		
		p.add(mezcladores);
		p.add(bAceptar);
		ventanaInicio.add(p);
		
		ventanaInicio.pack();
        dPantalla = Toolkit.getDefaultToolkit().getScreenSize(); // Dimensiones en pixels de la pantalla.
        dVentana = ventanaInicio.getSize(); // Dimensiones en pixels de la ventana.
        // Situamos la ventana en el centro de la pantalla.
        ventanaInicio.setLocation((dPantalla.width - dVentana.width) / 2, (dPantalla.height - dVentana.height) / 2);
		ventanaInicio.setVisible(true);
		ventanaInicio.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		
	}

	private void inicializarFrame() {
		ventana = new JFrame();
		ventana.setContentPane(this);
		ventana.pack();
		ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ventana.setVisible(true);
		
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
