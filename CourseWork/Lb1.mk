##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Lb1
ConfigurationName      :=Debug
WorkspacePath          :=/home/stud/C++Projects
ProjectPath            :=/home/stud/C++Projects/Lb1
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=01/21/24
CodeLitePath           :=/home/stud/.codelite
LinkerName             :=/usr/bin/g++-10
SharedObjectLinkerName :=/usr/bin/g++-10 -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="Lb1.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)UnitTest++ 
ArLibs                 :=  "UnitTest++" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++-10
CC       := /usr/bin/gcc-10
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/tests.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/server.cpp$(ObjectSuffix) $(IntermediateDirectory)/auth.cpp$(ObjectSuffix) $(IntermediateDirectory)/errors.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)


$(IntermediateDirectory)/.d:
	@test -d $(ConfigurationName) || $(MakeDirCommand) $(ConfigurationName)

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/tests.cpp$(ObjectSuffix): tests.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tests.cpp$(DependSuffix) -MM tests.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/stud/C++Projects/Lb1/tests.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests.cpp$(PreprocessSuffix): tests.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests.cpp$(PreprocessSuffix) tests.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/stud/C++Projects/Lb1/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/server.cpp$(ObjectSuffix): server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/server.cpp$(DependSuffix) -MM server.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/stud/C++Projects/Lb1/server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server.cpp$(PreprocessSuffix): server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server.cpp$(PreprocessSuffix) server.cpp

$(IntermediateDirectory)/auth.cpp$(ObjectSuffix): auth.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/auth.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/auth.cpp$(DependSuffix) -MM auth.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/stud/C++Projects/Lb1/auth.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/auth.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/auth.cpp$(PreprocessSuffix): auth.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/auth.cpp$(PreprocessSuffix) auth.cpp

$(IntermediateDirectory)/errors.cpp$(ObjectSuffix): errors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/errors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/errors.cpp$(DependSuffix) -MM errors.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/stud/C++Projects/Lb1/errors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/errors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/errors.cpp$(PreprocessSuffix): errors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/errors.cpp$(PreprocessSuffix) errors.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


