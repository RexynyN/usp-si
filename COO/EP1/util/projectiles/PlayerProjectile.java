package util.projectiles;
import java.awt.Color;

import util.GameLib;
import util.States;
import util.objects.Entity2D;

public class PlayerProjectile extends Entity2D {
    public PlayerProjectile(double x, double y, double vx, double vy, int state){
        super(x, y, vx, vy);
        this.setState(state);
    }

    public void updateCoords(long delta) {
        if (this.getState() == States.ACTIVE) {

            if (this.getY() < 0)
                this.setState(States.INACTIVE);
            else {
                this.setX(this.getX() + (this.getVelocityX() * delta));
                this.setY(this.getY() + (this.getVelocityY() * delta));
            }
        }
    }

    public void draw(){
        double coordX = this.getX();
		double coordY = this.getY();

        GameLib.setColor(Color.GREEN);
        GameLib.drawLine(coordX, coordY - 5, coordX, coordY + 5);
        GameLib.drawLine(coordX - 1, coordY - 3, coordX - 1, coordY + 3);
        GameLib.drawLine(coordX + 1, coordY - 3, coordX + 1, coordY + 3);
    }
}
