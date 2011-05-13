package afinador.src;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JComponent;

public class Display extends JComponent {
	
	private final static String[]notas = {"-","Do", "Do#", "Re", "Re#", "Mi", "Fa", "Fa#", "Sol", "Sol#", "La", "La#", "Si"};
	private int nNota, octava;
	private ImageIcon fondo;
	
	public Display() {
		nNota = 0;
		octava = -1;
		fondo = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"display.png");
		setPreferredSize(new Dimension(fondo.getIconWidth(), fondo.getIconHeight()));
		setUI(null);
	}
	
	public int getnNota() {
		return nNota;
	}

	public void setnNota(int nNota) {
		this.nNota = nNota;
		repaint();
	}

	public int getOctava() {
		return octava;
	}

	public void setOctava(int octava) {
		this.octava = octava;
	}

	public ImageIcon getFondo() {
		return fondo;
	}

	public void setFondo(ImageIcon fondo) {
		this.fondo = fondo;
	}

	public static String[] getNotas() {
		return notas;
	}

	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		((Graphics2D) g).setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
		FontMetrics fm;
		int x, y;
		g.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 50));
		fm = g.getFontMetrics();
		g.drawImage(fondo.getImage(), 0, 0, this);
		x = getWidth() / 2 - fm.stringWidth(notas[nNota]) / 2;
		y = getHeight() / 2 + fm.getHeight() / 4;
		g.drawString(notas[nNota+1], x, y);
	}
}
