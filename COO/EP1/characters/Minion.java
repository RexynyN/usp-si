package characters;

import util.States;
import util.projectiles.EnemyProjectile;

import java.awt.Color;
import util.GameLib;

public class Minion extends Enemy {
	private double angle;
	private double rotationVelocity;

	public Minion(double radius, long nextShot, double angle, double rotationVelocity) {
		super(radius, nextShot);
		this.angle = angle;
		this.rotationVelocity = rotationVelocity;
		this.setState(States.INACTIVE);
	}


	public boolean draw(long currentTime, long delta) {
		if (this.getState() == States.INACTIVE)
			return false;

		if (this.getState() == States.EXPLODING)
			this.explode(currentTime);
		else {
			GameLib.setColor(Color.CYAN);
			GameLib.drawCircle(this.getX(), this.getY(), this.getRadius());
			this.drawProjectiles(delta);
		}

		return true;
	}


	public void checkStates(long currentTime, long delta, double playerY) {
		// Verifica se o inimigo já terminou de explodir
		if (this.getState() == States.EXPLODING && currentTime > this.getExplosionEnd()) {
			this.setState(States.INACTIVE);
		}
		 
		if (this.getState() == States.ACTIVE) {

			/* verificando se inimigo saiu da tela */
			if (this.getY() > GameLib.HEIGHT + 10) {
				this.setState(States.INACTIVE);
			} else {
				// Atualiza a posição na tela
				this.setX(this.getX() + (this.getVelocityX() * Math.cos(this.angle) * delta));
				this.setY(this.getY() + (this.getVelocityY() * Math.sin(this.angle) * delta * (-1.0)));
				this.angle += this.rotationVelocity * delta;

				// Verifica se já é pra atirar de novo
				if (currentTime > this.getNextShot() && this.getY() < playerY) {
					double velocityX = Math.cos(this.angle) * 0.45;
					double velocityY = Math.sin(this.angle) * 0.45 * (-1.0);

					this.addProjectile(new EnemyProjectile(this.getX(), this.getY(), velocityX, velocityY, States.ACTIVE, 2.0));
					this.setNextShot((long) (currentTime + 1000 + Math.random() * 500));
				}
			}
		}
	}
}
