import java.util.ArrayList;
import java.util.List;

// Controlador: recibe las acciones, modifica el modelo y pide a la vista que muestre el resultado.
public class TaskController {
    private List<Task> tasks;
    private TaskView view;

    public TaskController(TaskView view) {
        this.view = view;
        this.tasks = new ArrayList<>();
    }

    public void addTask(String taskName) {
        tasks.add(new Task(taskName));
        view.printMessage("Tarea agregada: " + taskName);
    }

    public void completeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.get(index).complete();
            view.printMessage("Tarea completada: " + tasks.get(index).getName());
        } else {
            view.printMessage("Error: no existe una tarea con el indice " + index);
        }
    }

    public void displayTasks() {
        view.printTasks(tasks);
    }
}
