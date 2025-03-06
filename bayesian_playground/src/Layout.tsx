// src/Layout.tsx
import React, { FC, useState } from "react";
import { Container, Stack, Box } from "@mui/material";
import Header from "./components/Header";
import HyperparameterTable from "./components/HyperparameterTable";
import MainChart from "./components/MainChart";
import RMSChart from "./components/RMSChart";
import StepControls from "./components/StepControls";
import DebugConsole from "./components/DebugConsole";
import { useBayesianSimulation } from "./hooks/useBayesianSimulation";

const Layout: FC = () => {
  const [stepIndex, setStepIndex] = useState(0);
  const [acquisitionFn, setAcquisitionFn] = useState("UCB"); // Default: "UCB"
  // Pass acquisitionFn to the hook
  const { bayesianData, rmsErrors, totalSteps, setTotalSteps, logs } = useBayesianSimulation(acquisitionFn);

  return (
    <Container maxWidth="lg" sx={{ padding: 2 }}>
      <Stack spacing={2}>
        <Header />

        <Stack direction={{ xs: "column", md: "row" }} spacing={2}>
          <Box flex={1}>
            {/* Provide acquisitionFn to HyperparameterTable */}
            <HyperparameterTable
              acquisitionFn={acquisitionFn}
              setAcquisitionFn={setAcquisitionFn}
            />
          </Box>
          <Box flex={2}>
            <MainChart bayesianData={bayesianData} stepIndex={stepIndex} />
          </Box>
        </Stack>

        <Stack direction={{ xs: "column", md: "row" }} spacing={2}>
          <Box flex={1}>
            <RMSChart 
              rmsErrors={rmsErrors} 
              stepIndex={stepIndex}
              setStepIndex={setStepIndex}
            />
          </Box>
          <Box flex={1}>
            <StepControls
              stepIndex={stepIndex}
              setStepIndex={setStepIndex}
              totalSteps={totalSteps}
              setTotalSteps={setTotalSteps}
            />
          </Box>
        </Stack>

        <DebugConsole logs={logs} />
      </Stack>
    </Container>
  );
};

export default Layout;
