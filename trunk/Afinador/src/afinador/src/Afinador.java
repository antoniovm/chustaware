package afinador.src;
/**
 * 	Clase que se encarga de comparar valores del array de frecuencias con las frecuencias fundamentales(notas)
 */
public class Afinador extends Thread{
	
	private final int UMBRAL=100000;

	//Captura de audio
	private Captura captura;
	//señal de entrada
	private double [][] frecuencia;
	//Primera Octava (Hz):    Do     Do#    Re     Re#    Mi    Fa     Fa#    Sol   Sol#   La     La#    Si 
	private double [] notas={32.7, 34.65, 36.71, 38.89, 41.2, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};
	private int pitch, notaReal, octava;
	private double desafinio;
	private int canal; //0 = Izquierdo -- 1 = Derecho
	private boolean afinando;
	//Primera Octava (Hz):       Do     Do#    	Re 	    Re#	    Mi	    Fa   	Fa#	    Sol	   	Sol#	La 	    La#    	Si 
	private double [] notasTot={32.7, 	34.65, 	36.71,	38.89,	41.2,	43.65, 	46.25, 	49.00, 	51.91, 	55.00, 	58.27, 	61.74,
								65.41, 	69.3,	73.42, 	77.78, 	82.41, 	87.31,	92.5, 	98,		103.83, 110, 	116.54, 123.47,
								130.81,	138.59,	146.83,	155.56,	164.81,	174.61,	185,	196, 	207.65, 220,	233.08, 246.94,
								261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392, 	415.3,	440, 	466.16, 493.88,
								523.25, 554.37, 587.33, 622.25, 659.26, 698.46, 739.99, 783.99, 830.61, 880, 	932.33, 987.77};


	public Afinador() {
		captura = new Captura();
		frecuencia=captura.getFrecuencia();
		canal=1;
	}
	public double[][] getFrecuencia() {
		return frecuencia;
	}
	public void setFrecuencia(double[][] frecuencia) {
		this.frecuencia = frecuencia;
	}
	public double[] getNotas() {
		return notas;
	}
	public void setNotas(double[] notas) {
		this.notas = notas;
	}
	public int getPitch() {
		return pitch;
	}
	public void setPitch(int pitch) {
		this.pitch = pitch;
	}
	public int getNotaReal() {
		return notaReal;
	}
	public void setNotaReal(int notaReal) {
		this.notaReal = notaReal;
	}
	public int getOctava() {
		return octava;
	}
	public void setOctava(int octava) {
		this.octava = octava;
	}
	public double getDesafinio() {
		return desafinio;
	}
	public void setDesafinio(double desafinio) {
		this.desafinio = desafinio;
	}
	public boolean isAfinando() {
		return afinando;
	}
	public void setAfinando(boolean afinando) {
		this.afinando = afinando;
	}
	public void afinarEnergia(){
		captura.capturar();
		afinando=true;
		int max=0;
		while(afinando){
			for (int i = 1; i < 1000; i++) {
				if(frecuencia[canal][i]>frecuencia[canal][max])
					max=i;
			}
			pitch=max;
			calcularNota();
			//System.out.println(escalarFrecuencia()+","+desafinio+","+octava);
			
		}
	}
	public void afinarDeUnaVez(){
		double umbral=1000;
		captura.capturar();
		afinando=true;
		double amplitudMax=0;
		int frecMax=0;
		while(afinando){
			for (int i = 30; i < 1000; i++) {
				if (frecuencia[canal][i] < umbral)
					continue;
				if(frecuencia[canal][i]>amplitudMax){
					amplitudMax=frecuencia[canal][i];
					frecMax=i;
				}
			}
			pitch=frecMax;
			calcularNotaDeUnaVez();
			//System.out.println("FRECUENCIA: "+escalarFrecuencia() + "\t DESAFINIO: " + desafinio+ "\t OCTAVA: " + octava);
			frecMax=0;
			amplitudMax=0;
		}
	}
	public boolean haySenal() {
		for (int i = 20; i < frecuencia[canal].length/4; i++) 
			if(frecuencia[canal][i]>UMBRAL) return true;
		return false;
	}
	public void afinarPitch(){
		int pico=20; 
		int candidatoPitch=20;
		captura.capturar();
		afinando=true;
		while (afinando) {
			for (int i = 20; i < frecuencia[canal].length/4; i++) {
				//System.out.println(frecuencia[canal][i]);
				if(frecuencia[canal][i]<UMBRAL) continue;	//Si no supera el umbral, no se busca
				
				if(frecuencia[canal][i]<frecuencia[canal][i+1]) continue;	//Subiendo
					
				
				pico=i;	//Al haber una bajada, hemos encontrado un pico
				
				if((pico/candidatoPitch==2)||((pico/candidatoPitch+candidatoPitch)==2))		//Si un pico es multiplo del otro, el primero es el pitch
					if((Math.abs(pico%candidatoPitch)<2)||(Math.abs(pico%candidatoPitch+candidatoPitch)<2)){
							pitch=candidatoPitch;
							calcularNotaDeUnaVez();
							break;
					}
				if(frecuencia[canal][pico]>frecuencia[canal][candidatoPitch])	//Si el candidato es menor que el pico, este pasa a ser candidato
					candidatoPitch=pico;
				

			}
			System.out.println("FRECUENCIA: "+escalarFrecuencia() + "\t DESAFINIO: " + desafinio+ "\t OCTAVA: " + octava);
			
			
			
		}
	}
	public int calcularOctava(int i){
		double aux=escalarFrecuencia();
		int j;
		for (j = 1; aux > notas[i]; j++) {
			aux/=2;
		}
		return j;
	}
	public double calcularPuntoMedio(int nota,int octava){
		if(nota==notas.length-1)
			return (notas[nota+1]*Math.pow(2, octava+1)-notas[nota]*Math.pow(2, octava))/2;
		return (notas[nota+1]*Math.pow(2, octava)-notas[nota]*Math.pow(2, octava))/2;
	}
	private void calcularNotaDeUnaVez(){
		double frecuencia=escalarFrecuencia();
		for (int i = 0; i < notasTot.length; i++) {
			if(frecuencia == notasTot[i]){	//si encuentra frec igual
				desafinio=0;
				notaReal=i%12;
				octava=calcularOctava(i%12);
				return;
			}				
			if(frecuencia < notasTot[i] && i!=0){	//si encuentra una menor que no es la primera
				if(Math.abs(notasTot[i] - frecuencia) < Math.abs(frecuencia - notasTot[i+1])){	//compara restos
					desafinio= frecuencia - notasTot[i];
					notaReal=i%12;
					octava=calcularOctava(i%12);
					return;
				}else{
					desafinio=frecuencia - notasTot[i+1];
					notaReal=(i-1)%12;
					octava=calcularOctava((i-1)%12);
					return;
				}
			}
		}
	}
		/*Intento fallido de busqueda binaria...
		while(inf<=sup){
			centro=((sup - inf) / 2) + inf;
			
			if(frecuencia == notasTot[centro]){
				desafinio=0;
				notaReal=centro%12;
				octava=calcularOctava(centro%12);
				return;
			}
				break;
			
			if(frecuencia < notasTot[centro])
				sup = centro - 1;
			else
				inf = centro + 1;	
		}
		if(notasTot[inf] < frecuencia){
			if(notasTot[inf-1] < frecuencia)
				
		}
		*/
	
	private void calcularNota() {
		int octavaExceso=0,octavaDefecto=0, notaExceso=-1, notaDefecto=-1;
		double exceso=Double.POSITIVE_INFINITY,defecto=Double.NEGATIVE_INFINITY;
		
		for (int i = 0; i < notas.length; i++) {
			if((escalarFrecuencia()%notas[i])<exceso){	//Vemos si esta cerca por encima de la nota
				exceso=escalarFrecuencia()%notas[i];
				octavaExceso=calcularOctava(i);
				//if(exceso<calcularPuntoMedio(nota, octavaDefecto))
				notaExceso=i;
			}
			if((escalarFrecuencia()%notas[i]-notas[i])>defecto){//Vemos si esta cerca por debajo de la nota
				defecto=escalarFrecuencia()%notas[i]-notas[i];
				octavaDefecto=calcularOctava(i);
				notaDefecto=i;
			}
				
		}
		if((notaExceso==notas.length)||(notaDefecto==notas.length)){
			return; 
		}
		if(exceso<Math.abs(defecto)){	//El valor mas pequeño de los 2 es el mas cercano
			desafinio=exceso;
			notaReal=notaExceso;
			octava=octavaExceso;
		}else{
			desafinio=defecto;
			notaReal=notaDefecto;
			octava=octavaDefecto;
		}
		
		

	}
	@Override
	public void run() {
		super.run();
		//afinarEnergia();
		afinarPitch();
		//afinarDeUnaVez();
	}
	public Captura getCaptura() {
		return captura;
	}
	public void setCaptura(Captura captura) {
		this.captura = captura;
	}
	/**
	 * Escala frecuencia de 32K a 22K
	 * @return
	 */
	private double escalarFrecuencia(){
		return (captura.getAudioFormat().getSampleRate()/2)*pitch/captura.NUMERO_DE_MUESTRAS;
	}
}
