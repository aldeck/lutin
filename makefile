TYPE = APP

NAME = Lutin

SRCS = App.cpp
SRCS += MainWindow.cpp
SRCS += MathUtils.cpp
SRCS += RenderView.cpp
SRCS += Sprite.cpp

LIBS = be game media translation

RDEFS = Lutin.rdef

## include the makefile-engine
include $(BUILDHOME)/etc/makefile-engine
