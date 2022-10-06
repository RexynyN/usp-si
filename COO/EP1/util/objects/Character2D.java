package util.objects;

import util.GameLib;

public class Character2D extends Entity2D{

	private double radius;
	private long explosionStart;					
	private long explosionEnd;				
	private long nextShot;	

    public Character2D(double radius){
        super();        
        this.radius = radius;
        this.explosionStart = 0;
        this.explosionEnd = 0;
    }
    
	public Character2D(double radius, long nextShot){
        super();        
        this.radius = radius;
        this.explosionStart = 0;
        this.explosionEnd = 0;
        this.nextShot = nextShot;
    }

	public Character2D(double radius, long nextShot, double x, double y, double vX, double vY){
        super(x, y, vX, vY);        
        this.radius = radius;
        this.explosionStart = 0;
        this.explosionEnd = 0;
        this.nextShot = nextShot;
    }
    
	protected void explode(long currentTime){
		double alpha = (double) (currentTime - this.explosionStart) / (this.explosionEnd - this.explosionStart);
		GameLib.drawExplosion(this.getX(), this.getY(), alpha);
	}
	
	public void setPosition(double x, double y){
		this.setX(x);
		this.setY(y);
	}
	
	public void setVelocity(double vX, double vY){
		this.setVelocityX(vX);
		this.setVelocityY(vY);
	}
	
	public void setExplosion(long startTime, long endTime){
		this.explosionStart = startTime;
		this.explosionEnd = endTime;
	}

	public long getExplosionEnd(){
		return this.explosionEnd;
	}

	public long getExplosionStart(){
		return this.explosionStart;
	}
	
	protected void setNextShot(long ns){
		this.nextShot = ns;
	}
	
	public double getRadius(){
		return this.radius;
	}
	
	public long getNextShot(){
		return this.nextShot;
	}
}