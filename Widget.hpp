#ifndef WIDGET_H
#define WIDGET_H

#include "Panel.hpp"
#include "Vector2D.hpp"

namespace Ui {

    class Widget{

        public:
            virtual void Show() = 0;
            virtual void Refresh() = 0;
            virtual void Destroy() = 0;

        protected:
            Panel* m_Container;
    };
}

#endif // WIDGET_H
