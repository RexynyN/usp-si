
package characters;

import util.States;
import util.projectiles.EnemyProjectile;

import java.awt.Color;
import util.GameLib;

public class Tank extends Enemy {
    private double angle;
    private double rotationVelocity;
    private int health;
    private double landingY;

    public Tank(double radius, long nextShot, double angle, double rotationVelocity) {
        super(radius, nextShot);
        this.angle = angle;
        this.rotationVelocity = rotationVelocity;
        this.setState(States.INACTIVE);
        this.health = 10;
        this.setLandingY();
    }

    public boolean draw(long currentTime, long delta) {
		if (this.getState() == States.INACTIVE)
			return false;

		if (this.getState() == States.EXPLODING)
			this.explode(currentTime);
		else {
            GameLib.setColor(Color.ORANGE);
            GameLib.drawTriangle(this.getX(), this.getY(), this.getRadius());
			this.drawProjectiles(delta);
		}

		return true;
	}

    public void checkStates(long currentTime, long delta, double playerY) {
        if(this.getState() == States.EXPLODING && currentTime > this.getExplosionEnd())
            this.setState(States.INACTIVE);
        
        if (this.getState() == States.ACTIVE) {
            /* verificando se inimigo saiu da tela */
            if (this.getY() > GameLib.HEIGHT + 10) {
                this.setState(States.INACTIVE);
            } else {
                // É pra ele parar na altura de 70% da tela
                if (this.getY() < this.landingY) {
                    this.setX(this.getX() + (this.getVelocityX() * Math.cos(this.angle) * delta));
                    this.setY(this.getY() + (this.getVelocityY() * Math.sin(this.angle) * delta * (-1.0)));
                    this.angle += this.rotationVelocity * delta;
                }

                // Verifica se já é pra atirar de novo
                if (currentTime > this.getNextShot()) {
                    double velocityX = Math.cos(this.angle) * 0.25;
                    double velocityY = Math.sin(this.angle) * 0.25 * (-1.0);

                    this.addProjectile(
                            new EnemyProjectile(this.getX(), this.getY(), velocityX, velocityY, States.ACTIVE, 10));
                    this.setNextShot((long) (currentTime + 3000));
                }
            }
        }
    }

    // Modificado para dar dano, e não explodir
    @Override
    public void setState(int state){
        if(state == States.EXPLODING && this.health <= 0){
            super.setState(state);
        }else if (state == States.EXPLODING && this.health > 0){
            super.setState(States.ACTIVE);
            this.health--;
        }else{
            super.setState(state);
        }
    }

    private void setLandingY(){
        double random = 1;
        while(random > 0.6 || random < 0.1)
            random = Math.random();
        
        this.landingY = GameLib.HEIGHT * random;
    }
}
