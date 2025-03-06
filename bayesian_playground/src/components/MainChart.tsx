// src/components/MainChart.tsx
import { FC, useEffect, useState } from "react";
import Plot from "react-plotly.js";
import { Paper, Typography } from "@mui/material";
import { PlotData } from "plotly.js";
import ErrorBoundary from "./ErrorBoundary";
import { gpRegression, trueFunction } from "../utils/gpUtils";

interface MainChartProps {
  stepIndex: number;
  bayesianData: PlotData[]; // each trace from simulation (sampled points per step)
}

const X_PRED = Array.from({ length: 100 }, (_, i) => (i / 100) * 4 * Math.PI);

// Generate the true function curve
const generateSinWave = (): PlotData =>
  ({
    x: X_PRED,
    y: X_PRED.map((x) => trueFunction(x)),
    type: "scatter",
    mode: "lines",
    name: "True Function: sin(x)",
  }) as PlotData;

const MainChart: FC<MainChartProps> = ({ stepIndex, bayesianData }) => {
  const [estimatedFunction, setEstimatedFunction] = useState<{
    mean: number[];
    stdDev: number[];
  }>({ mean: [], stdDev: [] });

  // Whenever bayesianData or the current step changes, update the GP estimation.
  useEffect(() => {
    // Check if we have valid data for the current step.
    if (bayesianData.length > 0) {
      // Use the cumulative trace (last element) then slice up to current step.
      const cumulativeTrace = bayesianData[bayesianData.length - 1];
      const fullX = Array.isArray(cumulativeTrace.x)
        ? (cumulativeTrace.x as number[])
        : [];
      const fullY = Array.isArray(cumulativeTrace.y)
        ? (cumulativeTrace.y as number[])
        : [];
      // Only use points up to the current step (assuming stepIndex is 0-indexed)
      const X_train = fullX.slice(0, stepIndex + 1);
      const Y_train = fullY.slice(0, stepIndex + 1);
      if (X_train.length > 0 && Y_train.length > 0) {
        const result = gpRegression(X_train, Y_train, X_PRED);
        setEstimatedFunction(result);
      } else {
        setEstimatedFunction({ mean: [], stdDev: [] });
      }
    }
  }, [bayesianData, stepIndex]);

  // Build uncertainty bands if we have a valid GP estimation.
  const uncertaintyUpper = estimatedFunction.mean.map(
    (m, i) => m + 2 * (estimatedFunction.stdDev[i] || 0),
  );
  const uncertaintyLower = estimatedFunction.mean.map(
    (m, i) => m - 2 * (estimatedFunction.stdDev[i] || 0),
  );

  // Assemble the plot data.
  const plotData: PlotData[] = [
    generateSinWave(),
    // Only show GP curves if we have computed a mean.
    ...(estimatedFunction.mean.length > 0
      ? [
          {
            x: X_PRED,
            y: estimatedFunction.mean,
            type: "scatter",
            mode: "lines",
            line: { dash: "dot", color: "blue" },
            name: "GP Estimated Mean",
          } as PlotData,
          {
            x: X_PRED,
            y: uncertaintyUpper,
            type: "scatter",
            mode: "lines",
            fill: "tonexty",
            line: { color: "rgba(0,0,255,0.2)" },
            name: "Uncertainty Upper Bound",
          } as PlotData,
          {
            x: X_PRED,
            y: uncertaintyLower,
            type: "scatter",
            mode: "lines",
            fill: "tonexty",
            line: { color: "rgba(0,0,255,0.2)" },
            name: "Uncertainty Lower Bound",
          } as PlotData,
        ]
      : []),
    // Display sampled points up to the current step.
    ...(bayesianData.length > 0
      ? [
          {
            x: (Array.isArray(bayesianData[bayesianData.length - 1].x)
              ? (bayesianData[bayesianData.length - 1].x as number[])
              : []
            ).slice(0, stepIndex + 1),
            y: (Array.isArray(bayesianData[bayesianData.length - 1].y)
              ? (bayesianData[bayesianData.length - 1].y as number[])
              : []
            ).slice(0, stepIndex + 1),
            type: "scatter",
            mode: "markers",
            marker: { color: "red", size: 8 },
            name: "Sampled Points",
          } as PlotData,
        ]
      : []),
  ];

  return (
    <ErrorBoundary>
      <Paper sx={{ padding: 2 }}>
        <Typography variant="h6">
          Main Chart (Bayesian Optimization Visualization)
        </Typography>
        <Plot
          data={plotData}
          layout={{
            width: 600,
            height: 400,
            title: "True Function & Bayesian Estimate",
          }}
        />
      </Paper>
    </ErrorBoundary>
  );
};

export default MainChart;
