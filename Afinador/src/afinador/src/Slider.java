package afinador.src;

import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.ImageIcon;
import javax.swing.JComponent;

public class Slider extends JComponent {
	private int offset;
	private ImageIcon barra, pua;
	
	public Slider(){
		offset=0;
		barra=new ImageIcon(System.getProperty("user.dir")+"/src/img/barraSlider.png");
		pua=new ImageIcon(System.getProperty("user.dir")+"/src/img/puaCW.png");
		try{
			this.setPreferredSize(new Dimension(barra.getIconWidth(), pua.getIconHeight()));
		} catch (Exception e) {
			System.out.println("No se encuentran las imágenes");
		}
	}
	
	public void paintComponents(Graphics g) {
		super.paintComponents(g);
		if(offset == 0){
			g.drawImage(barra.getImage(), 0, 0, barra.getIconWidth(), barra.getIconHeight(), this);
			g.drawImage(pua.getImage(), this.getWidth()/2-pua.getIconWidth()/2, 0, pua.getIconWidth(), pua.getIconHeight(), this);
		}
	}
	
	public int getOffset() {
		return offset;
	}

	public void setOffset(int offset) {
		this.offset = offset;
		repaint();
	}

	public ImageIcon getBarra() {
		return barra;
	}

	public void setBarra(ImageIcon barra) {
		this.barra = barra;
	}

	public ImageIcon getPua() {
		return pua;
	}

	public void setPua(ImageIcon pua) {
		this.pua = pua;
	}
}
