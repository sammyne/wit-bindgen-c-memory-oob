use std::path::PathBuf;

use anyhow::Context;
use clap::Parser;
use wasmtime::component::*;
use wasmtime::{Config, Engine, Store};
use wasmtime_wasi::WasiCtxBuilder;

wasmtime::component::bindgen!({
    path: "../wit/world.wit",
    world: "greeter",
    async: true
});

#[async_std::main]
async fn main() -> anyhow::Result<()> {
    let App { path } = App::parse();

    let mut config = Config::default();
    config.wasm_component_model(true);
    config.async_support(true);
    let engine = Engine::new(&config)?;
    let mut linker = Linker::new(&engine);

    // Add the command world (aka WASI CLI) to the linker
    wasmtime_wasi::add_to_linker_async(&mut linker).context("Failed to link command world")?;
    let ctx = WasiCtxBuilder::new().inherit_stdout().build_p1();
    let mut store = Store::new(&engine, ctx);

    let component = Component::from_file(&engine, path).context("Component file not found")?;

    let (instance, _) = Greeter::instantiate_async(&mut store, &component, &linker)
        .await
        .context("instantiate world")?;

    const WHO: &str = "sammyne";

    let out = instance
        .call_greet(&mut store, WHO)
        .await
        .context("call func greet")?;
    println!("out = {out}");

    let out = instance.call_say_hi(&mut store).await.context("call func say-hi")?;
    println!("---");
    println!("out = {out}");

    let out = instance.call_greet_cc(&mut store, WHO).await.context("call func greet-cc")?;
    println!("---");
    println!("out = {out}");

    Ok(())
}

/// A CLI for executing WebAssembly components that
/// implement the `example` world.
#[derive(Parser)]
#[clap(name = "cli", version = env!("CARGO_PKG_VERSION"))]
struct App {
    /// The path to the component.
    #[clap(value_name = "COMPONENT_PATH")]
    path: PathBuf,
}
