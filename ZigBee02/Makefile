#
# OMNeT++/OMNEST Makefile for ZigBee02
#
# This file was generated with the command:
#  opp_makemake -f --deep -O out
#

# Name of target to be created (-o option)
TARGET = ZigBee02$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = -I. -IdeterminedMesh -InwkMesh -InwkTree

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/collector.o \
    $O/nwkMesh/nwkMeshDenialOfSleep.o \
    $O/nwkMesh/nwkMeshNormal.o \
    $O/nwkMesh/nwkMeshRepeatedTransmission.o \
    $O/nwkMesh/nwkMeshRepeatedTransmissionExactDest.o \
    $O/nwkMesh/nwkMeshRepeatedTransmissionExactSrc.o \
    $O/nwkMesh/nwkMeshSelectiveForward.o \
    $O/nwkMesh/nwkMeshSelectiveForwardExactDest.o \
    $O/nwkMesh/nwkMeshSelectiveForwardExactSrc.o \
    $O/nwkMesh/nwkMeshSpoofing.o \
    $O/nwkMesh/nwkMeshSpoofingExactDest.o \
    $O/nwkMesh/nwkMeshSpoofingExactSrc.o \
    $O/nwkMesh/nwkMeshWormhole.o \
    $O/nwkTree/address_helper.o \
    $O/nwkTree/nwkTreeDenialOfSleep.o \
    $O/nwkTree/nwkTreeRepeatedTransmission.o \
    $O/nwkTree/nwkTreeRepeatedTransmissionExactDest.o \
    $O/nwkTree/nwkTreeRepeatedTransmissionExactSrc.o \
    $O/nwkTree/nwkTreeSelectiveForward.o \
    $O/nwkTree/nwkTreeSelectiveForwardExactDest.o \
    $O/nwkTree/nwkTreeSelectiveForwardExactSrc.o \
    $O/nwkTree/nwkTreeSpoofing.o \
    $O/nwkTree/nwkTreeSpoofingExactDest.o \
    $O/nwkTree/nwkTreeSpoofingExactSrc.o \
    $O/nwkTree/nwkTreeWormhole.o \
    $O/nwkTree/nwkTreeNormal.o \
    $O/nwkMesh/mac_frame_m.o \
    $O/nwkMesh/nwkPacket_m.o \
    $O/nwkTree/address_appointment_m.o \
    $O/nwkTree/mac_frameTree_m.o \
    $O/nwkTree/nwkPacketTree_m.o

# Message files
MSGFILES = \
    nwkMesh/mac_frame.msg \
    nwkMesh/nwkPacket.msg \
    nwkTree/address_appointment.msg \
    nwkTree/mac_frameTree.msg \
    nwkTree/nwkPacketTree.msg

# SM files
SMFILES =

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f ZigBee02 ZigBee02.exe libZigBee02.so libZigBee02.a libZigBee02.dll libZigBee02.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h
	$(Q)-rm -f determinedMesh/*_m.cc determinedMesh/*_m.h determinedMesh/*_sm.cc determinedMesh/*_sm.h
	$(Q)-rm -f nwkMesh/*_m.cc nwkMesh/*_m.h nwkMesh/*_sm.cc nwkMesh/*_sm.h
	$(Q)-rm -f nwkTree/*_m.cc nwkTree/*_m.h nwkTree/*_sm.cc nwkTree/*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc determinedMesh/*.cc nwkMesh/*.cc nwkTree/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/collector.o: collector.cc \
	collector.h
$O/nwkMesh/mac_frame_m.o: nwkMesh/mac_frame_m.cc \
	nwkMesh/mac_frame_m.h
$O/nwkMesh/nwkMeshDenialOfSleep.o: nwkMesh/nwkMeshDenialOfSleep.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshNormal.o: nwkMesh/nwkMeshNormal.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshRepeatedTransmission.o: nwkMesh/nwkMeshRepeatedTransmission.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshRepeatedTransmissionExactDest.o: nwkMesh/nwkMeshRepeatedTransmissionExactDest.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshRepeatedTransmissionExactSrc.o: nwkMesh/nwkMeshRepeatedTransmissionExactSrc.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshSelectiveForward.o: nwkMesh/nwkMeshSelectiveForward.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshSelectiveForwardExactDest.o: nwkMesh/nwkMeshSelectiveForwardExactDest.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshSelectiveForwardExactSrc.o: nwkMesh/nwkMeshSelectiveForwardExactSrc.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshSpoofing.o: nwkMesh/nwkMeshSpoofing.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshSpoofingExactDest.o: nwkMesh/nwkMeshSpoofingExactDest.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshSpoofingExactSrc.o: nwkMesh/nwkMeshSpoofingExactSrc.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkMeshWormhole.o: nwkMesh/nwkMeshWormhole.cc \
	collector.h \
	nwkMesh/mac_frame_m.h \
	nwkMesh/nwkMeshNormal.h \
	nwkMesh/nwkPacket_m.h
$O/nwkMesh/nwkPacket_m.o: nwkMesh/nwkPacket_m.cc \
	nwkMesh/nwkPacket_m.h
$O/nwkTree/address_appointment_m.o: nwkTree/address_appointment_m.cc \
	nwkTree/address_appointment_m.h
$O/nwkTree/address_helper.o: nwkTree/address_helper.cc \
	nwkTree/address_helper.h
$O/nwkTree/mac_frameTree_m.o: nwkTree/mac_frameTree_m.cc \
	nwkTree/mac_frameTree_m.h
$O/nwkTree/nwkPacketTree_m.o: nwkTree/nwkPacketTree_m.cc \
	nwkTree/nwkPacketTree_m.h
$O/nwkTree/nwkTreeDenialOfSleep.o: nwkTree/nwkTreeDenialOfSleep.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeNormal.o: nwkTree/nwkTreeNormal.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeRepeatedTransmission.o: nwkTree/nwkTreeRepeatedTransmission.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeRepeatedTransmissionExactDest.o: nwkTree/nwkTreeRepeatedTransmissionExactDest.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeRepeatedTransmissionExactSrc.o: nwkTree/nwkTreeRepeatedTransmissionExactSrc.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeSelectiveForward.o: nwkTree/nwkTreeSelectiveForward.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeSelectiveForwardExactDest.o: nwkTree/nwkTreeSelectiveForwardExactDest.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeSelectiveForwardExactSrc.o: nwkTree/nwkTreeSelectiveForwardExactSrc.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeSpoofing.o: nwkTree/nwkTreeSpoofing.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeSpoofingExactDest.o: nwkTree/nwkTreeSpoofingExactDest.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeSpoofingExactSrc.o: nwkTree/nwkTreeSpoofingExactSrc.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h
$O/nwkTree/nwkTreeWormhole.o: nwkTree/nwkTreeWormhole.cc \
	collector.h \
	nwkTree/address_appointment_m.h \
	nwkTree/address_helper.h \
	nwkTree/mac_frameTree_m.h \
	nwkTree/nwkPacketTree_m.h \
	nwkTree/nwkTreeNormal.h

