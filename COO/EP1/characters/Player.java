package characters;

import java.util.ArrayList;
import java.util.Iterator;

import util.GameLib;
import util.States;
import util.objects.Character2D;
import util.projectiles.PlayerProjectile;

import java.awt.Color;

public class Player extends Character2D {
	private ArrayList<PlayerProjectile> projectiles = new ArrayList<>();
	private double nextShotDelay;

	public Player(double radius, long nextShot) {
		super(radius, nextShot);
		this.setState(States.ACTIVE);
		this.nextShotDelay = 100;
	}

	public Player(double radius, long nextShot, double x, double y, double vX, double vY) {
		super(radius, nextShot, x, y, vX, vY);
		this.setState(States.ACTIVE);
	}

	// Checa por colisão de inimigos nos projéteis do jogador
	public <T extends Enemy> void checkEnemyCollisions(ArrayList<T> enemys, long currentTime) {
		// Enquanto tiver projéteis para checar no arraylist, faz a colisão com os
		// inimigos
		for (int i = 0; i < projectiles.size(); i++) {
			for (T enemy : enemys) {
				if (enemy.getState() == States.ACTIVE) {
					double dx = enemy.getX() - projectiles.get(i).getX();
					double dy = enemy.getY() - projectiles.get(i).getY();

					double dist = Math.sqrt(dx * dx + dy * dy);

					if (dist < enemy.getRadius()) {
						projectiles.get(i).setState(States.INACTIVE);
						enemy.setExplosion(currentTime, currentTime + 500);
						enemy.setState(States.EXPLODING);
					}
				}
			}
		}

	}

	public void draw(long currentTime, long delta) {
		if (this.getState() == States.INACTIVE)
			return;

		if (this.getState() == States.EXPLODING)
			this.explode(currentTime);
		else {
			GameLib.setColor(Color.BLUE);
			GameLib.drawPlayer(this.getX(), this.getY(), this.getRadius());
			this.drawProjectiles(delta);
		}
	}

	public void drawProjectiles(long delta) {
		Iterator<PlayerProjectile> it = this.projectiles.iterator();
		PlayerProjectile proj;
		while (it.hasNext()) {
			proj = it.next();
			if (proj.getState() == States.ACTIVE) {
				proj.updateCoords(delta);
				proj.draw();
			}
		}
	}

	public void shoot(long currentTime) {
		if (currentTime > this.getNextShot()) {
			double y = this.getY() - 2 * this.getRadius();
			PlayerProjectile proj = new PlayerProjectile(this.getX(), y, 0.0, -1.0, States.ACTIVE);

			this.projectiles.add(proj);
			this.setNextShot(currentTime + (long) this.nextShotDelay);
		}
	}

	public void checkProjectilesStates(long delta) {
		Iterator<PlayerProjectile> it = this.projectiles.iterator();
		PlayerProjectile proj;
		while (it.hasNext()) {
			proj = it.next();
			if (proj.getState() == States.ACTIVE) {
				/* verificando se projétil saiu da tela */
				if (proj.getY() < 0) {
					proj.setState(States.INACTIVE);
				} else {
					proj.setX(proj.getX() + (proj.getVelocityX() * delta));
					proj.setY(proj.getY() + (proj.getVelocityY() * delta));
				}
			} else {
				it.remove();
			}
		}
	}

	public void moveUp(long delta) {
		this.setY(this.getY() - (delta * this.getVelocityY()));
	}

	public void moveDown(long delta) {
		this.setY(this.getY() + (delta * this.getVelocityY()));
	}

	public void moveLeft(long delta) {
		this.setX(this.getX() - (delta * this.getVelocityX()));
	}

	public void moveRight(long delta) {
		this.setX(this.getX() + (delta * this.getVelocityX()));
	}

	public void fitWindowFrame() {
		if (this.getX() < 0.0)
			this.setX(0.0);

		if (this.getX() >= GameLib.WIDTH)
			this.setX(GameLib.WIDTH - 1);

		if (this.getY() < 25.0)
			this.setY(25.0);

		if (this.getY() >= GameLib.HEIGHT)
			this.setY(GameLib.HEIGHT - 1);
	}

	public void checkState(long currentTime) {
		if (this.getState() == States.EXPLODING) {
			if (currentTime > this.getExplosionEnd()) {
				this.setState(States.ACTIVE);
			}
		}
	}

	public void powerUpGun() {
		this.nextShotDelay /= 2;
	}

	public void powerDownGun() {
		this.nextShotDelay *= 2;
	}
}
