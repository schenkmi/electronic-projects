classdef AudioAttenuatorAppV2 < handle
    % AudioAttenuatorAppV2
    % JOS-style logarithmic stepped attenuator calculator.
    %
    % The implementation follows the logarithmic ladder described by
    % Jos van Eijndhoven: binary stages have attenuation values
    % A, 2A, 4A, ... and each stage is designed to be independent by
    % maintaining either constant input resistance or constant output
    % resistance.  The E-series values are then applied and the complete
    % binary ladder is recalculated to show the resulting non-uniformity.
    %
    % Start with:
    %   app = AudioAttenuatorAppV2;
    %
    % Default example:
    %   10 kOhm, 1 dB, E96, 6 stages, constant output resistance.

    properties
        UIFigure
        InputPanel
        ResultsPanel
        GraphPanel

        REdit
        StepEdit
        SeriesDropDown
        TypeDropDown
        StagesDropDown
        PermDropDown
        CalculateButton
        ExportButton

        ResultTable
        InfoLabel
        AttAxes
        ErrorAxes

        Data
    end

    methods
        function app = AudioAttenuatorAppV2()
            app.buildUI();
            app.calculate();
        end

        function delete(app)
            if ~isempty(app.UIFigure) && isvalid(app.UIFigure)
                delete(app.UIFigure);
            end
        end
    end

    methods (Access = private)

        function buildUI(app)
            app.UIFigure = uifigure( ...
                'Name','JOS-Style Logarithmic Audio Attenuator Calculator V2', ...
                'Position',[60 60 1400 820]);

            outer = uigridlayout(app.UIFigure,[1 3]);
            outer.ColumnWidth = {300,610,'1x'};
            outer.RowHeight = {'1x'};
            outer.Padding = [10 10 10 10];

            % -------------------------------------------------------------
            % Input panel
            % -------------------------------------------------------------
            app.InputPanel = uipanel(outer,'Title','Design input');
            app.InputPanel.Layout.Column = 1;

            g = uigridlayout(app.InputPanel,[8 2]);
            g.RowHeight = {30,30,30,30,30,30,35,'1x'};
            g.ColumnWidth = {140,'1x'};
            g.Padding = [10 10 10 10];

            uilabel(g,'Text','Stage resistance (Ω):');
            app.REdit = uieditfield(g,'numeric','Value',10000, ...
                'Limits',[1 Inf]);
            app.REdit.Layout.Row = 1; app.REdit.Layout.Column = 2;

            uilabel(g,'Text','Stage attenuation (dB):');
            app.StepEdit = uieditfield(g,'numeric','Value',1.0, ...
                'Limits',[0.001 100]);
            app.StepEdit.Layout.Row = 2; app.StepEdit.Layout.Column = 2;

            uilabel(g,'Text','Resistor series:');
            app.SeriesDropDown = uidropdown(g, ...
                'Items',{'E6','E12','E24','E48','E96'}, ...
                'Value','E96');
            app.SeriesDropDown.Layout.Row = 3; app.SeriesDropDown.Layout.Column = 2;

            uilabel(g,'Text','Attenuator type:');
            app.TypeDropDown = uidropdown(g, ...
                'Items',{'Constant input resistance','Constant output resistance'}, ...
                'Value','Constant output resistance');
            app.TypeDropDown.Layout.Row = 4; app.TypeDropDown.Layout.Column = 2;

            uilabel(g,'Text','Number of stages:');
            app.StagesDropDown = uidropdown(g, ...
                'Items',arrayfun(@num2str,2:8,'UniformOutput',false), ...
                'Value','6');
            app.StagesDropDown.Layout.Row = 5; app.StagesDropDown.Layout.Column = 2;

            uilabel(g,'Text','Stage permutation:');
            app.PermDropDown = uidropdown(g, ...
                'Items',{'MSB → LSB (default)','LSB → MSB'}, ...
                'Value','MSB → LSB (default)');
            app.PermDropDown.Layout.Row = 6; app.PermDropDown.Layout.Column = 2;

            app.CalculateButton = uibutton(g,'push','Text','Calculate', ...
                'ButtonPushedFcn',@(src,event)app.calculate());
            app.CalculateButton.Layout.Row = 7; app.CalculateButton.Layout.Column = 1;

            app.ExportButton = uibutton(g,'push','Text','Export CSV', ...
                'ButtonPushedFcn',@(src,event)app.exportCSV());
            app.ExportButton.Layout.Row = 7; app.ExportButton.Layout.Column = 2;

            note = uilabel(g,'Text',sprintf([ ...
                'JOS-style binary logarithmic ladder.\n\n' ...
                'Stage attenuation is A, 2A, 4A, ... .\n' ...
                'The resistor values are calculated from the selected ' ...
                'constant-resistance condition, then rounded to the selected ' ...
                'E-series.\n\n' ...
                'The error is recalculated from the rounded resistors, ' ...
                'not from independent resistor rounding alone.']));
            note.Layout.Row = 8; note.Layout.Column = [1 2];
            note.VerticalAlignment = 'top';
            note.WordWrap = 'on';

            % -------------------------------------------------------------
            % Result panel
            % -------------------------------------------------------------
            app.ResultsPanel = uipanel(outer,'Title','Design result');
            app.ResultsPanel.Layout.Column = 2;

            rg = uigridlayout(app.ResultsPanel,[2 1]);
            rg.RowHeight = {'1x',150};
            rg.Padding = [5 5 5 5];

            app.ResultTable = uitable(rg);
            app.ResultTable.RowName = [];
            app.ResultTable.ColumnEditable = false;
            app.ResultTable.ColumnName = { ...
                'Stage','Nominal dB','Ideal Rseries','E-series Rseries', ...
                'Ideal Rshunt','E-series Rshunt','Actual dB','Stage error'};

            app.InfoLabel = uilabel(rg,'Text','');
            app.InfoLabel.VerticalAlignment = 'top';
            app.InfoLabel.WordWrap = 'on';

            % -------------------------------------------------------------
            % Graph panel
            % -------------------------------------------------------------
            app.GraphPanel = uipanel(outer,'Title','Performance');
            app.GraphPanel.Layout.Column = 3;

            pg = uigridlayout(app.GraphPanel,[2 1]);
            pg.RowHeight = {'1x','1x'};
            pg.Padding = [10 10 10 10];

            app.AttAxes = uiaxes(pg);
            title(app.AttAxes,'Attenuation vs. binary position');
            xlabel(app.AttAxes,'Position');
            ylabel(app.AttAxes,'Attenuation (dB)');
            grid(app.AttAxes,'on');

            app.ErrorAxes = uiaxes(pg);
            title(app.ErrorAxes,'Step-size / linearity error');
            xlabel(app.ErrorAxes,'Position');
            ylabel(app.ErrorAxes,'Error from design step (dB)');
            grid(app.ErrorAxes,'on');

            app.REdit.ValueChangedFcn = @(src,event)app.calculate();
            app.StepEdit.ValueChangedFcn = @(src,event)app.calculate();
            app.SeriesDropDown.ValueChangedFcn = @(src,event)app.calculate();
            app.TypeDropDown.ValueChangedFcn = @(src,event)app.calculate();
            app.StagesDropDown.ValueChangedFcn = @(src,event)app.calculate();
            app.PermDropDown.ValueChangedFcn = @(src,event)app.calculate();
        end

        function calculate(app)
            try
                R = app.REdit.Value;
                A = app.StepEdit.Value;
                N = str2double(app.StagesDropDown.Value);
                seriesName = app.SeriesDropDown.Value;
                topology = app.TypeDropDown.Value;
                perm = app.PermDropDown.Value;

                % JOS binary stage sequence: A, 2A, 4A, ... .
                % Internally use LSB->MSB so bit k has weight 2^(k-1).
                nominalDB = A .* 2.^(0:N-1);

                if contains(perm,'MSB')
                    displayDB = fliplr(nominalDB);
                else
                    displayDB = nominalDB;
                end

                k = 10.^(-nominalDB/20);
                idealRs = zeros(1,N);
                idealRp = zeros(1,N);

                switch topology
                    case 'Constant input resistance'
                        % Rparallel = Rb || Rload
                        % Rseries + Rparallel = Rload
                        % Rparallel/(Rseries+Rparallel) = k
                        %
                        % Rseries = R(1-k)
                        % Rshunt  = R*k/(1-k)
                        idealRs = R .* (1-k);
                        idealRp = R .* k ./ (1-k);

                    case 'Constant output resistance'
                        % Let RserTotal = Ra + Rsource.
                        % RserTotal || Rb = Rsource
                        % Rb/(RserTotal+Rb) = k
                        %
                        % RserTotal = R/k
                        % Rb = R/(1-k)
                        % Ra = R(1/k - 1)
                        idealRs = R .* (1./k - 1);
                        idealRp = R ./ (1-k);
                end

                base = app.eSeriesBase(seriesName);
                Rs = app.nearestE(idealRs,base);
                Rp = app.nearestE(idealRp,base);

                % Recalculate each stage using the actual rounded values.
                actualK = zeros(1,N);
                actualDB = zeros(1,N);

                for n = 1:N
                    if strcmp(topology,'Constant input resistance')
                        % The stage is terminated in R.  This gives the
                        % actual transfer of the stage.
                        p = app.parallel(Rp(n),R);
                        actualK(n) = p/(Rs(n)+p);
                    else
                        % The constant-output stage is evaluated with its
                        % designed source-side resistance R.  The first
                        % resistor is Ra; the total series branch seen by
                        % the stage is Ra + R.
                        % The actual stage ratio follows directly from
                        % the resistor network.
                        totalSeries = Rs(n) + R;
                        actualK(n) = Rp(n)/(totalSeries + Rp(n));
                    end
                    actualDB(n) = -20*log10(actualK(n));
                end

                % The actual complete ladder is the product of stage
                % transfer ratios.  This is the key JOS property: stages
                % are independently composable.
                positions = 0:(2^N-1);
                actualPosDB = zeros(size(positions));

                for p = 1:numel(positions)
                    bits = bitget(positions(p),1:N);
                    actualPosDB(p) = sum(bits .* actualDB);
                end

                idealPosDB = positions .* A;

                % Consecutive user-visible volume steps.  The intended
                % increment is A dB.  This captures the non-uniformity
                % discussed by JOS.
                stepActual = diff(actualPosDB);
                stepError = stepActual - A;

                % Also calculate error of every binary code against the
                % ideal attenuation.
                positionError = actualPosDB - idealPosDB;

                % For each stage, calculate the maximum contribution to
                % non-uniformity when that bit participates in a carry.
                % This is useful alongside the global error graph.
                maxDeviation = max(abs(stepError));

                % Impedance estimates from the actual ladder.
                Zin = zeros(size(positions));
                Zout = zeros(size(positions));
                for p = 1:numel(positions)
                    bits = bitget(positions(p),1:N);
                    [Zin(p),Zout(p)] = app.ladderImpedance( ...
                        Rs,Rp,R,bits,topology);
                end

                % Display table in the selected permutation.
                [~,order] = sort(displayDB,'descend');
                % order maps nominal descending sequence to internal stage
                % indices. For LSB->MSB, display is already ascending; the
                % table is explicitly shown MSB first to match JOS-style
                % diagrams.
                if contains(perm,'MSB')
                    order = N:-1:1;
                else
                    order = 1:N;
                end

                stageCol = (1:N)';
                T = table( ...
                    stageCol, ...
                    nominalDB(order)', ...
                    idealRs(order)',Rs(order)', ...
                    idealRp(order)',Rp(order)', ...
                    actualDB(order)', ...
                    (actualDB(order)-nominalDB(order))', ...
                    'VariableNames',{ ...
                    'Stage','Nominal_dB','Ideal_Rseries','Eseries_Rseries', ...
                    'Ideal_Rshunt','Eseries_Rshunt','Actual_dB','StageError_dB'});

                app.ResultTable.Data = T;

                info = sprintf([ ...
                    'Attenuator: %s\n' ...
                    'Stage resistance: %s\n' ...
                    'Stages: %d   |   Positions: %d   |   Range: 0 to %.6g dB\n' ...
                    'Average design step: %.6g dB\n' ...
                    'Maximum position error: %.6g dB\n' ...
                    'Maximum step-size deviation: %.6g dB\n' ...
                    'Input resistance range: %.6g … %.6g Ω\n' ...
                    'Output resistance range: %.6g … %.6g Ω'], ...
                    topology,app.formatValue(R),N,2^N,max(idealPosDB),A, ...
                    max(abs(positionError)),maxDeviation, ...
                    min(Zin),max(Zin),min(Zout),max(Zout));

                app.InfoLabel.Text = info;

                % Plots
                cla(app.AttAxes);
                plot(app.AttAxes,positions,idealPosDB,'--','LineWidth',1.2);
                hold(app.AttAxes,'on');
                plot(app.AttAxes,positions,actualPosDB,'o-','LineWidth',1.0);
                hold(app.AttAxes,'off');
                legend(app.AttAxes,{'Ideal','E-series'},'Location','northwest');
                grid(app.AttAxes,'on');

                cla(app.ErrorAxes);
                plot(app.ErrorAxes,positions(2:end),stepError,'o-','LineWidth',1.0);
                yline(app.ErrorAxes,0,'--');
                grid(app.ErrorAxes,'on');

                app.Data = struct( ...
                    'StageResistance',R, ...
                    'StageStep_dB',A, ...
                    'N',N, ...
                    'Series',seriesName, ...
                    'Topology',topology, ...
                    'Permutation',perm, ...
                    'NominalStage_dB',nominalDB, ...
                    'IdealRseries',idealRs, ...
                    'EseriesRseries',Rs, ...
                    'IdealRshunt',idealRp, ...
                    'EseriesRshunt',Rp, ...
                    'ActualStage_dB',actualDB, ...
                    'StageError_dB',actualDB-nominalDB, ...
                    'Position',positions, ...
                    'IdealPosition_dB',idealPosDB, ...
                    'ActualPosition_dB',actualPosDB, ...
                    'PositionError_dB',positionError, ...
                    'StepActual_dB',stepActual, ...
                    'StepError_dB',stepError, ...
                    'InputResistance',Zin, ...
                    'OutputResistance',Zout);

            catch ME
                uialert(app.UIFigure,ME.message,'Calculation error');
            end
        end

        function [zin,zout] = ladderImpedance(app,Rs,Rp,R,bits,topology)
            %#ok<INUSD>
            % Numerical DC resistance evaluation of the cascade.
            %
            % This is a practical impedance estimate for the JOS-style
            % independent-stage ladder. The exact stage transfer is
            % maintained by the resistor equations above.

            N = numel(Rs);

            % Input impedance with a terminating R.
            z = R;
            for n = N:-1:1
                if bits(n)
                    if strcmp(topology,'Constant input resistance')
                        z = Rs(n) + app.parallel(Rp(n),z);
                    else
                        z = Rs(n) + app.parallel(Rp(n),z);
                    end
                else
                    z = app.parallel(Rp(n),Rs(n)+z);
                end
            end
            zin = z;

            % Output impedance with source set to zero.
            z = 0;
            for n = 1:N
                if bits(n)
                    z = app.parallel(Rp(n),Rs(n)+z);
                else
                    z = app.parallel(Rp(n),Rs(n)+z);
                end
            end

            % A zero in the recursive model can understate the load-side
            % resistance; include the intended stage reference.
            zout = app.parallel(z,R);
        end

        function exportCSV(app)
            if isempty(app.Data)
                return
            end

            [file,path] = uiputfile('JOS_attenuator_results.csv', ...
                'Export JOS-style attenuator results');
            if isequal(file,0)
                return
            end

            D = app.Data;

            T = table( ...
                (1:D.N)', ...
                D.NominalStage_dB', ...
                D.IdealRseries',D.EseriesRseries', ...
                D.IdealRshunt',D.EseriesRshunt', ...
                D.ActualStage_dB',D.StageError_dB', ...
                'VariableNames',{ ...
                'Stage','Nominal_dB','Ideal_Rseries','Eseries_Rseries', ...
                'Ideal_Rshunt','Eseries_Rshunt','Actual_dB','StageError_dB'});

            writetable(T,fullfile(path,file));

            T2 = table( ...
                D.Position',D.IdealPosition_dB',D.ActualPosition_dB', ...
                D.PositionError_dB',D.StepActual_dB',D.StepError_dB', ...
                'VariableNames',{ ...
                'Position','Ideal_dB','Actual_dB','PositionError_dB', ...
                'StepActual_dB','StepError_dB'});

            [~,name,ext] = fileparts(file);
            file2 = fullfile(path,[name '_positions' ext]);
            writetable(T2,file2);

            uialert(app.UIFigure, ...
                sprintf('Created:\n%s\n%s',fullfile(path,file),file2), ...
                'Export complete');
        end
    end

    methods (Static, Access = private)

        function base = eSeriesBase(name)
            switch upper(name)
                case 'E6'
                    base = [10 15 22 33 47 68];

                case 'E12'
                    base = [10 12 15 18 22 27 33 39 47 56 68 82];

                case 'E24'
                    base = [10 11 12 13 15 16 18 20 22 24 27 30 ...
                            33 36 39 43 47 51 56 62 68 75 82 91];

                case 'E48'
                    base = [10.0 10.5 11.0 11.5 12.1 12.7 13.3 14.0 ...
                            14.7 15.4 16.2 16.9 17.8 18.2 19.1 20.0 ...
                            21.0 22.1 23.2 24.3 25.5 26.7 28.0 29.4 ...
                            30.1 31.6 33.2 34.8 36.5 38.3 40.2 42.2 ...
                            43.2 45.3 47.5 49.9 52.3 54.9 57.6 60.4 ...
                            63.4 66.5 69.8 73.2 76.8 80.6 84.5 88.7 93.1 97.6];

                case 'E96'
                    base = [ ...
                        10.0 10.2 10.5 10.7 11.0 11.3 11.5 11.8 ...
                        12.1 12.4 12.7 13.0 13.3 13.7 14.0 14.3 ...
                        14.7 15.0 15.4 15.8 16.2 16.5 16.9 17.4 ...
                        17.8 18.2 18.7 19.1 19.6 20.0 20.5 21.0 ...
                        21.5 22.1 22.6 23.2 23.7 24.3 24.9 25.5 ...
                        26.1 26.7 27.4 28.0 28.7 29.4 30.1 30.9 ...
                        31.6 32.4 33.2 34.0 34.8 35.7 36.5 37.4 ...
                        38.3 39.2 40.2 41.2 42.2 43.2 44.2 45.3 ...
                        46.4 47.5 48.7 49.9 51.1 52.3 53.6 54.9 ...
                        56.2 57.6 59.0 60.4 61.9 63.4 64.9 66.5 ...
                        68.1 69.8 71.5 73.2 75.0 76.8 78.7 80.6 ...
                        82.5 84.5 86.6 88.7 90.9 93.1 95.3 97.6];

                otherwise
                    error('Unknown E-series: %s',name);
            end
        end

        function r = nearestE(x,base)
            r = zeros(size(x));

            for n = 1:numel(x)
                if x(n) <= 0
                    r(n) = NaN;
                    continue
                end

                decade = 10^floor(log10(x(n)));
                candidates = base .* decade;

                % Include neighboring decades so values near a boundary
                % are always handled correctly.
                candidates = [ ...
                    base.*(decade/10), ...
                    candidates, ...
                    base.*(decade*10)];

                [~,idx] = min(abs(log10(candidates./x(n))));
                r(n) = candidates(idx);
            end
        end

        function z = parallel(a,b)
            if a == 0 || b == 0
                z = 0;
            elseif isinf(a)
                z = b;
            elseif isinf(b)
                z = a;
            else
                z = 1/(1/a+1/b);
            end
        end

        function s = formatValue(x)
            if x >= 1e6
                s = sprintf('%.6g MΩ',x/1e6);
            elseif x >= 1e3
                s = sprintf('%.6g kΩ',x/1e3);
            else
                s = sprintf('%.6g Ω',x);
            end
        end
    end
end
