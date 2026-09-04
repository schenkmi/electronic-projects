%% =============================================================
%  --- INPUT PARAMETERS for AP63205WU + SRU5018-4R7Y ---                                      
%  =============================================================
Vin = 24.0;         % Recommended operating input voltage for 4.7uH (Max: 32V)
Vout = 5.0;         % Fixed output voltage of the AP63205WU
Iout = 0.18;        % Output Current in A
fsw = 1.1 * 10^6;   % Fixed Internal Switching Frequency: 1.1 MHz
L = 4.7 * 10^-6;    % Bourns SRU5018-4R7Y Inductance
DCR = 0.036;        % Max DCR of SRU5018-4R7Y (36 mOhm)

% IC Specifications: Diodes Inc. AP63205WU
RdsOnHS = 0.125;    % Typ. High-Side FET On-Resistance in Ohms
RdsOnLS = 0.068;    % Typ. Low-Side FET On-Resistance in Ohms
tTransition = 5.0 * 10^-9; 
QgHS = 2.5 * 10^-9;        
Vgate = 5.0;               

% EMI Filter Parameters
Lemc = 4.7 * 10^-6;   
Cemc = 10.0 * 10^-6;  
DeltaILastsprung = 0.5; 

% Output Ripple Parameters
CoutTest = 22.0 * 10^-6; 
CoutEsr = 0.005;         

%% =============================================================
%  --- CALCULATIONS & OUTPUT ---                                 
%  =============================================================
fprintf('=============================================================\n');
fprintf('     AP63205WU CONVERTER ANALYSIS WITH SRU5018-4R7Y          \n');
fprintf('=============================================================\n\n');

% 1. Static Values
duty = Vout / Vin;
Pout = Vout * Iout;
fprintf('[STATIC VALUES]\n');
fprintf('Duty Cycle:                   %.2f %%\n', duty * 100);
fprintf('Output Power (Pout):          %.2f W\n', Pout);

% 2. Inductor Current Analysis
DeltaIL = (Vout * (Vin - Vout)) / (L * fsw * Vin);
Ipeak = Iout + (DeltaIL / 2.0);
IrmsL = sqrt(Iout^2 + (DeltaIL^2 / 12.0));

fprintf('\n[INDUCTOR CURRENT ANALYSIS]\n');
fprintf('Inductor Ripple Current (ΔIL): %.3f A (Ripple Ratio: %.1f %%)\n', DeltaIL, (DeltaIL/Iout)*100);
fprintf('Peak Inductor Current (Ipeak): %.3f A (Inductor Limit Isat: 2.0A)\n', Ipeak);
fprintf('RMS Inductor Current (Irms):   %.3f A (Inductor Limit Irms: 1.55A)\n', IrmsL);

% 3. Power Losses Analysis
PdcRLoss = (IrmsL^2) * DCR; 
PcondHS = duty * (Iout^2) * RdsOnHS;
PcondLS = (1.0 - duty) * (Iout^2) * RdsOnLS;
Pswitching = 0.5 * Vin * Iout * (2.0 * tTransition) * fsw;
PgateCharge = QgHS * Vgate * fsw;
PlossesTotal = PdcRLoss + PcondHS + PcondLS + Pswitching + PgateCharge;
Efficiency = (Pout / (Pout + PlossesTotal)) * 100;

fprintf('\n[PRECISE LOSS & EFFICIENCY ANALYSIS]\n');
fprintf('Inductor DCR Loss:            %.1f mW\n', PdcRLoss * 1000);
fprintf('IC Conduction Loss (HS FET):  %.1f mW\n', PcondHS * 1000);
fprintf('IC Conduction Loss (LS FET):  %.1f mW\n', PcondLS * 1000);
fprintf('IC Switching Loss:            %.1f mW\n', Pswitching * 1000);
fprintf('IC Gate Drive Loss:           %.1f mW\n', PgateCharge * 1000);
fprintf('Total Power Loss:             %.1f mW\n', PlossesTotal * 1000);
fprintf('Estimated Total Efficiency:   %.2f %%\n', Efficiency);

% 4. Corrected Output Capacitor Analysis
DeltaVoutTarget = 0.01 * Vout;
CoutRippel = DeltaIL / (8.0 * fsw * DeltaVoutTarget);
MaxESR = DeltaVoutTarget / DeltaIL;
CoutStability = DeltaILastsprung / (2.0 * pi * (fsw * 0.1) * DeltaVoutTarget);
CoutRealRecommended = max(CoutRippel, CoutStability) * 2.0;

fprintf('\n[CORRECTED CAPACITOR ANALYSIS (COUT)]\n');
fprintf('Ideal Ripple C (Theory Only): %.3f µF\n', CoutRippel * 1000000);
fprintf('Maximum Allowed Capacitor ESR: %.1f mΩ\n', MaxESR * 1000);
fprintf('C for Transient Stability:    %.2f µF\n', CoutStability * 1000000);
fprintf('Recommended Real C (X7R):     %.1f µF (Standard Value: 22 µF)\n', max(22.0, CoutRealRecommended * 1000000));

% 5. Output Voltage Ripple Verification
CoutEffective = CoutTest * 0.65; 
DeltaV_C = DeltaIL / (8.0 * fsw * CoutEffective);
DeltaV_ESR = DeltaIL * CoutEsr;
DeltaV_Out_Total = DeltaV_C + DeltaV_ESR;

fprintf('\n[REAL OUTPUT VOLTAGE RIPPLE ANALYSIS]\n');
fprintf('Tested Output Capacitor:      %.1f µF\n', CoutTest * 1000000);
fprintf('Total Peak-to-Peak Ripple:    %.2f mV (%.2f %% of Vout)\n', DeltaV_Out_Total * 1000, (DeltaV_Out_Total / Vout) * 100);
fprintf('=============================================================\n');