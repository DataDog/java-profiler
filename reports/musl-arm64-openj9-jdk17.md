---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:01:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 12 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795618530 64
1795618535 64
1795618540 64
1795618545 64
1795618550 64
1795618555 64
1795618560 64
1795618565 64
1795618570 64
1795618575 64
1795618580 64
1795618585 64
1795618590 47
1795618595 47
1795618600 47
1795618605 47
1795618610 47
1795618615 47
1795618620 47
1795618625 47
```
</details>

---

