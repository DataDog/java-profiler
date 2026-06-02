package com.datadoghq.profiler;

public enum AgentPhase {
    IDLE("idle"),
    CONTEXT_BUILD("context_build"),
    AWAITING_INFERENCE("awaiting_inference"),
    TOOL_EXECUTION("tool_execution"),
    TOKENIZING("tokenizing"),
    EMBEDDING("embedding"),
    RETRYING("retrying"),
    SERIALIZING("serializing"),
    INFERENCE_WAIT("inference_wait");

    public static final String ATTRIBUTE_NAME = "llm.agent.phase";

    private final String token;

    AgentPhase(String token) {
        this.token = token;
    }

    public String token() {
        return token;
    }
}
