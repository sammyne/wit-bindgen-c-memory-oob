
WASI_SDK_PATH=/opt/wasi-sdk

CC=$(WASI_SDK_PATH)/bin/clang --sysroot=$(WASI_SDK_PATH)/share/wasi-sysroot

GUEST_DIR=guest-c

bindgen:
	wit-bindgen c --out-dir $(GUEST_DIR)/bindings wit

modularize:
	mkdir -p out
	$(CC) -I$(GUEST_DIR) $(GUEST_DIR)/bindings/greeter.c $(GUEST_DIR)/bindings/greeter_component_type.o $(GUEST_DIR)/src/greeter.c -o out/greeter.wasm -mexec-model=reactor

componentize:
	wasm-tools component new out/greeter.wasm -o out/greeter.component.wasm --adapt ./wasi_snapshot_preview1.reactor.wasm
