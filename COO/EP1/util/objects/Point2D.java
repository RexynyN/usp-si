package util.objects;
public class Point2D {
    private double coordX; // coordenadas x
    private double coordY; // coordenadas y

    public Point2D(double x, double y) {
        this.coordX = x;
        this.coordY = y;
    }

    // Getters/Setters coordX
    public double getX() {
        return this.coordX;
    }

    public void setX(double x){
        this.coordX = x; 
    }

    public double getY() {
        return this.coordY;
    }

    public void setY(double y){
        this.coordY = y; 
    }

    public void set2DPoint(double x, double y){
        this.coordX = x; 
        this.coordY = y; 
    }
}
