set demo_component test/mesa_demo/hello_gl
set demo_binary    hello_gl
set demo_ram_quota 32M
set demo_caps      200

set demo_config {
<config ld_verbose="true">
	<libc stdout="/dev/log" stderr="/dev/log"/>
	<vfs>
		<dir name="dev"> <log/> </dir>
		<rom name="hello1.tga"/>
		<rom name="hello2.tga"/>
		<rom name="hello-gl.f.glsl"/>
		<rom name="hello-gl.v.glsl"/>
	</vfs>
</config>}

set demo_modules {
	hello_gl
	hello1.tga
	hello2.tga
	hello-gl.f.glsl
	hello-gl.v.glsl
}

source ${genode_dir}/repos/libports/run/mesa.inc
