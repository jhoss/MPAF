import ROOT as rt
from array import *
from sms import *
from smsPlotSigABS import *

# class producing the 2D plot with xsec colors
class smsPlotSig(smsPlotSigABS):

    def __init__(self, modelname, histo, energy, lumi, preliminary, label):
        self.standardSIGDef(modelname, histo, energy, lumi, preliminary)
        self.LABEL = label
        # canvas for the plot
        self.c = rt.TCanvas("cCONT_%s" %label,"cCONT_%s" %label,600,600)
        self.histo  = histo ['histogram']
        # canvas style
        self.setStyle()
        self.setStyleCOLZ()

    # define the plot canvas
    def setStyleCOLZ(self):        
        # set z axis
        self.histo.GetZaxis().SetLabelFont(42)
        self.histo.GetZaxis().SetTitleFont(42)
        self.histo.GetZaxis().SetLabelSize(0.035)
        self.histo.GetZaxis().SetTitleSize(0.035)
        self.histo.SetMinimum(-2.0)
        self.histo.SetMaximum(2.0)

        # define the palette for z axis
        NRGBs = 5
        NCont = 255
#        stops = array("d",[0.00, 0.34, 0.61, 0.84, 1.00])
#        red= array("d",[0.50, 0.50, 1.00, 1.00, 1.00])
#        green = array("d",[ 0.50, 1.00, 1.00, 0.60, 0.50])
#        blue = array("d",[1.00, 1.00, 0.50, 0.40, 0.50])
#        rt.TColor.CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont)
        rt.gStyle.SetNumberContours(NCont)
        
        self.c.cd()
        self.histo.Draw("colz")
        
        rt.gPad.Update()
        palette = self.histo.GetListOfFunctions().FindObject("palette")
        palette.SetX1NDC(1.-0.18)
        palette.SetY1NDC(0.14)
        palette.SetX2NDC(1.-0.13)
        palette.SetY2NDC(1.-0.08)
        palette.SetLabelFont(42)
        palette.SetLabelSize(0.035)

    def DrawPaletteLabel(self):
        textCOLZ = rt.TLatex(0.98,0.62,"Significance (#sigma)")
        textCOLZ.SetNDC()
        #textCOLZ.SetTextAlign(13)
        textCOLZ.SetTextFont(42)
        textCOLZ.SetTextSize(0.045)
        textCOLZ.SetTextAngle(90)
        textCOLZ.Draw()
        self.c.textCOLZ = textCOLZ
            
    def Draw(self):
        self.emptyHisto.GetXaxis().SetRangeUser(self.model.Xmin, self.model.Xmax)
        self.emptyHisto.GetYaxis().SetRangeUser(self.model.Ymin, self.model.Ymax)
        self.emptyHisto.GetZaxis().SetRangeUser(-2.5, +2.5)
        self.emptyHisto.SetMinimum(-2.0)
        self.emptyHisto.SetMaximum(2.0)
        
        for x in range(self.emptyHisto.GetNbinsX()):
            for y in range(self.emptyHisto.GetNbinsY()):
                xval = self.emptyHisto.GetXaxis().GetBinCenter(x+1)
                yval = self.emptyHisto.GetYaxis().GetBinCenter(y+1)
                histoBin=self.histo.FindBin(xval,yval)
                emptyHistoBin=self.emptyHisto.FindBin(xval,yval)
                z=self.histo.GetBinContent(histoBin)
                self.emptyHisto.SetBinContent(emptyHistoBin,z)

        #self.emptyHisto.GetZaxis().SetRangeUser(self.model.Zmin, self.model.Zmax)
        self.emptyHisto.Draw("COLZ")
 

#        self.emptyHisto.Draw()
#        self.histo.Draw("COLZSAME")
        #if self.model.mTopDiagOn:
        #    self.DrawMtopDiagonal(1)
#        self.DrawLines()
        if self.model.diagOn:
            self.DrawDiagonal()
        #if self.model.mTopDiagOn:          Jan
#            self.DrawMtopDiagonal(1)
        #    self.DrawSmallMtopDiagonal(1)  Jan
            #gdiagonal = self.c.mtopgdiagonal.Clone("MtopDiagonalClone")
            #gdiagonal.SetFillColorAlpha(rt.kWhite, 0.6)
            #ldiagonal = self.c.mtopldiagonal
            #tdiagonal = self.c.mtoptdiagonal
            #gdiagonal.Draw("FSAME")
            #ldiagonal.Draw("LSAME")
            #tdiagonal.Draw("SAME")
            #self.c.mtopgdiagonal2 = gdiagonal
        #if self.model.t2ccDiagOn:  Jan
        #    self.DrawT2ccDiagonal()    Jan
        self.DrawText()
#        self.DrawLegend()
        self.DrawPaletteLabel()
        
       
