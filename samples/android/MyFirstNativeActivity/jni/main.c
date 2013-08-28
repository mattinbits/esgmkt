/*
 * main.c
 *
 *  Created on: 5 Aug 2013
 *      Author: matthew.livesey
 */

#include <android/log.h>
#include <android_native_app_glue.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <time.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "NativeActivitySimpleExample", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#define  LOGE(...) ((void) __android_log_print(ANDROID_LOG_ERROR,"NativeActivitySimpleExample",__VA_ARGS__))


EGLDisplay display;
EGLSurface surface;
EGLContext context;
int32_t width;
int32_t height;

double startTime;

static double now_ms(void) {

    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;

}



typedef  struct Background  {
	void * data;
	int (* draw)();
} Background;

Background current_background;

typedef  struct ChangingBackgroundData {
    float period;
} ChangingBackgroundData;

typedef  struct StaticUniformBackgroundData {
    float r;
    float g;
    float b;
} StaticUniformBackgroundData;

static int drawChangingBackground( Background* self)
{

	ChangingBackgroundData* ptr_data = (ChangingBackgroundData *)self->data;
	float period = ptr_data->period;
	// LOGI("period: %f", period);
	// LOGI(" draw pointer to data: %d", ptr_data);
	float currentTime = now_ms()-startTime;
	float rcurrentModulo = fmod(currentTime,period)+period/4.0;
	float rvalue=0.0;
	float gcurrentModulo = fmod(currentTime+period/3.0,period)+period/4.0;
	float gvalue=0.0;
	float bcurrentModulo= fmod(currentTime/2,period)+period/4.0;
	float bvalue=0.0;
	if(rcurrentModulo< (period * 5.0/8.0))
	{
		rvalue=rcurrentModulo/(period*3.0/4.0);
	}else
	{
		rvalue=((period*5.0/4.0)-rcurrentModulo)/(period*3.0/4.0);
	}
	if(gcurrentModulo<(period * 5.0/8.0))
	{
		gvalue=gcurrentModulo/(period*3.0/4.0);
	}else
	{
		gvalue=(period*5.0/4.0-gcurrentModulo)/(period*3.0/4.0);
	}
	if(bcurrentModulo<(period * 5.0/8.0))
	{
		bvalue=bcurrentModulo/(period*3.0/4.0);
	}else
	{
		bvalue=(period*5.0/4.0-bcurrentModulo)/(period*3.0/4.0);
	}

	//LOGI("Rvalue is %f",rvalue);
	glClearColor(rvalue, gvalue,bvalue, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	return 0;
}

static Background New_ChangingBackground( float period)
{
	ChangingBackgroundData* ptr_data = (ChangingBackgroundData*) malloc(sizeof(ChangingBackgroundData));
	LOGI("Period in constructor: %f", period);
	(*ptr_data).period=period;
	LOGI("Period in constructor mark 2: %f", (*ptr_data).period);
	LOGI("pointer to data: %d", ptr_data);
	Background background;
	background.draw=drawChangingBackground;
	background.data= ptr_data;
	return background;
}

static void Destroy_Background(Background* background)
{
	free(background->data);
}

static int drawStaticUniformBackground( Background* self)
{
	 StaticUniformBackgroundData* ptr_data = (StaticUniformBackgroundData *)self->data;
	 LOGI("r, g, b: %f %f %f",ptr_data->r, ptr_data->g, ptr_data->b);
	 glClearColor(ptr_data->r, ptr_data->g, ptr_data->b , 1.0);
	 //glClearColor(1.0,0.0,0.0, 1.0);
	 glClear(GL_COLOR_BUFFER_BIT);
	 return 0;
}


static  Background New_StaticUniformBackground(float r, float g, float b)
{
	 StaticUniformBackgroundData* ptr_data = (StaticUniformBackgroundData*) malloc(sizeof(StaticUniformBackgroundData));
	(*ptr_data).r=r;
	(*ptr_data).g=g;
	ptr_data->b=b;
	//LOGI("r, g, b: %f %f %f",data.r, data.g, data.b);
	Background background;
	background.draw=drawStaticUniformBackground;
	background.data= ptr_data;
	return background;
}

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}



static const char gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char gFragmentShader[] =
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";


static int setupGraphics(struct android_app* app)
{
	const EGLint attribs[] = {
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_BLUE_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_RED_SIZE, 8,
	EGL_DEPTH_SIZE, 16,
	EGL_STENCIL_SIZE,0,
	EGL_NONE
	};
	EGLint numConfigs;
	EGLConfig config;
	 display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);
   // LOGI("Choosing Config");

    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    char message [16];
    //snprintf(message, 16,"Num configs: %d",numConfigs);
   //LOGI("Num configs: %d",numConfigs);
   // LOGI(message);
    //LOGI("Config chosen");

    EGLint  dummy, format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    //LOGI("Config Attributes gotten");
    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);
    //LOGI("Buffers geom set");
    surface = eglCreateWindowSurface(display, config, app->window, NULL);
    //LOGI("surface built");
    context = eglCreateContext(display, config, NULL, NULL);
    //LOGI("Context built");
    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
            LOGW("Unable to eglMakeCurrent");
            return -1;
     }
    LOGI("Executed Make Current");
    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);
    //LOGI("Width: %d",width);
    //LOGI("Height: %d",height);
    // Initialize GL state.
        //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
        glEnable(GL_CULL_FACE);
       // glShadeModel(GL_SMOOTH);
        glDisable(GL_DEPTH_TEST);

        //current_background = New_ChangingBackground(4000.0f);
        current_background = New_StaticUniformBackground(1.0,0.0,0.0);
        return 0;
}

static void tearDownGraphics(struct android_app* app) {
    if (display != EGL_NO_DISPLAY) {
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context != EGL_NO_CONTEXT) {
            eglDestroyContext(display,context);
        }
        if (EGL_NO_SURFACE) {
            eglDestroySurface(display, surface);
        }
        eglTerminate(display);
    }

    display = EGL_NO_DISPLAY;
    context = EGL_NO_CONTEXT;
    surface = EGL_NO_SURFACE;

    Destroy_Background(&current_background);
}

static void handle_cmd(struct android_app* app, int32_t cmd) {
	LOGI("Command occurred");
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            // The window is being shown, get it ready.
        	LOGI("Init Window Command occurred");
            if (app->window != NULL) {
                setupGraphics(app);
            }break;
        case APP_CMD_TERM_WINDOW:
            // The window is being hidden or closed, clean it up.
        	LOGI("Init Window Command occurred");
        	tearDownGraphics(app);
            break;
    }
}

static int32_t handle_input(struct android_app* app, AInputEvent* event) {
	LOGI("Input occurred");
    return 0;
}


void drawFrame()
{
	if (display == NULL || display == EGL_NO_DISPLAY) {
		// No display.
		//LOGI("No display");
		return;
	}


	current_background.draw(&current_background);
	//LOGI("TICK");
	eglSwapBuffers(display,surface);
}

void android_main(struct android_app* app)
{
	// Make sure glue isn't stripped.
	app_dummy();
	 display = EGL_NO_DISPLAY;
	 context = EGL_NO_CONTEXT;
	 surface = EGL_NO_SURFACE;
	 startTime=now_ms();
	app->onAppCmd = handle_cmd;
	app->onInputEvent = handle_input;
	LOGI("In Main");
	//printGLString("Version", GL_VERSION);
	//printGLString("Vendor", GL_VENDOR);
	//printGLString("Renderer", GL_RENDERER);
	//printGLString("Extensions", GL_EXTENSIONS);

	while(1)
	{
		int ident;
		int fdesc;
		int events;
		struct android_poll_source* source;

		while((ident = ALooper_pollAll(0, &fdesc, &events, (void**)&source)) >= 0)
		{
			 LOGI("event!");
			// process this event
			 if (source)
			 {
				source->process(app, source);
			 }
			 if (app->destroyRequested != 0) {
				tearDownGraphics(app);
				 return;
			 }
		}
		//LOGI("After event loop");
		drawFrame();
	}
}


