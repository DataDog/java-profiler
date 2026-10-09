---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 03:39:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (6 unique values: 52-86 cores)</summary>

```
1791531220 84
1791531225 86
1791531230 86
1791531235 86
1791531240 86
1791531245 66
1791531250 66
1791531255 66
1791531260 64
1791531265 64
1791531270 64
1791531275 64
1791531280 64
1791531285 64
1791531290 64
1791531295 64
1791531300 64
1791531305 64
1791531310 64
1791531315 64
```
</details>

---

