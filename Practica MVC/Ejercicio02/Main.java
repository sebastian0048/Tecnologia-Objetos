public class Main {
    public static void main(String[] args) {
        TaskView view = new TaskView();
        Storage<Task> storage = new FileTaskStorage("tareas.txt");
        TaskController controller = new TaskController(view, storage);

        controller.addTask("Estudiar el patron MVC");
        controller.addTask("Preparar la exposicion");
        controller.addTask("Revisar el informe");
        controller.addTask("Comprar materiales");
        System.out.println();
        controller.displayTasks();

        System.out.println();
        controller.completeTask(0);
        controller.updateTask(1, "Preparar las diapositivas");
        controller.deleteTask(3);
        controller.deleteTask(7);
        System.out.println();
        controller.displayTasks();

        System.out.println();
        controller.saveTasks();

        // Un controlador nuevo empieza vacio y recupera las tareas desde el archivo.
        System.out.println();
        TaskController otherController = new TaskController(view, storage);
        otherController.displayTasks();
        otherController.loadTasks();
        otherController.displayTasks();
    }
}
