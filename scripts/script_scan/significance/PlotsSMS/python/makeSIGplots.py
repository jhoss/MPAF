import sys
from inputFileSig import *
from smsPlotSig import *
from smsPlotXSEC import *
from smsPlotCONT import *
from smsPlotBrazil import *

if __name__ == '__main__':
    # read input arguments
    filename = sys.argv[1]
    modelname = sys.argv[1].split("/")[-1].split("_")[0]
    analysisLabel = sys.argv[1].split("/")[-1].split("_")[1] if len(sys.argv[1].split("/")[-1].split("_"))>1 else ""
    outputname = sys.argv[2]

    # read the config file
    fileIN = inputFileSig(filename)
    
    # classic temperature histogra
    sigPlot = smsPlotSig(modelname, fileIN.HISTOGRAM, fileIN.ENERGY, fileIN.LUMI, fileIN.PRELIMINARY, "")
    sigPlot.Draw()
    sigPlot.Save("%sSIG" %outputname)

    # only lines
    #contPlot = smsPlotCONT(modelname, fileIN.HISTOGRAM, fileIN.OBSERVED, fileIN.EXPECTED, fileIN.OBSERVED2, fileIN.EXPECTED2, fileIN.ENERGY, fileIN.LUMI, fileIN.PRELIMINARY, "")
    #contPlot.Draw()
    #contPlot.Save("%sCONT" %outputname)

    # brazilian flag (show only 1 sigma)
    #brazilPlot = smsPlotBrazil(modelname, fileIN.HISTOGRAM, fileIN.OBSERVED, fileIN.EXPECTED, fileIN.OBSERVED2, fileIN.EXPECTED2, fileIN.ENERGY, fileIN.LUMI, fileIN.PRELIMINARY, "")
    #brazilPlot.Draw()
    #brazilPlot.Save("%sBAND" %outputname)
