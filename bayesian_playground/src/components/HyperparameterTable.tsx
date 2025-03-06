// src/components/HyperparameterTable.tsx
import { FC } from "react";
import {
  Paper,
  Typography,
  Table,
  TableContainer,
  TableHead,
  TableRow,
  TableCell,
  TableBody,
  FormControl,
  InputLabel,
  Select,
  MenuItem,
} from "@mui/material";

interface HyperparameterTableProps {
  acquisitionFn: string;
  setAcquisitionFn: (fn: string) => void;
}

const HyperparameterTable: FC<HyperparameterTableProps> = ({
  acquisitionFn,
  setAcquisitionFn,
}) => (
  <Paper sx={{ padding: 2 }}>
    <Typography variant="h6">Hyperparameters</Typography>

    {/* Acquisition function selection */}
    <FormControl fullWidth sx={{ my: 2 }}>
      <InputLabel id="acquisition-label">Acquisition Function</InputLabel>
      <Select
        labelId="acquisition-label"
        value={acquisitionFn}
        label="Acquisition Function"
        onChange={(e) => setAcquisitionFn(e.target.value)}
      >
        <MenuItem value="UCB">Upper Confidence Bound (UCB)</MenuItem>
        <MenuItem value="EI">Expected Improvement (EI)</MenuItem>
        <MenuItem value="PI">Probability of Improvement (PI)</MenuItem>
      </Select>
    </FormControl>

    <TableContainer>
      <Table>
        <TableHead>
          <TableRow>
            <TableCell>#</TableCell>
            <TableCell>Name</TableCell>
            <TableCell>Both</TableCell>
            <TableCell>Points</TableCell>
            <TableCell>Line</TableCell>
            <TableCell>Length Scale</TableCell>
            <TableCell>Noise</TableCell>
            <TableCell>Jitter</TableCell>
            <TableCell>Remove</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          <TableRow>
            <TableCell>1</TableCell>
            <TableCell>Row 1</TableCell>
            <TableCell>✔</TableCell>
            <TableCell>✔</TableCell>
            <TableCell>✔</TableCell>
            <TableCell>1</TableCell>
            <TableCell>0.1</TableCell>
            <TableCell>□</TableCell>
            <TableCell>X</TableCell>
          </TableRow>
        </TableBody>
      </Table>
    </TableContainer>
  </Paper>
);

export default HyperparameterTable;
