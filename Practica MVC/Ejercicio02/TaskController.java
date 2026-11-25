import java.util.ArrayList;
import java.util.List;

// Controlador: recibe las acciones, modifica el modelo y pide a la vista que muestre el resultado.
public class TaskController {
    private List<Task> tasks;
    private TaskView view;
    private Storage<Task> storage;

    // Recibe el almacenamiento como interfaz, asi puede cambiarse por otro sin tocar esta clase.
    public TaskController(TaskView view, Storage<Task> storage) {
        this.view = view;
        this.storage = storage;
        this.tasks = new ArrayList<>();
    }

    public void addTask(String taskName) {
        tasks.add(new Task(taskName));
        view.printMessage("Tarea agregada: " + taskName);
    }

    public void completeTask(int index) {
        try {
            Task task = findTask(index);
            task.complete();
            view.printMessage("Tarea completada: " + task.getName());
        } catch (TaskException e) {
            view.printMessage("Error: " + e.getMessage());
        }
    }

    public void updateTask(int index, String newName) {
        try {
            Task task = findTask(index);
            String oldName = task.getName();
            task.setName(newName);
            view.printMessage("Tarea actualizada: " + oldName + " ahora es " + newName);
        } catch (TaskException e) {
            view.printMessage("Error: " + e.getMessage());
        }
    }

    public void deleteTask(int index) {
        try {
            Task task = findTask(index);
            tasks.remove(index);
            view.printMessage("Tarea eliminada: " + task.getName());
        } catch (TaskException e) {
            view.printMessage("Error: " + e.getMessage());
        }
    }

    public void saveTasks() {
        try {
            storage.save(tasks);
            view.printMessage("Tareas guardadas: " + tasks.size());
        } catch (TaskException e) {
            view.printMessage("Error: " + e.getMessage());
        }
    }

    public void loadTasks() {
        try {
            tasks = storage.load();
            view.printMessage("Tareas cargadas: " + tasks.size());
        } catch (TaskException e) {
            view.printMessage("Error: " + e.getMessage());
        }
    }

    public void displayTasks() {
        view.printTasks(tasks);
    }

    private Task findTask(int index) throws TaskException {
        if (index < 0 || index >= tasks.size()) {
            throw new TaskException("no existe una tarea con el indice " + index);
        }
        return tasks.get(index);
    }
}
