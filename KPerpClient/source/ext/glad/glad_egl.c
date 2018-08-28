/*

    EGL loader generated by glad 0.1.25 on Wed Jul 25 11:55:57 2018.

    Language/Generator: C/C++
    Specification: egl
    APIs: egl=1.4
    Profile: -
    Extensions:
        
    Loader: True
    Local files: False
    Omit khrplatform: True

    Commandline:
        --api="egl=1.4" --generator="c" --spec="egl" --omit-khrplatform --extensions=""
    Online:
        http://glad.dav1d.de/#language=c&specification=egl&loader=on&api=egl%3D1.4
*/
#ifdef __ANDROID__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad_egl.h>

int gladLoadEGL(void) {
    return gladLoadEGLLoader((GLADloadproc)eglGetProcAddress);
}

static int find_extensionsEGL(void) {
	return 1;
}

static void find_coreEGL(void) {
}

int gladLoadEGLLoader(GLADloadproc load) {
	(void) load;
	find_coreEGL();

	if (!find_extensionsEGL()) return 0;
	return 1;
}

#endif