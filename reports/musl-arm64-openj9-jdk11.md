---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-12 05:49:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 12 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 10 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1778579052 64
1778579057 64
1778579062 64
1778579067 64
1778579072 64
1778579077 64
1778579082 64
1778579087 64
1778579092 64
1778579097 64
1778579102 64
1778579107 64
1778579112 64
1778579117 64
1778579122 64
1778579127 64
1778579132 64
1778579138 64
1778579143 52
1778579148 52
```
</details>

---

