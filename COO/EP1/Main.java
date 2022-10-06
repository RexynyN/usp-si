import java.util.ArrayList;
import java.util.Iterator;

import characters.*;
import util.BackGround;
import util.GameLib;
import util.Spawner;
import util.States;
import util.projectiles.PowerUpGun;

/***********************************************************************/
/*                                                                     */
/* Para jogar:                                                         */
/*                                                                     */
/*    - cima, baixo, esquerda, direita: movimentação do player.        */
/*    - control: disparo de projéteis.                                 */
/*    - ESC: para sair do jogo.                                        */
/*                                                                     */
/***********************************************************************/

public class Main {
	public static boolean running = true;

	/* Espera, sem fazer nada, até que o instante de tempo atual seja */
	/* maior ou igual ao instante especificado no parâmetro "time. */
	public static void busyWait(long time) {
		while (System.currentTimeMillis() < time)
			Thread.yield();
	}

	/* Método principal */
	public static void main(String[] args) {

		/* Indica que o jogo está em execução */
		/* variáveis usadas no controle de tempo efetuado no main loop */
		long delta;
		long currentTime = System.currentTimeMillis();

		/* variáveis do player */
		Player player = new Player(12.0, currentTime);
		player.initializePosition(GameLib.WIDTH / 2, GameLib.HEIGHT * 0.90, 0.25, 0.25);

		// Arraylist de inimigos
		ArrayList<Minion> minions = new ArrayList<Minion>();

		ArrayList<Squadron> squadrons = new ArrayList<Squadron>();

		ArrayList<Tank> tanks = new ArrayList<Tank>();

		// Spawner de Inimigos
		Spawner spawner = new Spawner(currentTime);

		// PowerUp (desativado)
		PowerUpGun powerUp = new PowerUpGun(0, 0, 0, 0, States.INACTIVE, 7.0);

		/* estrelas que formam o fundo de primeiro plano */
		BackGround back1 = new BackGround(0.070, 0.0, 20, 3, 3);

		/* estrelas que formam o fundo de segundo plano */
		BackGround back2 = new BackGround(0.045, 0.0, 50, 2, 2);

		/* iniciado interface gráfica */

		GameLib.initGraphics();
		// GameLib.initGraphics_SAFE_MODE(); // chame esta versão do método caso nada seja desenhado na janela do jogo.

		/*************************************************************************************************/
		/*                                                                                               */
		/* Main loop do jogo */
		/* ----------------- */
		/*                                                                                               */
		/* O main loop do jogo executa as seguintes operações: */
		/*                                                                                               */
		/*
		 * 1) Verifica se há colisões e atualiza estados dos elementos conforme a
		 * necessidade.
		 */
		/*                                                                                               */
		/*
		 * 2) Atualiza estados dos elementos baseados no tempo que correu entre a última
		 * atualização
		 */
		/*
		 * e o timestamp atual: posição e orientação, execução de disparos de projéteis,
		 * etc.
		 */
		/*                                                                                               */
		/*
		 * 3) Processa entrada do usuário (teclado) e atualiza estados do player
		 * conforme a necessidade.
		 */
		/*                                                                                               */
		/* 4) Desenha a cena, a partir dos estados dos elementos. */
		/*                                                                                               */
		/*
		 * 5) Espera um período de tempo (de modo que delta seja aproximadamente sempre
		 * constante).
		 */
		/*                                                                                               */
		/*************************************************************************************************/
		while (running) {

			/* Usada para atualizar o estado dos elementos do jogo */
			/* (player, projéteis e inimigos) "delta" indica quantos */
			/* ms se passaram desde a última atualização. */

			delta = System.currentTimeMillis() - currentTime;

			/* Já a variável "currentTime" nos dá o timestamp atual. */
			currentTime = System.currentTimeMillis();

			/***************************/
			/* Verificação de colisões */
			/***************************/

			// Checa colisões do powerUp
			powerUp.checkPlayerCollisions(player, currentTime);

			// Checa colisões com o player
			if (player.getState() == States.ACTIVE) {
				/* colisões player - inimigos */
				Iterator<Squadron> squadronCollision = squadrons.iterator();
				while (squadronCollision.hasNext()) {
					squadronCollision.next().checkPlayerCollisions(player, currentTime);
				}

				Iterator<Minion> minionCollision = minions.iterator();
				while (minionCollision.hasNext()) {
					minionCollision.next().checkPlayerCollisions(player, currentTime);
				}

				Iterator<Tank> tankCollision = tanks.iterator();
				while (tankCollision.hasNext()) {
					tankCollision.next().checkPlayerCollisions(player, currentTime);
				}
			}

			/* colisões projeteis (player) - inimigos */
			player.checkEnemyCollisions(minions, currentTime);
			player.checkEnemyCollisions(squadrons, currentTime);
			player.checkEnemyCollisions(tanks, currentTime);

			/***************************/
			/* Atualizações de estados */
			/***************************/

			/* projeteis (player) */
			player.checkProjectilesStates(delta);

			/* projeteis (inimigos) */
			Iterator<Squadron> squadronCollision = squadrons.iterator();
			while (squadronCollision.hasNext()) {
				Squadron squadron = squadronCollision.next();
				// Atualiza o estado do inimigo
				squadron.checkProjectilesStates(delta);
				squadron.checkStates(currentTime, delta);
			}

			Iterator<Minion> minionCollision = minions.iterator();
			while (minionCollision.hasNext()) {
				Minion minion = minionCollision.next();
				// Atualiza o estado do inimigo
				minion.checkProjectilesStates(delta);
				minion.checkStates(currentTime, delta, player.getY());
			}

			Iterator<Tank> tankCollision = tanks.iterator();
			while (tankCollision.hasNext()) {
				Tank tank = tankCollision.next();
				// Atualiza o estado do inimigo
				tank.checkProjectilesStates(delta);
				tank.checkStates(currentTime, delta, player.getY());
			}

			/* verificando se novos inimigos (tipo 1) devem ser "lançados" */
			Minion newMinion = spawner.spawnMinion(currentTime);
			if (newMinion != null)
				minions.add(newMinion);

			/* verificando se novos inimigos (tipo 2) devem ser "lançados" */
			Squadron newSquadron = spawner.spawnSquadron(currentTime);
			if (newSquadron != null)
				squadrons.add(newSquadron);

			/* verificando se novos inimigos (tipo 3) devem ser "lançados" */
			Tank newTank = spawner.spawnTank(currentTime);
			if (newTank != null)
				tanks.add(newTank);

			/* verificando se um novo powerup deve ser "lançados" */
			spawner.spawnPowerUp(currentTime, powerUp);

			powerUp.updateCoords(delta);

			if (powerUp.getState() == States.PICKEDUP) 
				powerUp.checkPowerUpTimer(player, currentTime);


			/* Verificando se a explosão do player já acabou. */
			/* Ao final da explosão, o player volta a ser controlável */
			player.checkState(currentTime);

			/********************************************/
			/* Verificando entrada do usuário (teclado) */
			/********************************************/

			if (player.getState() == States.ACTIVE) {

				if (GameLib.iskeyPressed(GameLib.KEY_UP))
					player.moveUp(delta);

				if (GameLib.iskeyPressed(GameLib.KEY_DOWN))
					player.moveDown(delta);

				if (GameLib.iskeyPressed(GameLib.KEY_LEFT))
					player.moveLeft(delta);

				if (GameLib.iskeyPressed(GameLib.KEY_RIGHT))
					player.moveRight(delta);

				if (GameLib.iskeyPressed(GameLib.KEY_CONTROL)) {
					if (currentTime > player.getNextShot()) {
						player.shoot(currentTime);
					}
				}
			}

			if (GameLib.iskeyPressed(GameLib.KEY_ESCAPE))
				running = false;

			/* Verificando se coordenadas do player ainda estão dentro */
			/* da tela de jogo após processar entrada do usuário. */
			player.fitWindowFrame();

			/*******************/
			/* Desenho da cena */
			/*******************/

			/* desenhando plano fundo distante */
			back2.draw(delta);

			/* desenhando plano de fundo próximo */
			back1.draw(delta);

			/* desenhando player */
			player.draw(currentTime, delta);

			/* desenhando inimigos (tipo 1) */
			Minion minion;
			Iterator<Minion> minionsIt = minions.iterator();
			while (minionsIt.hasNext()) {
				minion = minionsIt.next();

				if(!minion.draw(currentTime, delta))
					// Se o inimigo estiver com o estado de Inativo, remove ele do arraylist
					minionsIt.remove();
			}

			/* desenhando inimigos (tipo 2) */
			Squadron squadron;
			Iterator<Squadron> squadronsIt = squadrons.iterator();
			while (squadronsIt.hasNext()) {
				squadron = squadronsIt.next();

				if(!squadron.draw(currentTime, delta))
					// Se o inimigo estiver com o estado de Inativo, remove ele do arraylist
					squadronsIt.remove();
			}

			/* desenhando inimigos (tipo 3) */
			Tank tank;
			Iterator<Tank> tanksIt = tanks.iterator();
			while (tanksIt.hasNext()) {
				tank = tanksIt.next();

				if(!tank.draw(currentTime, delta))
					// Se o inimigo estiver com o estado de Inativo, remove ele do arraylist
					tanksIt.remove();
			}

			// Desenha o powerup
			powerUp.draw();
			
			/*
			 * chamada a display() da classe GameLib atualiza o desenho exibido pela
			 * interface do jogo.
			 */
			GameLib.display();

			/*
			 * faz uma pausa de modo que cada execução do laço do main loop demore
			 * aproximadamente 3 ms.
			 */
			busyWait(currentTime + 3);
		}

		System.exit(0);
	}
}
