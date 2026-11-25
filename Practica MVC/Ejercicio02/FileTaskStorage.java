import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

// Guarda cada tarea en una linea con el formato estado;nombre.
public class FileTaskStorage implements Storage<Task> {
    private Path path;

    public FileTaskStorage(String fileName) {
        this.path = Paths.get(fileName);
    }

    @Override
    public void save(List<Task> tasks) throws TaskException {
        List<String> lines = new ArrayList<>();
        for (Task task : tasks) {
            lines.add(task.isCompleted() + ";" + task.getName());
        }
        try {
            Files.write(path, lines, StandardCharsets.UTF_8);
        } catch (IOException e) {
            throw new TaskException("no se pudo guardar el archivo " + path);
        }
    }

    @Override
    public List<Task> load() throws TaskException {
        if (!Files.exists(path)) {
            throw new TaskException("no existe el archivo " + path);
        }
        List<Task> tasks = new ArrayList<>();
        try {
            for (String line : Files.readAllLines(path, StandardCharsets.UTF_8)) {
                // El limite 2 conserva los punto y coma que pueda tener el nombre de la tarea.
                String[] parts = line.split(";", 2);
                if (parts.length == 2) {
                    tasks.add(new Task(parts[1], Boolean.parseBoolean(parts[0])));
                }
            }
        } catch (IOException e) {
            throw new TaskException("no se pudo leer el archivo " + path);
        }
        return tasks;
    }
}
