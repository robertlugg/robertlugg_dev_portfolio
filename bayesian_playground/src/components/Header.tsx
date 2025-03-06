// src/components/Header.tsx
import React, { FC } from "react";
import { Paper, Typography } from "@mui/material";

const Header: FC = () => (
    <Paper sx={{ padding: 2, textAlign: "center" }}>
        <Typography variant="h5">Bayesian 1D Curve Fitting</Typography>
    </Paper>
);

export default Header;