#pragma once

namespace test {

    class Test {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float elapsedTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

}