#ifndef Histo1DDataMCRatio_h
#define Histo1DDataMCRatio_h


#include "interface/Histo1D.h"
#include "interface/Figure.h"

namespace theDoctor
{

    class Histo1DDataMCRatio : public Histo1D 
    {

        public:

        Histo1DDataMCRatio(Variable* theVar_, 
                           Region* theRegion_, 
                           Channel* theChannel_,
                           Histo1D* theSumData,
                           Histo1D* theSumBackground) : 
        Histo1D(Name("1DDataMCRatio","Data/MC"),theVar_,theRegion_,theChannel_)
        {
            string nameHisto =  string("v:")+theVar->getTag()
                +"|r:" +theRegion->getTag()
                +"|c:" +theChannel->getTag()
                +"|t:" +theHistoType.getTag();

            theHisto->SetName(nameHisto.c_str());

            theHisto->Add(theSumData->getClone());
            theHisto->Divide(theSumBackground->getClone());
        
        } 

        ~Histo1DDataMCRatio() { }

        static void GetHistoDependencies(vector<pair<string,string> >& output, string options = "")
        {
            output.push_back(pair<string,string>("1DSumBackground",options));
            output.push_back(pair<string,string>("1DSumData",options));
        }

        static void Produce(vector<Variable>* theVariables,
                            vector<ProcessClass>* theProcessClasses,
                            vector<Region>* theRegions,
                            vector<Channel>* theChannels,
                            HistoScrewdriver* theHistoScrewdriver,
                            OptionsScrewdriver theGlobalOptions,
                            string histoOptions)      
        {
            // Browse the (var x reg x chan) space
            for (unsigned int v = 0 ; v < theVariables->size() ; v++)
            for (unsigned int r = 0 ; r < theRegions->size()   ; r++)
            for (unsigned int c = 0 ; c < theChannels->size()  ; c++)
            {

                vector<Histo1D*> theDatas;

                Variable* theVar     = &((*theVariables)[v]);
                Region*   theRegion  = &((*theRegions)[r]);
                Channel*  theChannel = &((*theChannels)[c]);

                Histo1D* theSumData = theHistoScrewdriver->get1DHistoForPlotPointer("1DSumData",
                                                                                    theVar->getTag(),
                                                                                    theRegion->getTag(),
                                                                                    theChannel->getTag(),
                                                                                    "");

                Histo1D* theSumBackground = theHistoScrewdriver->get1DHistoForPlotPointer("1DSumBackground",
                                                                                          theVar->getTag(),
                                                                                          theRegion->getTag(),
                                                                                          theChannel->getTag(),
                                                                                          "");

                theDatas.push_back(theSumBackground);

                theHistoScrewdriver->Add1DHistoForPlots(
                        Histo1DDataMCRatio(theVar,theRegion,theChannel,theSumData,theSumBackground)
                        );
            }
        }

        private:

    };

}

#endif
