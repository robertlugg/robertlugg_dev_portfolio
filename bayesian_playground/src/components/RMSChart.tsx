import React, { FC } from "react";
import Plot from "react-plotly.js";
import { Paper, Typography } from "@mui/material";

interface RMSChartProps {
  rmsErrors: number[];
  stepIndex: number;
  setStepIndex: (newStep: number) => void;
}

const RMSChart: FC<RMSChartProps> = ({ rmsErrors, stepIndex, setStepIndex }) => {
  // Create X array = [0, 1, 2, ...]
  const xValues = Array.from({ length: rmsErrors.length }, (_, i) => i);

  return (
    <Paper sx={{ padding: 2, height: "100%" }}>
      <Typography variant="h6" gutterBottom>
        RMS Error Over Iterations
      </Typography>
      <Plot
        data={[
          {
            x: xValues,
            y: rmsErrors,
            type: "scatter",
            mode: "lines+markers",
            name: "RMS Error"
          }
        ]}
        layout={{
          title: "RMS Error",
          autosize: true,
          margin: { t: 40, r: 20, b: 40, l: 50 },
          yaxis: { rangemode: "tozero" }, // Force Y to start at 0
          dragmode: "pan",
          shapes: [
            // A vertical line at x=stepIndex, spanning the entire chart's Y
            {
              type: "line",
              xref: "x",
              yref: "paper", // so it goes from top to bottom
              x0: stepIndex,
              x1: stepIndex,
              y0: 0,
              y1: .5,
              line: {
                color: "red",
                width: 2
              }
            }
          ]
        }}
        style={{ width: "100%", height: "100%" }}
        useResizeHandler
        config={{
          editable: true // allow shape dragging
        }}
        // This fires whenever shapes or layout get updated
        onRelayout={(figure: Readonly<Plotly.PlotRelayoutEvent>) => {
          // Check if shape[0] was moved
          const shapes = figure["shapes"] as Plotly.Shape[];
          if (shapes && shapes[0] && shapes[0].x0 !== undefined) {
            const newX = shapes[0].x0 as number;
            // Convert to an integer step (or clamp if needed)
            const newStep = Math.max(0, Math.min(Math.round(newX), rmsErrors.length - 1));
            setStepIndex(newStep);
          }
        }}
      />
    </Paper>
  );
};

export default RMSChart;
