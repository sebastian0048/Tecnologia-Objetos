import java.util.List;

// Abstraccion generica de almacenamiento: el controlador no sabe donde se guardan los datos.
public interface Storage<T> {
    void save(List<T> items) throws TaskException;

    List<T> load() throws TaskException;
}
