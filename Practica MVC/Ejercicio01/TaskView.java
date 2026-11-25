import java.util.List;

// Vista: solo muestra informacion
public class TaskView {
    public void printTasks(List<Task> tasks) {
        System.out.println("Lista de tareas:");
        for (int i = 0; i < tasks.size(); i++) {
            Task task = tasks.get(i);
            // Pendiente lleva un espacio extra para que los nombres queden alineados.
            String status = task.isCompleted() ? "Completada" : "Pendiente ";
            System.out.println("  " + i + "  " + status + "  " + task.getName());
        }
    }

    public void printMessage(String message) {
        System.out.println(message);
    }
}
