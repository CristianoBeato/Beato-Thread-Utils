# Beato-ThreadUtils
a set of utilities made in c++ for multi threaded tasks, with SDL2 based portability
- Base class for simple thread based implementation.
- Mutexes, Conditions e semaphores classes to easy the implement.
- Auto Lock (RAII), mutexes locks and unloks, with auto initialization and shutdown for easy control.
- Task queue based worker thread.
- Demultiplexer thread, for event driven queue (Reactor pattern).
- Reference counting.
- intrusive pointer with reference counting, with auto deletion for garbage collection.

# Beato-ThreadUtils
um conjunto de utlidades em c++ para programação em multitarefa, com portabilidade baseada na biblioteca SDL2.

- Classe base para implementação baseada em thread simples.
- Mutexes, Conditions e semaphores baseados em classes para facil implementação.
- Auto Lock (RAII), locks e unloks de mutex com inicialisação e finalização automatica para facil controle;
- Thread consumidora baseada em fila de tarefas.
- Thread demultiplexadora de fila de eventos (Reactor pattern).
- contagem de referencias.
- ponteiro intrusivo com contagem de referencias e auto deleção, para garbage collection.
