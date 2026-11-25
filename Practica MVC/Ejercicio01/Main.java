public class Main {
    public static void main(String[] args) {
        TaskView view = new TaskView();
        TaskController controller = new TaskController(view);

        controller.addTask("Estudiar el patron MVC");
        controller.addTask("Preparar la exposicion");
        controller.addTask("Revisar el informe");
        System.out.println();
        controller.displayTasks();

        System.out.println();
        controller.completeTask(0);
        controller.completeTask(5);
        System.out.println();
        controller.displayTasks();
    }
}
