import { FC } from "react";
import Plot from "react-plotly.js";
import { Paper, Typography } from "@mui/material";
import ErrorBoundary from "./ErrorBoundary";

interface PlotWrapperProps {
  title: string;
  data: Plotly.Data[];
  width?: number;
  height?: number;
}

const PlotWrapper: FC<PlotWrapperProps> = ({
  title,
  data,
  width = 600,
  height = 400,
}) => (
  <ErrorBoundary>
    <Paper sx={{ padding: 2 }}>
      <Typography variant="h6">{title}</Typography>
      <Plot data={data} layout={{ width, height, title }} />
    </Paper>
  </ErrorBoundary>
);

export default PlotWrapper;
