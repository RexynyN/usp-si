package util.projectiles;

import util.GameLib;
import util.objects.Entity2D;
import util.States;
import characters.Player;
import java.awt.Color;

public class PowerUpGun extends Entity2D {
    private double angle;
    private double radius;
    private long duration;
    private long timer;

    public PowerUpGun(double x, double y, double vx, double vy, int state, double radius) {
        super(x, y, vx, vy);
        this.setState(state);
        this.radius = radius;
        this.angle = (3 * Math.PI) / 2;
        this.timer = 0;
        this.duration = 5000;
    }

    // Checa por colisão do jogador nos inimigos e nos seus projéteis
    public void checkPlayerCollisions(Player player, long currentTime) {
        if (player.getState() == States.EXPLODING || this.getState() == States.INACTIVE
                || this.getState() == States.PICKEDUP)
            return;

        double dx = this.getX() - player.getX();
        double dy = this.getY() - player.getY();
        double dist = Math.sqrt(dx * dx + dy * dy);

        if (dist < (player.getRadius() + this.radius) * 0.8) {
            this.setState(States.PICKEDUP);
            player.powerUpGun();
            this.timer = currentTime + this.duration;
        }
    }

    // Checa por colisão do jogador nos inimigos e nos seus projéteis
    public void checkPowerUpTimer(Player player, long currentTime) {
        // Convenção para dizer que o player não está sob efeito do powerUp
        if (this.timer == 0) {
            return;
        }

        if (currentTime > this.timer) {
            player.powerDownGun();
            this.setState(States.INACTIVE);
            this.timer = 0;
        }
    }

    public void updateCoords(long delta) {
        if (this.getState() == States.ACTIVE) {
            /* verificando se saiu da tela */
            if (this.getY() > GameLib.HEIGHT + 10) {
                this.setState(States.INACTIVE);
            } else {
                // Atualiza a posição na tela
                this.setX(this.getX() + (this.getVelocityX() * Math.cos(this.angle) * delta));
                this.setY(this.getY() + (this.getVelocityY() * Math.sin(this.angle) * delta * (-1.0)));
            }
        }
    }

    public void draw() {
        if (this.getState() == States.ACTIVE) {

            // Cria uma animação dahorinha
            if (Math.floor(Math.random() * 10) % 2 == 0)
                GameLib.setColor(Color.GREEN);
            else
                GameLib.setColor(Color.GRAY);

            GameLib.drawCircle(this.getX(), this.getY(), this.radius);
        }
    }
}
