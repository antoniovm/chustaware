package afinador.src;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.Event;
import java.awt.Font;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.TextArea;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;

import javax.swing.Action;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.KeyStroke;
import javax.swing.UIManager;
import javax.swing.event.HyperlinkEvent;
import javax.swing.event.HyperlinkListener;

public class InterfazGrafica extends JPanel implements ActionListener {
	private final static String titulo = "CWTuner";
	private final static String autores = "Jorge Garcia Hinestrosa\nSergio Revueltas Estrada\nMiguel Vicente Linares\nAntonio Vicente Martin";
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
		afinador.getCaptura().setIg(this);
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
		//barra de menu
		barra = new JMenuBar();
		mArchivo = new JMenu("Archivo");
		mHerramientas = new JMenu("Herramientas");
		mAyuda = new JMenu("Ayuda");
		
		//desplegables
		iSalir = new JMenuItem("Salir");
		iOpciones = new JMenuItem("Opciones");
		iInstrucciones = new JMenuItem("Instrucciones");
		iAbout = new JMenuItem("Acerca de "+titulo);
		
		//atajos de teclado
		iSalir.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F4, ActionEvent.ALT_MASK));
		iOpciones.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, ActionEvent.CTRL_MASK));
		iInstrucciones.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_F1, 0));
		
		//añadir
		mArchivo.add(iSalir);
		mHerramientas.add(iOpciones);
		mAyuda.add(iInstrucciones);
		mAyuda.add(iAbout);
		
		barra.add(mArchivo);
		barra.add(mHerramientas);
		barra.add(mAyuda);
		
		ventana.setJMenuBar(barra);
		
		//escuchar
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
		
		//aceptar dando a enter, focus para textfield
		mezcladores.setFocusable(true);
		mezcladores.requestFocusInWindow();
		mezcladores.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					bAceptar.doClick();
				}
			}
		});
		
		ajustesDialog(ventanaInicio);
		ventanaInicio.setVisible(true);
	}
	
	private void inicializarDialogInstrucciones() {
		Font fuente = new Font(Font.SANS_SERIF, Font.PLAIN, 12);
		GridBagConstraints constraints = new GridBagConstraints();
		JTextArea areaInfo = new JTextArea();
		JTextArea areaDisplay = new JTextArea();
		JTextArea areaSlider = new JTextArea();
		JTextArea areaBombillaOn = new JTextArea();
		JTextArea areaBombillaOff = new JTextArea();
		JPanel pImgDisplay, pImgPua, pImgOn, pImgOff;
		JButton bOk = new JButton("OK");
		vInstrucciones = new JDialog(ventana, "Instrucciones de uso", true);
		vInstrucciones.setLayout(new GridBagLayout());
		vInstrucciones.getContentPane().setBackground(Color.WHITE);
		
		pImgDisplay = new JPanel() {
			public void paint(Graphics g) {
				g.drawImage(display.getFondo().getImage(), 0, 0, this);
			}
		};
		pImgPua = new JPanel() {
			public void paint(Graphics g) {
				g.drawImage(slider.getPua().getImage(), 0, 0, this);
			}
		};
		pImgOn = new JPanel() {
			public void paint(Graphics g) {
				g.drawImage(bombillas[0].getImagenOn().getImage(), 0, 0, this);
			}
		};
		pImgOff = new JPanel() {
			public void paint(Graphics g) {
				g.drawImage(bombillas[0].getImagenOff().getImage(), 0, 0, this);
			}
		};
		areaInfo.setFont(fuente);
		areaInfo.setEditable(false);
		areaInfo.setText(titulo+" es un programa creado con la intención de facilitar el trabajo a la hora de afinar una guitarra\n" +
				"eléctrica.\n" +
				"Para ello, tan solo hay que conectar la guitarra eléctrica al ordenador a través de la linea de entrada de su tarjeta de sonido o\n" +
				"a través de la interfaz del micrófono.\n" +
				"Una vez conectada, al tocar una nota, dicha nota se mostrará en la pantalla, y en caso de coincidir con\n" +
				"alguna de las notas que aparecen en la parte inferior de la pantalla, se encenderá la luz correspondiente\n" +
				"en verde, indicándonos que dicha nota es la que suena.\n" +
				"Si la cuerda está afinada, estará marcada la posición 0 en la barra central, en caso contrario, se muestra\n" +
				"el grado de desafinio aproximado.\n");
		
		areaDisplay.setFont(fuente);
		areaDisplay.setEditable(false);
		areaDisplay.setText("En este display se muestra la nota que está sonando.\n"+
				"Se mostrará la nota pertinente junto a su octava.");
		
		areaSlider.setFont(fuente);
		areaSlider.setEditable(false);
		areaSlider.setText("Si la nota está afinada, la púa estará situada en la posición 0.\n" +
				"Cuanto más lejos se encuentre del 0, más desafinado está dicha nota.");
		
		areaBombillaOn.setFont(fuente);
		areaBombillaOn.setEditable(false);
		areaBombillaOn.setText("Luz verde:\n" +
				"La nota se corresponde con la nota indicada en dicha bombilla.\n" +
				"La cuerda está afinada.");
		
		areaBombillaOff.setFont(fuente);
		areaBombillaOff.setEditable(false);
		areaBombillaOff.setText("Luz roja:\n" +
				"La nota no se corresponde con la nota indicada en dicha bombilla.\n" +
				"La cuerda no está afinada.");
		
		pImgDisplay.setPreferredSize(new Dimension(display.getFondo().getIconWidth(), display.getFondo().getIconHeight()));
		pImgPua.setPreferredSize(new Dimension(slider.getPua().getIconWidth(), slider.getPua().getIconHeight()));
		pImgOn.setPreferredSize(new Dimension(bombillas[0].getImagenOn().getIconWidth(), bombillas[0].getImagenOn().getIconHeight()));
		pImgOff.setPreferredSize(new Dimension(bombillas[0].getImagenOff().getIconWidth(), bombillas[0].getImagenOff().getIconHeight()));
		
		constraints.gridx = 0;
		constraints.gridy = 0;
		constraints.gridwidth = 2;
		constraints.gridheight = 1;
		constraints.insets = new Insets(5, 5, 5, 5);
		constraints.weightx = 1.0;
		constraints.weighty = 1.0;
		constraints.fill = GridBagConstraints.BOTH;
		vInstrucciones.add(areaInfo, constraints);
		constraints.gridwidth = 1;
		constraints.gridy = 1;
		constraints.fill = GridBagConstraints.NONE;
		vInstrucciones.add(pImgDisplay, constraints);
		constraints.gridx = 1;
		constraints.fill = GridBagConstraints.BOTH;
		vInstrucciones.add(areaDisplay, constraints);
		constraints.gridx = 0;
		constraints.gridy = 2;
		constraints.fill = GridBagConstraints.NONE;
		vInstrucciones.add(pImgPua, constraints);
		constraints.gridx = 1;
		constraints.fill = GridBagConstraints.BOTH;
		vInstrucciones.add(areaSlider, constraints);
		constraints.gridx = 0;
		constraints.gridy = 3;
		constraints.fill = GridBagConstraints.NONE;
		vInstrucciones.add(pImgOn, constraints);
		constraints.gridx = 1;
		constraints.fill = GridBagConstraints.BOTH;
		vInstrucciones.add(areaBombillaOn, constraints);
		constraints.gridx = 0;
		constraints.gridy = 4;
		constraints.fill = GridBagConstraints.NONE;
		vInstrucciones.add(pImgOff, constraints);
		constraints.gridx = 1;
		constraints.fill = GridBagConstraints.BOTH;
		vInstrucciones.add(areaBombillaOff, constraints);
		constraints.gridwidth = 2;
		constraints.gridx = 0;
		constraints.gridy = 5;
		constraints.fill = GridBagConstraints.NONE;
		constraints.insets = new Insets(20, 0, 20, 0);
		vInstrucciones.add(bOk, constraints);
		
		bOk.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				vInstrucciones.dispose();			
			}
		});
		
		vInstrucciones.setFocusable(true);
		vInstrucciones.requestFocusInWindow();
		vInstrucciones.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					vInstrucciones.dispose();
				}
			}
		});
		
		ajustesDialog(vInstrucciones);
	}
	
	private void inicializarDialogAbout() {
		vAbout = new JDialog(ventana,"Acerca de "+titulo,true);
		JEditorPane editorInfo; //zona de informacion, acepta HTML
		JPanel pImagen, pBajo; //panel pua, panel zona desarrolladores
		JTextArea areaAutores; //texto zona de desarrolladores
		JButton bOK = new JButton("OK");
		
		GridBagConstraints constraints = new GridBagConstraints();
		
		//zona informacion, usando HTML
		editorInfo = new JEditorPane();
		editorInfo.setContentType("text/html");
		editorInfo.setText(titulo+"<br>version 1.0<br>Build ID: 20110513<br>© 2011<br><br>Agradecimientos:<br><a href=\"http://www.nauticom.net/www/jdtaft/JavaFFT.htm\">FFT</a>, <a href=\"http://www.nauticom.net/www/jdtaft/JavaWindows.htm\">Window</a>");
		editorInfo.setEditable(false);
		editorInfo.addHyperlinkListener(new HyperlinkListener() {
			public void hyperlinkUpdate(HyperlinkEvent e) {
				if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {
					try {
						Desktop.getDesktop().browse(
								new URI((e.getURL()).toString())); //abre el navegador por defecto
					} catch (IOException e1) {
						e1.printStackTrace();
					} catch (URISyntaxException e1) {
						e1.printStackTrace();
					}
				}
			}
		});
		
		editorInfo.setBackground(vAbout.getBackground()); //todo el panel superior del mismo color
		vAbout.setLayout(new GridBagLayout());
		
		constraints.gridx = 1;
		constraints.gridy = 0;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		constraints.weightx = 1.0;
		constraints.weighty = 1.0;
		constraints.fill = GridBagConstraints.BOTH;
		constraints.insets = new Insets(0, 0, 15, 0);
		vAbout.add(editorInfo, constraints);
		
		//panel de la pua
		pImagen = new JPanel() {
			public void paint(Graphics g) {
				g.drawImage(slider.getPua().getImage(), 0, 0, this);
			}
		};
		
		constraints.gridx = 0;
		constraints.gridy = 0;
		constraints.gridwidth = 1;
		constraints.gridheight = 1;
		constraints.insets = new Insets(15, 15, 15, 15);
		vAbout.add(pImagen,constraints);
		
		//panel inferior, desarrolladores
		pBajo = new JPanel();
		pBajo.setLayout(new GridBagLayout());
		pBajo.setBackground(Color.WHITE);
		
		//texto desarrolladores, reutilizamos valores anteriores de constraints
		areaAutores=new JTextArea("Desarrolladores:\n"+autores);
		areaAutores.setFont(new Font(Font.SANS_SERIF, Font.PLAIN, 12));
		areaAutores.setEditable(false);
		pBajo.add(areaAutores, constraints);
		
		//boton OK
		constraints.gridx=1;
		constraints.gridy=0;
		constraints.anchor = GridBagConstraints.SOUTHEAST;
		constraints.fill = GridBagConstraints.NONE;
		
		bOK.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				vAbout.dispose();
			}
		});
		pBajo.add(bOK, constraints);
		
		//añadir panel con textarea y boton OK
		constraints.gridx=0;
		constraints.gridy=1;
		constraints.gridwidth = 2;
		constraints.weightx = 0.0;
		constraints.weighty = 0.0;
		constraints.fill = GridBagConstraints.BOTH;
		constraints.insets = new Insets(0, 0, 0, 0);
		vAbout.add(pBajo, constraints);
		
		//esta es la clave, ponemos a la escucha el dialog, no el boton
		vAbout.setFocusable(true);
		vAbout.requestFocusInWindow();
		vAbout.addKeyListener(new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ENTER) {
					vAbout.dispose();
				}
			}
		});
		
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
		ventana.setIconImage(slider.getPua().getImage());
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
		//gradiente
		/*Color color1 = new Color(0,0,0);
		Color color2 = new Color(255,255,255);
		GradientPaint gr = new GradientPaint(0, 0, color1, 0, getHeight(), color2);
		((Graphics2D)g).setPaint(gr);
		((Graphics2D)g).fillRect(0, 0, getWidth(), getHeight());*/
		ImageIcon img = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"fondo.png");
		g.drawImage(img.getImage(), 0, 0, this.getWidth(), this.getHeight(), this);
	}
	
	public void paint(Graphics g) {
		super.paint(g);
		// Si no estamos en la pantalla inicial, pintamos las luces, etc
		if(!inicio) {
			
		}
	}

	public void pintar() {
			slider.setOffset((int)afinador.getDesafinio());	//escala de slider
			display.setnNota(afinador.getNotaReal());
			display.setOctava(afinador.getOctava());
			display.setSignal(afinador.haySenal());
			if((afinador.getNotaReal()%12==4)&&(afinador.getOctava()==2)) {activarBombilla(0);return;}
			if((afinador.getNotaReal()%12==9)&&(afinador.getOctava()==2)) {activarBombilla(1);return;}
			if((afinador.getNotaReal()%12==2)&&(afinador.getOctava()==3)) {activarBombilla(2);return;}
			if((afinador.getNotaReal()%12==7)&&(afinador.getOctava()==3)) {activarBombilla(3);return;}
			if((afinador.getNotaReal()%12==11)&&(afinador.getOctava()==3)){ activarBombilla(4);return;}
			if((afinador.getNotaReal()%12==4)&&(afinador.getOctava()==4)) {activarBombilla(5);return;}
			activarBombilla(-1);
			/*try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}*/
		
		
	}
	private void activarBombilla(int on) {
		for (int i = 0; i < bombillas.length; i++) {
			if(i==on){
				bombillas[i].setOn(true);
				bombillas[i].repaint();
				continue;
			}
			bombillas[i].setOn(false);
			bombillas[i].repaint();
		}
		
	}
}
