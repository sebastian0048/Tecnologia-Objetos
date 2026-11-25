// Modelo: guarda los datos de una tarea y su estado.
public class Task {
    private String name;
    private boolean completed;

    public Task(String name) {
        this(name, false);
    }

    public Task(String name, boolean completed) {
        this.name = name;
        this.completed = completed;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public boolean isCompleted() {
        return completed;
    }

    public void complete() {
        completed = true;
    }
}
