---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 05:55:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1792403525 74
1792403530 74
1792403535 74
1792403540 76
1792403545 76
1792403550 76
1792403555 76
1792403560 76
1792403565 76
1792403570 76
1792403575 76
1792403580 76
1792403585 76
1792403590 76
1792403595 76
1792403600 76
1792403605 76
1792403610 76
1792403615 76
1792403620 76
```
</details>

---

