// src/components/StepControls.tsx
import React, { FC, ChangeEvent, KeyboardEvent } from "react";
import {
  Paper,
  Typography,
  Slider,
  TextField,
  Box,
  IconButton,
} from "@mui/material";
import ArrowBackIosIcon from "@mui/icons-material/ArrowBackIos";
import ArrowForwardIosIcon from "@mui/icons-material/ArrowForwardIos";

interface StepControlsProps {
  stepIndex: number;
  setStepIndex: (index: number) => void;
  totalSteps: number;
  setTotalSteps: (steps: number) => void;
}

const StepControls: FC<StepControlsProps> = ({
  stepIndex,
  setStepIndex,
  totalSteps,
  setTotalSteps,
}) => {
  // Handler for slider changes
  const handleSliderChange = (_: Event, newValue: number | number[]) => {
    if (typeof newValue === "number") {
      setStepIndex(newValue);
    }
  };

  // Handler for textbox changes
  const handleTextChange = (e: ChangeEvent<HTMLInputElement>) => {
    const value = Number(e.target.value);
    if (!isNaN(value)) {
      const clamped = Math.max(0, Math.min(value, totalSteps - 1));
      setStepIndex(clamped);
    }
  };

  // Backward and forward button handlers
  const handleBackward = () => {
    setStepIndex(Math.max(0, stepIndex - 1));
  };

  const handleForward = () => {
    setStepIndex(Math.min(totalSteps - 1, stepIndex + 1));
  };

  // Keyboard handler: left arrow or "<" moves back; right arrow or ">" moves forward.
  const handleKeyDown = (e: KeyboardEvent<HTMLDivElement>) => {
    if (e.key === "ArrowLeft" || e.key === "<") {
      handleBackward();
    } else if (e.key === "ArrowRight" || e.key === ">") {
      handleForward();
    }
  };

  return (
    <Paper
      sx={{ padding: 2, textAlign: "center" }}
      tabIndex={0}
      onKeyDown={handleKeyDown}
    >
      <Typography variant="h6">Step Controls</Typography>

      {/* Slider Section: only numbers displayed */}
      <Box
        sx={{
          display: "flex",
          alignItems: "center",
          justifyContent: "center",
          mt: 2,
        }}
      >
        <Typography variant="body1" sx={{ mr: 1 }}>
          0
        </Typography>
        <Slider
          value={stepIndex}
          onChange={handleSliderChange}
          min={0}
          max={totalSteps - 1}
          step={1}
          sx={{ width: "60%", mx: 2 }}
        />
        <Typography variant="body1">{totalSteps - 1}</Typography>
      </Box>

      {/* Step textbox with forward/back buttons */}
      <Box sx={{ mt: 2, textAlign: "center" }}>
        <Typography variant="body1">Step:</Typography>
        <Box
          sx={{
            display: "flex",
            alignItems: "center",
            justifyContent: "center",
            mt: 1,
          }}
        >
          <IconButton onClick={handleBackward} aria-label="Previous Step">
            <ArrowBackIosIcon />
          </IconButton>
          <TextField
            value={stepIndex}
            onChange={handleTextChange}
            type="number"
            inputProps={{
              min: 0,
              max: totalSteps - 1,
              style: {
                textAlign: "center",
                fontFamily: "monospace",
                fontSize: "1.2rem",
              },
            }}
            sx={{ width: 80, mx: 1 }}
          />
          <IconButton onClick={handleForward} aria-label="Next Step">
            <ArrowForwardIosIcon />
          </IconButton>
        </Box>
      </Box>
    </Paper>
  );
};

export default StepControls;
