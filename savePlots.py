#!/usr/bin/env python2

import ROOT
import sys
import os

def main():
    if len(sys.argv) != 3:
        print "Wrong number of arguments !"
        print "Syntax is: python savePlots.py inputFile.root outputDir"

    outputformat = "png"

    f = ROOT.TFile.Open(sys.argv[1])
    outdir = sys.argv[2]
    try:
        os.makedirs(outdir)
    except:
        pass

    style = ROOT.gStyle
    stat = style.GetOptStat()

    c = ROOT.TCanvas("can", "can", 600,600)
    # Loop over plots
    for k in f.GetListOfKeys():
        o = k.ReadObj()
        if "TH2" in k.GetClassName():
            style.SetOptStat(0)
            o.Draw("colz")
        elif "TH1" in k.GetClassName():
            style.SetOptStat(stat)
            o.Draw()
        c.SaveAs(outdir+"/"+o.GetName()+"."+outputformat)

    f.Close()

if __name__ == "__main__":
    main()
