package util;

import characters.*;
import util.projectiles.PowerUpGun;

public class Spawner {
    private long nextMinion;
    
    private long nextTank;

    // Variaveis do Squadron
    private long nextSquadron;
    private int squadronCounter;
    private double squadronSpawn;

    // Variaveis de PowerUp
    private long nextPowerUp;

    public Spawner(long currentTime) {
        this.nextMinion = currentTime + 2000;

        this.squadronSpawn = GameLib.WIDTH * 0.20;
        this.nextSquadron = currentTime + 7000;

        this.nextTank = currentTime + 10000;
        
        this.nextPowerUp = currentTime + 5000;
    }


    public Tank spawnTank(long currentTime) {
        if (currentTime > this.nextTank) {
                Tank tank = new Tank(30.0, currentTime + 1000, (3 * Math.PI) / 2, 0.0);

                double velocity = 0.20;
                tank.initializePosition(Math.random() * (GameLib.WIDTH - 20.0) + 10.0, -10.0, velocity, velocity);
                tank.setState(States.ACTIVE);
                this.nextTank = currentTime + 15000;

                return tank;
        }

        return null;
    }

    public Minion spawnMinion(long currentTime) {
        if (currentTime > this.nextMinion) {
                Minion minion = new Minion(9.0, currentTime + 500, (3 * Math.PI) / 2, 0.0);

                double velocity = 0.20 + Math.random() * 0.15;
                minion.initializePosition(Math.random() * (GameLib.WIDTH - 20.0) + 10.0, -10.0, velocity, velocity);
                minion.setState(States.ACTIVE);
                this.nextMinion = currentTime + 1500;

                return minion;
        }
        return null;
    }

    public Squadron spawnSquadron(long currentTime) {
        if (currentTime > this.nextSquadron) {
                Squadron squadron = new Squadron(12.0, (3 * Math.PI) / 2, 0.0);

                squadron.initializePosition(this.squadronSpawn, -10.0, 0.42, 0.42);
                squadron.setState(States.ACTIVE);
                this.squadronCounter++;

                if (this.squadronCounter < 10) {
                    this.nextSquadron = currentTime + 120;
                } else {
                    this.squadronCounter = 0;
                    this.squadronSpawn = Math.random() > 0.5 ? GameLib.WIDTH * 0.2 : GameLib.WIDTH * 0.8;
                    this.nextSquadron = (long) (currentTime + 3000 + Math.random() * 3000);
                }

                return squadron;
            }
        
        return null;
    }

    public void spawnPowerUp(long currentTime, PowerUpGun power){
        if(currentTime > this.nextPowerUp /*  + Math.floor(Math.random() * 1000 )*/){
            double velocity = 0.20;
            
            power.initializePosition(Math.random() * (GameLib.WIDTH - 20.0) + 10.0, -10.0, velocity, velocity);
            power.setState(States.ACTIVE);

            this.nextPowerUp = currentTime + 10000 + (long) Math.random() * 10000;
        }
    }
}
