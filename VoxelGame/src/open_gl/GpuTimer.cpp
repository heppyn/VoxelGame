#include "GpuTimer.h"

#include <glad/glad.h>

OpenGl::GpuTimer::GpuTimer() {
    glGenQueries(2, QueryId_);
}

void OpenGl::GpuTimer::Start() const {
    glQueryCounter(QueryId_[0], GL_TIMESTAMP);
}
void OpenGl::GpuTimer::Stop() {
    glQueryCounter(QueryId_[1], GL_TIMESTAMP);

    int available = 0;
    while (!available) {
        glGetQueryObjectiv(QueryId_[1], GL_QUERY_RESULT_AVAILABLE, &available);
    }

    Stopped_ = true;
}
long long OpenGl::GpuTimer::Time() {
    if (!Stopped_)
        Stop();

    long long start, stop;

    glGetQueryObjecti64v(QueryId_[0], GL_QUERY_RESULT, &start);
    glGetQueryObjecti64v(QueryId_[1], GL_QUERY_RESULT, &stop);

    return stop - start;
}

float OpenGl::GpuTimer::TimeMs() {
    const auto time = Time();

    return time / 1000000.0f;
}
