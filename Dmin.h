//
//  Dmin.h
//  Dsuite
//
//  Created by Milan Malinsky on 02/04/2019.
//  Copyright © 2019 Milan Malinsky. All rights reserved.
//

#ifndef Dmin_h
#define Dmin_h
#include "Dsuite_utils.h"


void parseDminOptions(int argc, char** argv);
int DminMain(int argc, char** argv);

class TrioDinfo {
public:
    TrioDinfo() {
        ABBAtotal = 0;
        BABAtotal = 0;
        BBAAtotal = 0;
        treeArrangement = 0; BBAAarrangement = 0; DminArrangement = 0;
        regionDs.resize(3); usedVars.resize(3);
        usedVars[0] = 0; usedVars[1] = 0; usedVars[2] = 0;
        localD1num = 0; localD2num = 0; localD3num = 0;
        localD1denom = 0; localD2denom = 0; localD3denom = 0;
        F_d_denom1 = 0; F_d_denom1_reversed = 0; F_dM_denom1 = 0; F_dM_denom1_reversed = 0; F_G_denom1 = 0; F_G_denom1_reversed = 0;
        F_d_denom2 = 0; F_d_denom2_reversed = 0; F_dM_denom2 = 0; F_dM_denom2_reversed = 0; F_G_denom2 = 0; F_G_denom2_reversed = 0;
        F_d_denom3 = 0; F_d_denom3_reversed = 0; F_dM_denom3 = 0; F_dM_denom3_reversed = 0; F_G_denom3 = 0; F_G_denom3_reversed = 0;
    };
    
    // string P1; string P2; string P3;
    double ABBAtotal; double BABAtotal; double BBAAtotal;
    double D1; double D2; double D3; double D1_p; double D2_p; double D3_p;
    double F_d_denom1; double F_d_denom1_reversed; double F_dM_denom1; double F_dM_denom1_reversed; double F_G_denom1; double F_G_denom1_reversed;
    double F_d_denom2; double F_d_denom2_reversed; double F_dM_denom2; double F_dM_denom2_reversed; double F_G_denom2; double F_G_denom2_reversed;
    double F_d_denom3; double F_d_denom3_reversed; double F_dM_denom3; double F_dM_denom3_reversed; double F_G_denom3; double F_G_denom3_reversed;
    
    
    
    double localD1num; double localD2num; double localD3num;
    double localD1denom; double localD2denom; double localD3denom;
    std::vector<std::vector<double>> regionDs; // vector with three empty (double) vectors
    std::vector<int> usedVars;
    
    int treeArrangement;    // 1 - trios[i][0] and trios[i][1] are P1 and P2
                            // 2 - trios[i][0] and trios[i][2] are P1 and P2
                            // 3 - trios[i][1] and trios[i][2] are P1 and P2
    
    int BBAAarrangement;    // 1 - trios[i][0] and trios[i][1] are P1 and P2
                            // 2 - trios[i][0] and trios[i][2] are P1 and P2
                            // 3 - trios[i][1] and trios[i][2] are P1 and P2
    
    int DminArrangement;    // 1 - trios[i][0] and trios[i][1] are P1 and P2
                            // 2 - trios[i][0] and trios[i][2] are P1 and P2
                            // 3 - trios[i][1] and trios[i][2] are P1 and P2
    
    
    void assignTreeArrangement(std::vector<int>& treeLevels, int loc1, int loc2, int loc3) {
        int midLoc = std::max(std::min(loc1,loc2), std::min(std::max(loc1,loc2),loc3));
        if (midLoc == loc1) {
            if (loc2 < loc1) {
                int m1 = *std::min_element(treeLevels.begin()+loc2, treeLevels.begin()+loc1);
                int m2 = *std::min_element(treeLevels.begin()+loc1, treeLevels.begin()+loc3);
                if (m1 < m2) treeArrangement = 2; else treeArrangement = 1;
            } else {
                int m1 = *std::min_element(treeLevels.begin()+loc3, treeLevels.begin()+loc1);
                int m2 = *std::min_element(treeLevels.begin()+loc1, treeLevels.begin()+loc2);
                if (m1 < m2) treeArrangement = 1; else treeArrangement = 2;
            }
        } else if (midLoc == loc2) {
            if (loc1 < loc2) {
                int m1 = *std::min_element(treeLevels.begin()+loc1, treeLevels.begin()+loc2);
                int m2 = *std::min_element(treeLevels.begin()+loc2, treeLevels.begin()+loc3);
                if (m1 < m2) treeArrangement = 3; else treeArrangement = 1;
            } else {
                int m1 = *std::min_element(treeLevels.begin()+loc3, treeLevels.begin()+loc2);
                int m2 = *std::min_element(treeLevels.begin()+loc2, treeLevels.begin()+loc1);
                if (m1 < m2) treeArrangement = 1; else treeArrangement = 3;
            }
        } else if (midLoc == loc3) {
            if (loc1 < loc3) {
                int m1 = *std::min_element(treeLevels.begin()+loc1, treeLevels.begin()+loc3);
                int m2 = *std::min_element(treeLevels.begin()+loc3, treeLevels.begin()+loc2);
                if (m1 < m2) treeArrangement = 3; else treeArrangement = 2;
                
            } else {
                int m1 = *std::min_element(treeLevels.begin()+loc2, treeLevels.begin()+loc3);
                int m2 = *std::min_element(treeLevels.begin()+loc3, treeLevels.begin()+loc1);
                if (m1 < m2) treeArrangement = 2; else treeArrangement = 3;
            }
        }
    }
    
    std::vector<string> assignBBAAarrangement(std::vector<string>& trio, bool fStats) {
        std::vector<string> outVec; if (fStats) outVec.resize(11); else outVec.resize(5);
        // Find which topology is in agreement with the counts of the BBAA, BABA, and ABBA patterns
        if (BBAAtotal >= BABAtotal && BBAAtotal >= ABBAtotal) {
            BBAAarrangement = P3isTrios2; outVec[2] = trio[2];
            if (D1 >= 0) {outVec[0] = trio[0]; outVec[1] = trio[1]; }
            else { outVec[0] = trio[1]; outVec[1] = trio[0]; }
            outVec[3] = numToString(std::fabs(D1)); outVec[4] = numToString(D1_p);
        } else if (BABAtotal >= BBAAtotal && BABAtotal >= ABBAtotal) {
            BBAAarrangement = P3isTrios1; outVec[2] = trio[1];
            if (D2 >= 0) {outVec[0] = trio[0]; outVec[1] = trio[2]; }
            else { outVec[0] = trio[2]; outVec[1] = trio[0]; }
            outVec[3] = numToString(std::fabs(D2)); outVec[4] = numToString(D2_p);
        } else if (ABBAtotal >= BBAAtotal && ABBAtotal >= BABAtotal) {
            BBAAarrangement = P3isTrios0; outVec[2] = trio[0];
            if (D3 >= 0) {outVec[0] = trio[2]; outVec[1] = trio[1]; }
            else { outVec[0] = trio[1]; outVec[1] = trio[2]; }
            outVec[3] = numToString(std::fabs(D3)); outVec[4] = numToString(D3_p);
        }
        return outVec;
    }
    
    std::vector<string> assignDminArrangement(std::vector<string>& trio, bool fStats) {
        std::vector<string> outVec; if (fStats) outVec.resize(11); else outVec.resize(5);
        if (std::fabs(D1) <= std::fabs(D2) && std::fabs(D1) <= std::fabs(D3)) { // (P3 == S3)
            DminArrangement = P3isTrios2; outVec[2] = trio[2];
            if (D1 >= 0) { outVec[0] = trio[0]; outVec[1] = trio[1]; }
            else {outVec[0] = trio[1]; outVec[1] = trio[0];}
            outVec[3] = numToString(std::fabs(D1)); outVec[4] = numToString(D1_p);
        } else if (std::fabs(D2) <= std::fabs(D1) && std::fabs(D2) <= std::fabs(D3)) { // (P3 == S2)
            DminArrangement = P3isTrios1; outVec[2] = trio[1];
            if (D2 >= 0) {outVec[0] = trio[0]; outVec[1] = trio[2]; }
            else { outVec[0] = trio[2]; outVec[1] = trio[0]; }
            outVec[3] = numToString(std::fabs(D2)); outVec[4] = numToString(D2_p);
        } else if (std::fabs(D3) <= std::fabs(D1) && std::fabs(D3) <= std::fabs(D2)) { // (P3 == S1)
            DminArrangement = P3isTrios0; outVec[2] = trio[0];
            if (D3 >= 0) {outVec[0] = trio[2]; outVec[1] = trio[1]; }
            else { outVec[0] = trio[1]; outVec[1] = trio[2]; }
            outVec[3] = numToString(std::fabs(D3)); outVec[4] = numToString(D3_p);
        }
        return outVec;
    }
    
    
    
    void calculateFinalDs() throw(const char*) {
        double* Ds = calculateThreeDs(ABBAtotal, BABAtotal, BBAAtotal);
        D1 = Ds[0]; D2 = Ds[1]; D3 = Ds[2];
        
        // Get the standard error values:
        double D1stdErr = jackknive_std_err(regionDs[0]); double D2stdErr = jackknive_std_err(regionDs[1]);
        double D3stdErr = jackknive_std_err(regionDs[2]);
        // Get the Z-scores
        double D1_Z = std::fabs(D1)/D1stdErr; double D2_Z = std::fabs(D2)/D2stdErr;
        double D3_Z = std::fabs(D3)/D3stdErr;
        // And p-values
        D1_p = 1 - normalCDF(D1_Z); D2_p = 1 - normalCDF(D2_Z);
        D3_p = 1 - normalCDF(D3_Z);
    }
    
    void addRegionDs(int arrangement) {
        switch (arrangement) {
            case P3isTrios2: regionDs[0].push_back(localD1num/localD1denom); localD1num = 0; localD1denom = 0; usedVars[0] = 0; break;
            case P3isTrios1: regionDs[1].push_back(localD2num/localD2denom); localD2num = 0; localD2denom = 0; usedVars[1] = 0; break;
            case P3isTrios0: regionDs[2].push_back(localD3num/localD3denom); localD3num = 0; localD3denom = 0; usedVars[2] = 0; break;
        }
    }
    
};


#endif /* Dmin_h */
