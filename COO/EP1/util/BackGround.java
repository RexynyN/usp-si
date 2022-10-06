package util;
import java.util.Iterator;

import util.objects.Point2D;

import java.util.ArrayList;
import java.awt.Color;

public class BackGround {
    private ArrayList<Point2D> points = new ArrayList<>();
    private double speed;
    private double count;
    private int particles;
    private double width;
    private double height;

    public BackGround(double speed, double count, int particles, double width, double height) {
        this.speed = speed;
        this.count = count;
        this.height = height;
        this.width = width;
        this.particles = particles;

        // Cria as particulas do background
        for (int i = 0; i < particles; i++) {
            points.add(new Point2D(Math.random() * GameLib.WIDTH, Math.random() * GameLib.HEIGHT));
        }
    }

    public void draw(long delta) {
    	GameLib.setColor(Color.DARK_GRAY);
        Iterator<Point2D> it = points.iterator();

        this.incrementCount(delta);

        while (it.hasNext()) {
            Point2D p = it.next();
            GameLib.fillRect(p.getX(), (p.getY() + this.count) % GameLib.HEIGHT, this.width, this.height);
        }
    }

    public void incrementCount(double delta) {
        if (delta > 0)
            this.count += this.speed * delta;
    }

    public void updateParticles(int particles){
        int delta = particles - this.particles; 

        if(delta == 0)
            return;

        // Se for maior que zero, adiciona partículas, senão retira partículas
        if(delta > 0){
            for (int i = 0; i < delta; i++) {
                points.add(new Point2D(Math.random() * GameLib.WIDTH, Math.random() * GameLib.HEIGHT));
            }
        }else{
            delta = Math.abs(delta);
            for (int i = 1; i <= delta; i++) {
                points.remove(this.particles - i);
            }
        }
    }

    // Getters/Setters
    public void setWidth (double w){
        if(w > 0)
            this.width = w;
    }

    public double getWidth(){
        return this.width;
    }

    public void setHeight (double h){
        if(h > 0)
            this.width = h;
    }

    public double getHeight(){
        return this.height;
    }

    public void setCount(double c) {
        if (c > 0)
            this.count = c;
    }

    public double getCount() {
        return this.count;
    }

    public void setSpeed (double s) {
        if (s > 0)
            this.speed = s;
    }

    public double getSpeed() {
        return this.speed;
    }

    public void setParticles(int p) {
        if (p > 0)
            this.particles = p;
    }

    public int getParticles() {
        return this.particles;
    }

}
