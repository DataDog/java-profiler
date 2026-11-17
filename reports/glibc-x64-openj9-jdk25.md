---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 12:45:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 11 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (4 unique values: 46-56 cores)</summary>

```
1794937270 56
1794937275 56
1794937280 56
1794937285 56
1794937290 56
1794937295 56
1794937300 56
1794937305 56
1794937310 56
1794937315 54
1794937320 54
1794937325 54
1794937330 54
1794937335 48
1794937340 48
1794937345 48
1794937350 48
1794937355 48
1794937360 48
1794937365 48
```
</details>

---

