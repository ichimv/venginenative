#include "stdafx.h"
#include "Application.h"
#include "Media.h"

Application * Application::instance = nullptr;

Application::Application(int windowwidth, int windowheight)
{
	instance = this;
	frame = 0;
	width = windowwidth;
	height = windowheight;
	invokeQueue = queue<function<void(void)>>();
	onRenderFrame = {};
	asset = new AssetLoader();
	scene = new Scene();
	onRenderFrame = EventHandler<int>();
	onWindowResize = EventHandler<int>();
	idMap = unordered_map<int, void*>();
	hasExited = false;
	vulkan = new VulkanToolkit();
	vulkan->initialize();
	//auto data = readFileImageData(path);
	ImageData *img = new ImageData();
	img->width = 1;
	img->height = 1;
	unsigned char * emptytexture = new unsigned char[4]{ (unsigned char)0x255, (unsigned char)0x255, (unsigned char)0x255, (unsigned char)0x255 };
	img->data = (void*)emptytexture;
	dummyTexture = vulkan->createTexture(img);
	renderer = new Renderer(width, height);
}

Application::~Application()
{
}

void Application::start()
{

	glfwSetWindowSizeCallback(vulkan->window, [](GLFWwindow* window, int width, int height) -> void {
		Application::instance->width = width;
		Application::instance->height = height;
	});

	shouldClose = false;
	int frames = 0;
	double lastTime = 0.0;
	while (!glfwWindowShouldClose(vulkan->window) && !shouldClose)
	{
		frames++;
		double nowtime = floor(glfwGetTime());
		if (nowtime != lastTime) {
			printf("FPS %d\n", frames);
			frames = 0;
		}
		lastTime = nowtime;

		if (shouldClose) break;
		onRenderFrameFunc();

		glfwPollEvents();
	}
	delete vulkan;
	glfwTerminate();
	shouldClose = true;
	hasExited = true;
}

unsigned int Application::getNextId()
{
	return lastId++;
}
void * Application::getObjectById(unsigned int id)
{
	return idMap[id];
}

void Application::registerId(unsigned int id, void * p)
{
	idMap[id] = p;
}

void Application::invoke(const function<void(void)> &func)
{
	invokeQueue.push(func);
}

void Application::onRenderFrameFunc()
{
	if (mainDisplayCamera != nullptr) {
		time = glfwGetTime(); 

		if (vpmatrixUpdateFrameId != frame) {
			viewProjMatrix = mainDisplayCamera->projectionMatrix * mainDisplayCamera->transformation->getInverseWorldTransform();
			vpmatrixUpdateFrameId = frame;
		}

		while (invokeQueue.size() > 0) {
			invokeQueue.front()();
			invokeQueue.pop();
		}
		onRenderFrame.invoke(0);
		
		renderer->renderToSwapChain(mainDisplayCamera);

		frame++;
	}
}