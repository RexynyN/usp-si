package characters;

import java.util.ArrayList;
import java.util.Iterator;

import util.GameLib;
import util.States;
import util.objects.Character2D;
import util.projectiles.EnemyProjectile;

public class Enemy extends Character2D {
	private ArrayList<EnemyProjectile> projectiles = new ArrayList<>();

	public Enemy(double radius, long nextShot) {
		super(radius, nextShot);
	}

	public Enemy(double radius) {
		super(radius, 0);
	}

	// Checa por colisão do jogador nos inimigos e nos seus projéteis
	public void checkPlayerCollisions(Player player, long currentTime) {
		if (player.getState() == States.EXPLODING)
			return;

		double dx = this.getX() - player.getX();
		double dy = this.getY() - player.getY();
		double dist = Math.sqrt(dx * dx + dy * dy);

		if (dist < (player.getRadius() + this.getRadius()) * 0.8) {
			player.setState(States.EXPLODING);
			player.setExplosion(currentTime, currentTime + 2000);
			return;
		}

		Iterator<EnemyProjectile> it = this.projectiles.iterator();
		EnemyProjectile proj;

		// Enquanto tiver projéteis para checar no arraylist, faz a colisão com o player
		while (it.hasNext()) {
			proj = it.next();

			dx = proj.getX() - player.getX();
			dy = proj.getY() - player.getY();
			dist = Math.sqrt(dx * dx + dy * dy);

			if (dist < (player.getRadius() + proj.getRadius()) * 0.8) {
				player.setState(States.EXPLODING);
				player.setExplosion(currentTime, currentTime + 2000);
				break;
			}
		}
	}

	public void checkProjectilesStates(long delta) {
		Iterator<EnemyProjectile> it = this.projectiles.iterator();
		EnemyProjectile proj;

		while (it.hasNext()) {
			proj = it.next();
			if (proj.getState() == States.ACTIVE) {
				/* verificando se projétil saiu da tela */
				if (proj.getY() > GameLib.HEIGHT) {
					proj.setState(States.INACTIVE);
				} else {
					proj.setX(proj.getX() + (proj.getVelocityX() * delta));
					proj.setY(proj.getY() + (proj.getVelocityY() * delta));
				}
			} else 
				it.remove();
		}
	}

	public void drawProjectiles(long delta) {
		Iterator<EnemyProjectile> it = this.projectiles.iterator();
		EnemyProjectile proj;

		while (it.hasNext()) {
			proj = it.next();
			if (proj.getState() == States.ACTIVE) {
				proj.updateCoords(delta);
				proj.draw();
			}
		}
	}

	public void addProjectile(EnemyProjectile proj) {
		this.projectiles.add(proj);
	}
}
