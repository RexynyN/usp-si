package util.objects;

public class Entity2D extends Point2D{
    private int state;
    private double velocityX;
    private double velocityY;

    public Entity2D(){
        super(0, 0);
        this.state = 0;
        this.velocityX = 0;
        this.velocityY = 0;
    }

    public Entity2D(double x, double y){
        super(x, y);
        this.state = 0;
        this.velocityX = 0;
        this.velocityY = 0;
    }

    public Entity2D(double x, double y, double vx, double vy){
        super(x, y);
        this.state = 0;
        this.velocityX = vx;
        this.velocityY = vy;
    }

        
	public void initializePosition(double x, double y, double vX, double vY){
		this.setX(x);
		this.setY(y);
		this.setVelocityX(vX);
		this.setVelocityY(vY);
	}


    public int getState(){
        return this.state;
    }

    public void setState(int s){
        // Os estados possíveis são {0, 1, 2}, então tem que estar nesse intervalo;
        if(s >= 0 && s <= 3)
            this.state = s;
    }

    public double getVelocityX(){
        return this.velocityX;
    }

    public void setVelocityX(double v){
        this.velocityX = v;
    }

    public double getVelocityY(){
        return this.velocityY;
    }

    public void setVelocityY(double v){
        this.velocityY = v;
    }
    
}
