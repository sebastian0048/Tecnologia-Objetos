// Error propio de la gestion de tareas: indice inexistente o fallo al usar el archivo.
public class TaskException extends Exception {
    public TaskException(String message) {
        super(message);
    }
}
