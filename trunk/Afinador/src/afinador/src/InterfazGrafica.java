package afinador.src;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.UIManager;

public class InterfazGrafica extends JPanel implements ActionListener {
	private Afinador afinador;	//Para mostrar los valores que se manejan en esta clase
	private Captura captura;	//Para configurar los parametros de entrada de audio
	private JComboBox mezcladores;
	private JButton bAceptar;
	private boolean inicio;
	private JFrame ventana;
	private JDialog ventanaInicio;
	private Bombilla[]bombillas;
	private Slider slider;
	private Display display;
	private GridBagConstraints constraints;
	
	public InterfazGrafica(Afinador afinador) {
		setLayout(new GridBagLayout());
		constraints = new GridBagConstraints();
		this.afinador = afinador;
		this.captura = afinador.getCaptura();
		inicio = true;
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e) {e.printStackTrace();}
		inicializarSlider();
		inicializarDisplay();
		inicializarBombillas();
		inicializarFrame();
		inicializarDialog();
	}
	
	private void inicializarSlider() {
		slider = new Slider();
		constraints.gridx = 0;
		constraints.gridy = 0;
		constraints.gridwidth = 6;
		constraints.anchor = GridBagConstraints.CENTER;
		this.add(slider, constraints);
	}
	
	private void inicializarDisplay() {
		display = new Display();
		constraints.gridx = 0;
		constraints.gridy = 1;
		constraints.gridwidth = 6;
		this.add(display, constraints);
	}
	
	private void inicializarBombillas() {
		bombillas = new Bombilla[6];
		constraints.gridx = 0;
		constraints.gridy = 3;
		constraints.gridwidth = 1;
		constraints.weightx = 1.0;
		
		for (int i = 0; i < 6; i++) {
			bombillas[i] = new Bombilla(i);
			constraints.gridx = i;
			this.add(bombillas[i], constraints);
		}
	}
	
	private void inicializarDialog() {
		Dimension dPantalla, dVentana;
		JPanel p = new JPanel();
		ventanaInicio = new JDialog(ventana, "Seleccione un mezclador", true);
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
		
		ventanaInicio.setResizable(false);
		ventanaInicio.pack();
        dPantalla = Toolkit.getDefaultToolkit().getScreenSize(); // Dimensiones en pixels de la pantalla.
        dVentana = ventanaInicio.getSize(); // Dimensiones en pixels de la ventana.
        // Situamos la ventana en el centro de la pantalla.
        ventanaInicio.setLocation((dPantalla.width - dVentana.width) / 2, (dPantalla.height - dVentana.height) / 2);
		ventanaInicio.setVisible(true);
		ventanaInicio.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		
	}

	private void inicializarFrame() {
		Dimension dPantalla, dVentana;
		ventana = new JFrame();
		ventana.add(this);
		ventana.pack();
		dPantalla = Toolkit.getDefaultToolkit().getScreenSize(); // Dimensiones en pixels de la pantalla.
        dVentana = ventana.getSize(); // Dimensiones en pixels de la ventana.
        // Situamos la ventana en el centro de la pantalla.
        ventana.setLocation((dPantalla.width - dVentana.width) / 2, (dPantalla.height - dVentana.height) / 2);
		ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ventana.setVisible(true);
		
	}
	
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Color color1 = new Color(12,74,88);
		Color color2 = new Color(51,141,209);
		GradientPaint gr = new GradientPaint(0, 0, color1, 0, getHeight(), color2);
		((Graphics2D)g).setPaint(gr);
		((Graphics2D)g).fillRect(0, 0, getWidth(), getHeight());
	}
	
	public void paint(Graphics g) {
		super.paint(g);
		// Si no estamos en la pantalla inicial, pintamos las luces, etc
		if(!inicio) {
			
		}
		/*GradientPaint gr = new GradientPaint(0, 0, Color.black, 0, getHeight(), Color.white);
		((Graphics2D)g).setPaint(gr);
		((Graphics2D)g).fillRect(0, 0, getWidth(), getHeight());*/
	}
}
