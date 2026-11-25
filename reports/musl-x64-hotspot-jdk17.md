---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:29:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 73-81 cores)</summary>

```
1795627495 73
1795627500 73
1795627505 73
1795627510 73
1795627515 73
1795627520 73
1795627525 73
1795627530 73
1795627535 73
1795627540 73
1795627545 73
1795627550 73
1795627555 73
1795627560 73
1795627565 73
1795627570 73
1795627575 81
1795627580 81
1795627585 81
1795627590 81
```
</details>

---

