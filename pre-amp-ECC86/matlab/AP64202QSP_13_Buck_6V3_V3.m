% =============================================================
%  --- INPUT PARAMETERS ---                                      
%  =============================================================
Vin = 35.0;         % Input Voltage in V
Vout = 6.3;         % Output Voltage in V
Iout = 0.66;        % Output Current in A
fsw = 1.0 * 10^6;   % Switching Frequency: 1 MHz
L = 15.0 * 10^-6;   % Inductance Bourns SRU8043-150Y: 15 uH
DCR = 0.046;        % Maximum DC Resistance of the inductor in Ohms

% IC Specifications: Diodes Inc. AP64202Q
Vfb = 0.8;          % Feedback Reference Voltage in V
RdsOnHS = 0.150;    % Typ. High-Side FET On-Resistance in Ohms
RdsOnLS = 0.080;    % Typ. Low-Side FET On-Resistance in Ohms
tTransition = 5.0 * 10^-9; % Switching node Rise/Fall transition time: 5 ns
QgHS = 3.0 * 10^-9;        % Gate Charge of High-Side FET: 3 nC
Vgate = 5.0;               % Internal Gate Driver Voltage in V

% EMI Filter Parameters
Lemc = 4.7 * 10^-6;   % Proposed EMI Filter Inductance: 4.7 uH
Cemc = 10.0 * 10^-6;  % Proposed EMI Filter Capacitance: 10 uF
DeltaILastsprung = 0.5; % Assumed Load Step for Cout calculation: 0.5 A

% Soft-Start Target Parameters
tss_target = 4.0;   % Desired Soft-Start Time in milliseconds (ms)

%% =============================================================
%  --- CALCULATIONS & OUTPUT ---                                 
%  =============================================================
fprintf('=============================================================\n');
fprintf('   COMPLETE BUCK CONVERTER ANALYSIS (AP64202Q + SRU8043)   \n');
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
fprintf('Inductor Ripple Current (ΔIL): %.3f A\n', DeltaIL);
fprintf('Peak Inductor Current (Ipeak): %.3f A (Inductor Limit: 2.0A)\n', Ipeak);
fprintf('RMS Inductor Current (Irms):   %.3f A (Inductor Limit: 2.7A)\n', IrmsL);

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

% 4. Peripheral Components & Feedback
fswkHz = fsw / 1000.0;
Rt = 100000.0 / fswkHz; 
R2 = 10000.0;
R1 = R2 * ((Vout / Vfb) - 1.0);

fprintf('\n[EXTERNAL COMPONENTS & FEEDBACK]\n');
fprintf('Frequency Resistor (RT):      %.1f kΩ\n', Rt);
fprintf('Feedback Resistor R1 (Top):   %.2f kΩ\n', R1 / 1000.0);
fprintf('Feedback Resistor R2 (Bottom): %.1f kΩ\n', R2 / 1000.0);

% 5. Soft-Start Calculation
Css = 3.5 * tss_target; % Formula from AP64202Q Datasheet (Result in nF)
fprintf('\n[SOFT-START ANALYSIS (SS PIN)]\n');
fprintf('Target Soft-Start Time (tss): %.1f ms\n', tss_target);
fprintf('Calculated SS Cap (Css):       %.1f nF (Standard Value: 15 nF)\n', Css);

% 6. Corrected Output Capacitor Analysis
DeltaVoutTarget = 0.01 * Vout;
CoutRippel = DeltaIL / (8.0 * fsw * DeltaVoutTarget);
MaxESR = DeltaVoutTarget / DeltaIL;
CoutStability = DeltaILastsprung / (2.0 * pi * (fsw * 0.1) * DeltaVoutTarget);
CoutRealRecommended = max(CoutRippel, CoutStability) * 2.0;

fprintf('\n[CORRECTED CAPACITOR ANALYSIS (COUT)]\n');
fprintf('Ideal Ripple C (Theory Only): %.3f µF\n', CoutRippel * 1000000);
fprintf('Maximum Allowed Capacitor ESR: %.1f mΩ\n', MaxESR * 1000);
fprintf('C for Transient Stability:    %.2f µF\n', CoutStability * 1000000);
fprintf('Recommended Real C (X7R):     %.1f µF (Standard Value: 22 µF or 47 µF)\n', max(22.0, CoutRealRecommended * 1000000));

% 7. EMI Filter Design
f0 = 1.0 / (2.0 * pi * sqrt(Lemc * Cemc));
AttenuatondB = 40.0 * log10(fsw / f0);
Z0 = sqrt(Lemc / Cemc);
CdMin = 4.0 * Cemc;
RdOpt = 1.0 * Z0;

fprintf('\n[EMI FILTER DESIGN (PI-FILTER)]\n');
fprintf('Filter Resonance Freq (f0):   %.1f kHz\n', f0 / 1000.0);
fprintf('Theoretical Attenuation @1MHz: %.1f dB\n', AttenuatondB);
fprintf('Filter Characteristic Imp (Z0): %.2f Ω\n', Z0);
fprintf('Damping Electrolytic Cap (Cd): %.1f µF\n', CdMin * 1000000);
fprintf('Damping Resistor (Rd):        %.2f Ω\n', RdOpt);
fprintf('=============================================================\n');
