#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "Async.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class AsyncSampleApp : public App {
public:
    static void prepareSettings(Settings* settings);
    void draw() override;
    void mouseDown( MouseEvent event ) override;
};

void AsyncSampleApp::prepareSettings(Settings* settings)
{
    settings->setMultiTouchEnabled(false);
}

void AsyncSampleApp::mouseDown( MouseEvent event )
{
    auto bgCall = [&](){
        console() << "Called async function in thread: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    };
    
    auto callback = [&](){
        console() << "Got callback in thread: " << std::this_thread::get_id() << std::endl;
    };
    
    Async::call(bgCall, callback);
}

void AsyncSampleApp::draw()
{
    // random animation to show the app doesn't freeze
    gl::clear(Color(0, 0, 0));
    gl::color(1, 1, 0);
    gl::drawSolidCircle(getWindowCenter() + vec2(sin(getElapsedSeconds()), cos(getElapsedSeconds())) * 50.0f, 10);
}

CINDER_APP( AsyncSampleApp, RendererGl, &AsyncSampleApp::prepareSettings )
