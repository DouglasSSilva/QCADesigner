################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/objects/QCADesigner-QCADCell.o \
../src/objects/QCADesigner-QCADCellRendererLayerList.o \
../src/objects/QCADesigner-QCADCellRendererVT.o \
../src/objects/QCADesigner-QCADClockCombo.o \
../src/objects/QCADesigner-QCADCompoundDO.o \
../src/objects/QCADesigner-QCADDOContainer.o \
../src/objects/QCADesigner-QCADDesignObject.o \
../src/objects/QCADesigner-QCADLabel.o \
../src/objects/QCADesigner-QCADLayer.o \
../src/objects/QCADesigner-QCADPrintDialog.o \
../src/objects/QCADesigner-QCADRuler.o \
../src/objects/QCADesigner-QCADStretchyObject.o \
../src/objects/QCADesigner-QCADSubstrate.o \
../src/objects/QCADesigner-QCADTreeViewContainer.o \
../src/objects/QCADesigner-QCADUndoEntry.o \
../src/objects/QCADesigner-QCADUndoEntryGroup.o \
../src/objects/QCADesigner-mouse_handlers.o \
../src/objects/QCADesigner-object_helpers.o \
../src/objects/batch_sim-QCADCell.o \
../src/objects/batch_sim-QCADCompoundDO.o \
../src/objects/batch_sim-QCADDOContainer.o \
../src/objects/batch_sim-QCADDesignObject.o \
../src/objects/batch_sim-QCADLabel.o \
../src/objects/batch_sim-QCADLayer.o \
../src/objects/batch_sim-QCADRuler.o \
../src/objects/batch_sim-QCADStretchyObject.o \
../src/objects/batch_sim-QCADSubstrate.o \
../src/objects/batch_sim-object_helpers.o \
../src/objects/graph_dialog-QCADCell.o \
../src/objects/graph_dialog-QCADClockCombo.o \
../src/objects/graph_dialog-QCADCompoundDO.o \
../src/objects/graph_dialog-QCADDOContainer.o \
../src/objects/graph_dialog-QCADDesignObject.o \
../src/objects/graph_dialog-QCADLabel.o \
../src/objects/graph_dialog-QCADLayer.o \
../src/objects/graph_dialog-QCADPrintDialog.o \
../src/objects/graph_dialog-QCADRuler.o \
../src/objects/graph_dialog-QCADStretchyObject.o \
../src/objects/graph_dialog-QCADSubstrate.o \
../src/objects/graph_dialog-object_helpers.o 

C_SRCS += \
../src/objects/QCADCell.c \
../src/objects/QCADCellRendererLayerList.c \
../src/objects/QCADCellRendererVT.c \
../src/objects/QCADClockCombo.c \
../src/objects/QCADCompoundDO.c \
../src/objects/QCADDOContainer.c \
../src/objects/QCADDesignObject.c \
../src/objects/QCADLabel.c \
../src/objects/QCADLayer.c \
../src/objects/QCADPrintDialog.c \
../src/objects/QCADRuler.c \
../src/objects/QCADStretchyObject.c \
../src/objects/QCADSubstrate.c \
../src/objects/QCADTreeViewContainer.c \
../src/objects/QCADUndoEntry.c \
../src/objects/QCADUndoEntryGroup.c \
../src/objects/mouse_handlers.c \
../src/objects/object_helpers.c 

OBJS += \
./src/objects/QCADCell.o \
./src/objects/QCADCellRendererLayerList.o \
./src/objects/QCADCellRendererVT.o \
./src/objects/QCADClockCombo.o \
./src/objects/QCADCompoundDO.o \
./src/objects/QCADDOContainer.o \
./src/objects/QCADDesignObject.o \
./src/objects/QCADLabel.o \
./src/objects/QCADLayer.o \
./src/objects/QCADPrintDialog.o \
./src/objects/QCADRuler.o \
./src/objects/QCADStretchyObject.o \
./src/objects/QCADSubstrate.o \
./src/objects/QCADTreeViewContainer.o \
./src/objects/QCADUndoEntry.o \
./src/objects/QCADUndoEntryGroup.o \
./src/objects/mouse_handlers.o \
./src/objects/object_helpers.o 

C_DEPS += \
./src/objects/QCADCell.d \
./src/objects/QCADCellRendererLayerList.d \
./src/objects/QCADCellRendererVT.d \
./src/objects/QCADClockCombo.d \
./src/objects/QCADCompoundDO.d \
./src/objects/QCADDOContainer.d \
./src/objects/QCADDesignObject.d \
./src/objects/QCADLabel.d \
./src/objects/QCADLayer.d \
./src/objects/QCADPrintDialog.d \
./src/objects/QCADRuler.d \
./src/objects/QCADStretchyObject.d \
./src/objects/QCADSubstrate.d \
./src/objects/QCADTreeViewContainer.d \
./src/objects/QCADUndoEntry.d \
./src/objects/QCADUndoEntryGroup.d \
./src/objects/mouse_handlers.d \
./src/objects/object_helpers.d 


# Each subdirectory must supply rules for building sources it contributes
src/objects/%.o: ../src/objects/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


