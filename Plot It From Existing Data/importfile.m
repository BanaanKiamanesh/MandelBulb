function data = importfile(DIM, dataLines)
    %  Example:
    %  data = importfile(128, [2, Inf]);
    %       or
    %  data = importfile(128);


    %% Input handling
    if nargin < 2
        dataLines = [2, Inf];
    end

    filename = ['../Data/MandelData_' num2str(DIM) '.csv'];

    %% Set up the Import Options and import the data
    opts = delimitedTextImportOptions("NumVariables", 3);

    % Options
    opts.DataLines = dataLines;
    opts.Delimiter = ",";
    opts.VariableNames = ["x", "y", "z"];
    opts.VariableTypes = ["double", "double", "double"];
    opts.ExtraColumnsRule = "ignore";
    opts.EmptyLineRule = "read";

    % Import the data
    data = readtable(filename, opts);

    %% Convert to output type
    data = table2array(data);
end