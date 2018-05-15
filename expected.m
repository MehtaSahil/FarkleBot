format long g
clear
clc

%% Six dice
scoring_probs_6 = [6 180 300 720 1800 2250 2280 2280 2280 2280 2280 2280 13272 13272] ./ 46656;
scoring_values_6 = [3000 2000 2500 1500 1000 1500 300 200 300 400 500 600 100 50];

EV_6 = sum(scoring_probs_6.*scoring_values_6);
exp_gain_6 = @(running_total) EV_6 - (1176/46656)*running_total;
running_total_limit_6 = fzero(exp_gain_6, 300);

%% Five dice
scoring_probs_5 = [6 150 250 250 250 250 250 250 2760 2760] ./ 7776;
scoring_values_5 = [2000 1000 300 200 300 400 500 600 100 50];

EV_5 = sum(scoring_probs_5.*scoring_values_5);
exp_gain_5 = @(running_total) EV_5 - (600/7776)*running_total;
running_total_limit_5 = fzero(exp_gain_5, 300);

%% Four dice
scoring_probs_4 = [6 20 20 20 20 20 20 483 483] ./ 1296;
scoring_values_4 = [1000 300 200 300 400 500 600 100 50];

EV_4 = sum(scoring_probs_4.*scoring_values_4);
exp_gain_4 = @(running_total) EV_4 - (204/1296)*running_total;
running_total_limit_4 = fzero(exp_gain_4, 300);

%% Three dice
scoring_probs_3 = [1 1 1 1 1 1 75 75] ./ 216;
scoring_values_3 = [300 200 300 400 500 600 100 50];

EV_3 = sum(scoring_probs_3.*scoring_values_3);
exp_gain_3 = @(running_total) EV_3 - (60/216)*running_total;
running_total_limit_3 = fzero(exp_gain_3, 300);

%% Two dice
scoring_probs_2 = [10 10] ./ 36;
scoring_values_2 = [100 50];

EV_2 = sum(scoring_probs_2.*scoring_values_2);
exp_gain_2 = @(running_total) EV_2 - (16/36)*running_total;
running_total_limit_2 = fzero(exp_gain_2, 300);

%% One dice
scoring_probs_1 = [1 1] ./ 6;
scoring_values_1 = [100 50];

EV_1 = sum(scoring_probs_1.*scoring_values_1);
exp_gain_1 = @(running_total) EV_1 - (4/6)*running_total;
running_total_limit_1 = fzero(exp_gain_1, 300);