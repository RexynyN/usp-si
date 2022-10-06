package characters;

import util.States;
import util.GameLib;
import java.awt.Color;
import util.projectiles.EnemyProjectile;

public class Squadron extends Enemy {
	private final double[] angles = { Math.PI / 2 + Math.PI / 8, Math.PI / 2, (Math.PI / 2 - Math.PI / 8) };
	private double angle;
	private double rotationVelocity;

	public Squadron(double radius, double angle, double rotationVelocity) {
		super(radius, 0);
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
			GameLib.setColor(Color.MAGENTA);
			GameLib.drawDiamond(this.getX(), this.getY(), this.getRadius());
			this.drawProjectiles(delta);
		}

		return true;
	}

	public void checkStates(long currentTime, long delta) {

		if (this.getState() == States.EXPLODING && currentTime > this.getExplosionEnd())
			this.setState(States.INACTIVE);

		else if (this.getState() == States.ACTIVE) {

			/* verificando se inimigo saiu da tela */
			if (this.getY() > GameLib.WIDTH + 10) {
				this.setState(States.INACTIVE);
			} else {
				boolean shootNow = false;
				double previousY = this.getY();

				this.setX(this.getX() + (this.getVelocityX() * Math.cos(this.angle) * delta));
				this.setY(this.getY() + (this.getVelocityY() * Math.sin(this.angle) * delta * (-1.0)));
				this.angle += this.rotationVelocity * delta;

				double threshold = GameLib.HEIGHT * 0.30;

				if (previousY < threshold && this.getY() >= threshold) {

					if (this.getX() < GameLib.WIDTH / 2)
						this.rotationVelocity = 0.003;
					else
						this.rotationVelocity = -0.003;
				}

				if (this.rotationVelocity > 0 && Math.abs(this.angle - 3 * Math.PI) < 0.05) {
					this.rotationVelocity = 0.0;
					this.angle = 3 * Math.PI;
					shootNow = true;
				}

				if (this.rotationVelocity < 0 && Math.abs(this.angle) < 0.05) {
					this.rotationVelocity = 0.0;
					this.angle = 0.0;
					shootNow = true;
				}

				if (shootNow) {
					for (int k = 0; k < this.angles.length; k++) {
						double a = this.angles[k] + (Math.random() * (Math.PI / 6 - Math.PI / 12));
						double vx = Math.cos(a) * 0.30;
						double vy = Math.sin(a) * 0.30;

						this.addProjectile(new EnemyProjectile(this.getX(), this.getY(), vx, vy, States.ACTIVE, 2.0));
					}
				}
			}
		}
	}

}
