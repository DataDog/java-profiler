---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:18:50 EST

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
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795705987 64
1795705992 64
1795705997 64
1795706002 64
1795706007 64
1795706012 64
1795706017 64
1795706022 64
1795706027 64
1795706032 64
1795706037 64
1795706042 64
1795706047 64
1795706052 64
1795706057 64
1795706062 64
1795706067 64
1795706072 64
1795706077 64
1795706082 64
```
</details>

---

