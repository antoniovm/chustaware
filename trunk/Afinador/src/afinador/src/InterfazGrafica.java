package afinador.src;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.io.File;

import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.KeyStroke;
import javax.swing.UIManager;

public class InterfazGrafica extends JPanel implements ActionListener {
	private final static String titulo = "CWTuner";
	private final static String autores = "Jorge Garcia Hinestrosa\nSergio Revueltas Estrada\nMiguel Vicente Linares\nAntonio Vicente Martin";
	private final static ImageIcon pua = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"puaCW.png");
	private Afinador afinador;	//Para mostrar los valores que se manejan en esta clase
	private Captura captura;	//Para configurar los parametros de entrada de audio
	private JComboBox mezcladores;
	private JButton bAceptar;
	private boolean inicio;
	private JFrame ventana;
	private JDialog ventanaInicio, vInstrucciones, vAbout;
	private Bombilla[]bombillas;
	private Slider slider;
	private Display display;
	private GridBagConstraints constraints;
	private JMenuBar barra;
	private JMenu mArchivo, mHerramientas, mAyuda;
	private JMenuItem iSalir, iOpciones, iAbout, iInstrucciones;
	
	public InterfazGrafica(Afinador afinador) {
		setLayout(new GridBagLayout());
		this.constraints = new GridBagConstraints();
		this.constraints.insets = new Insets(15, 15, 15, 15);
		this.afinador = afinador;
		this.captura = afinador.getCaptura();
		this.inicio = true;
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (Exception e) {e.printStackTrace();}
		
		inicializarSlider();
		inicializarDisplay();
		inicializarBombillas();
		inicializarFrame();
		inicializarDialogOpciones();
		inicializarDialogInstrucciones();
		inicializarDialogAbout();
	}
	
	private void inicializarMenuBar() {
		barra = new JMenuBar();
		mArchivo = new JMenu("Archivo");
		mHerramientas = new JMenu("Herramientas");
		mAyuda = new JMenu("Ayuda");
		
		iSalir = new JMenuItem("Salir");
		iOpciones = new JMenuItem("Opciones");
		iInstrucciones = new JMenuItem("Instrucciones");
		iAbout = new JMenuItem("Acerca de "+titulo);
		
		iSalir.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F4, ActionEvent.ALT_MASK));
		iOpciones.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, ActionEvent.CTRL_MASK));
		iInstrucciones.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F1, 0));
		mArchivo.add(iSalir);
		mHerramientas.add(iOpciones);
		mAyuda.add(iInstrucciones);
		mAyuda.add(iAbout);
		
		barra.add(mArchivo);
		barra.add(mHerramientas);
		barra.add(mAyuda);
		
		ventana.setJMenuBar(barra);
		
		iSalir.addActionListener(this);
		iOpciones.addActionListener(this);
		iInstrucciones.addActionListener(this);
		iAbout.addActionListener(this);
	}
	
	private void inicializarSlider() {
		slider = new Slider();
		constraints.gridx = 0;
		constraints.gridy = 1;
		constraints.gridwidth = 6;
		constraints.anchor = GridBagConstraints.CENTER;
		this.add(slider, constraints);
	}
	
	private void inicializarDisplay() {
		display = new Display();
		constraints.gridx = 0;
		constraints.gridy = 0;
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
	
	private void inicializarDialogOpciones() {
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
		
		ajustesDialog(ventanaInicio);
		ventanaInicio.setVisible(true);
	}
	
	private void inicializarDialogInstrucciones() {
		vInstrucciones = new JDialog(ventana, "Instrucciones de uso", true);
		ajustesDialog(vInstrucciones);
	}
	
	private void inicializarDialogAbout() {
		JTextArea areaInfo, areaAutores;
		JPanel pImagen;
		Color color = new Color(240,240,240);
		GridBagConstraints c = new GridBagConstraints();
		vAbout = new JDialog(ventana,"Acerca de "+titulo,true);
		vAbout.setLayout(new GridBagLayout());
		
		c.insets = new Insets(15, 15, 15, 15);
		
		areaInfo = new JTextArea();
		areaAutores = new JTextArea();
		pImagen = new JPanel() {
			
			public void paint(Graphics g) {
				g.drawImage(pua.getImage(), 0, 0, this);
			}
		};
		pImagen.setPreferredSize(new Dimension(pua.getIconWidth(), pua.getIconHeight()));
		pImagen.setBackground(color);
		vAbout.add(pImagen, c);
		
		c.gridx = 1;
		areaInfo.setText(titulo+"\nversion 1.0\nBuild ID: 20110513\n\nhttp://code.google.com/p/chustaware/");
		areaInfo.setBackground(color);
		areaInfo.setEditable(false);
		areaInfo.setBorder(null);
		vAbout.add(areaInfo, c);
		
		c.gridy = 1;
		c.gridwidth = 2;
		areaInfo.setText(autores);
		
		ajustesDialog(vAbout);
	}
	
	private void ajustesDialog(JDialog dialog) {
		dialog.setResizable(false);
		dialog.pack();
		centrarDialog(dialog);
		dialog.dispose();
		dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
	}

	private void inicializarFrame() {
		Dimension dPantalla, dVentana;
		ventana = new JFrame(titulo+" v1.0");
		ventana.setIconImage(pua.getImage());
		inicializarMenuBar();
		ventana.add(this, BorderLayout.CENTER);
		ventana.setResizable(false);
		ventana.pack();
		dPantalla = Toolkit.getDefaultToolkit().getScreenSize(); // Dimensiones en pixels de la pantalla.
        dVentana = ventana.getSize(); // Dimensiones en pixels de la ventana.
        // Situamos la ventana en el centro de la pantalla.
        ventana.setLocation((dPantalla.width - dVentana.width) / 2, (dPantalla.height - dVentana.height) / 2);
		ventana.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ventana.setVisible(true);
		
	}
	
	private void centrarDialog(JDialog dialog) {
		Dimension dPantalla, dVentana;
		dPantalla = Toolkit.getDefaultToolkit().getScreenSize(); // Dimensiones en pixels de la pantalla.
        dVentana = dialog.getSize(); // Dimensiones en pixels de la ventana.
        // Situamos la ventana en el centro de la pantalla.
        dialog.setLocation((dPantalla.width - dVentana.width) / 2, (dPantalla.height - dVentana.height) / 2);
	}
	
	public void actionPerformed(ActionEvent e) {
		if (e.getSource() == iSalir) {
			System.exit(0);
		}
		if (e.getSource() == iOpciones) {
			ventanaInicio.setVisible(true);
		}
		if (e.getSource() == iInstrucciones) {
			vInstrucciones.setVisible(true);
		}
		if (e.getSource() == iAbout) {
			vAbout.setVisible(true);
		}

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
	}

	public void pintar() {
		while(true){
			slider.setOffset((int)afinador.getDesafinio());
			display.setnNota(afinador.getNotaReal());
			/*try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}*/
		}
		
	}
}
