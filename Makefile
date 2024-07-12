
WASI_SDK_PATH=/opt/wasi-sdk

CC=$(WASI_SDK_PATH)/bin/clang++ --sysroot=$(WASI_SDK_PATH)/share/wasi-sysroot

GUEST_DIR=guest-c
HOST_DIR=host-rs

bindgen:
	rm -rf $(GUEST_DIR)/bindings
	wit-bindgen c --out-dir $(GUEST_DIR)/bindings wit

modularize: bindgen
	rm -rf out
	mkdir -p out
	$(CC) -std=c++11 -I$(GUEST_DIR) $(GUEST_DIR)/bindings/greeter.c $(GUEST_DIR)/bindings/greeter_component_type.o $(GUEST_DIR)/src/greeter.c $(GUEST_DIR)/src/greeter.cc -o out/greeter.wasm -mexec-model=reactor

componentize: modularize
	wasm-tools component new out/greeter.wasm -o out/greeter.component.wasm --adapt /opt/wasmtime/adapter-modules/wasi_snapshot_preview1.reactor.wasm

run: componentize
	cd $(HOST_DIR) && cargo build
	$(HOST_DIR)/target/debug/cli out/greeter.component.wasm
