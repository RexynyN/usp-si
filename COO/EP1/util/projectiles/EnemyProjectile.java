package util.projectiles;
import java.awt.Color;

import util.GameLib;
import util.objects.Entity2D;
import util.States;

public class EnemyProjectile extends Entity2D{
    private double radius;
    public EnemyProjectile(double x, double y, double vx, double vy, int state, double radius){
        super(x, y, vx, vy);
        this.setState(state);
        this.radius = radius;
    }

    public void updateCoords(long delta) {
        if (this.getState() == States.ACTIVE) {

            if (this.getY() > GameLib.HEIGHT)
                this.setState(States.INACTIVE);
            else {
                double coord = this.getX() + (this.getVelocityX() * delta);
                this.setX(coord);

                coord = this.getY() + (this.getVelocityY() * delta);
                this.setY(coord);
            }
        }
    }

    public void draw(){
        GameLib.setColor(Color.RED);
        GameLib.drawCircle(this.getX(), this.getY(), this.radius);
    }

    public double getRadius(){
        return this.radius;
    } 
}