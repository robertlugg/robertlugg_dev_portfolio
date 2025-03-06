// src/components/DebugConsole.tsx
import { FC } from "react";
import { Paper, Typography } from "@mui/material";

interface DebugConsoleProps {
    logs: string[];
}

const DebugConsole: FC<DebugConsoleProps> = ({ logs }) => (
    <Paper sx={{ padding: 2, backgroundColor: "#f5f5f5", minHeight: 100, maxHeight: 300, overflow: 'auto' }}>
        <Typography variant="h6">Debug Console</Typography>
        <Typography 
            variant="body2" 
            sx={{ 
                whiteSpace: 'pre-wrap',
                fontFamily: 'monospace'
            }}
        >
            {logs.length ? logs.join("") : "No errors logged."}
        </Typography>
    </Paper>
);

export default DebugConsole;