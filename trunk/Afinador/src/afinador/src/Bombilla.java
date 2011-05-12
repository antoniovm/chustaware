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

public class Bombilla extends JComponent {
	
	private final static String[] notas = {"Mi2", "La2", "Re3", "Sol3", "Si3", "Mi4"};
	private boolean on;
	private int nNota;
	private ImageIcon imagenOn, imagenOff;
	
	public Bombilla(int nNota) {
		this.on = false;
		this.nNota = nNota;
		this.imagenOn = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"on.png");
		this.imagenOff = new ImageIcon("."+File.separator+"bin"+File.separator+"afinador"+File.separator+"img"+File.separator+"off.png");
		setPreferredSize(new Dimension(imagenOff.getIconWidth()*2, imagenOff.getIconHeight()*2));
		setUI(null);
	}
	
	@Override
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		((Graphics2D) g).setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
		FontMetrics fm;
		int x, y;
		g.setFont(new Font(Font.SANS_SERIF, Font.BOLD, 14));
		fm = g.getFontMetrics();
		
		if (on) {
			g.drawImage(imagenOn.getImage(), getWidth()/2-imagenOn.getIconWidth()/2, 0, imagenOn.getIconWidth(), imagenOn.getIconHeight(), this);
		} else {
			g.drawImage(imagenOff.getImage(), getWidth()/2-imagenOff.getIconWidth()/2, 0, imagenOff.getIconWidth(), imagenOff.getIconHeight(), this);
		}
		
		x = getWidth() / 2 - fm.stringWidth(notas[nNota]) / 2;
		y = getHeight() / 2 + fm.getHeight() / 4 +10;
		g.drawString(notas[nNota], x, y);
	}

	public boolean isOn() {
		return on;
	}

	public void setOn(boolean on) {
		this.on = on;
	}

	public ImageIcon getImagenOn() {
		return imagenOn;
	}

	public void setImagenOn(ImageIcon imagenOn) {
		this.imagenOn = imagenOn;
	}

	public ImageIcon getImagenOff() {
		return imagenOff;
	}

	public void setImagenOff(ImageIcon imagenOff) {
		this.imagenOff = imagenOff;
	}
	
	

}
