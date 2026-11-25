---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 09:53:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 931 |
| Sample Rate | 15.52/sec |
| Health Score | 970% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 31-33 cores)</summary>

```
1795618080 33
1795618085 33
1795618090 33
1795618095 33
1795618100 33
1795618105 33
1795618110 33
1795618115 33
1795618120 33
1795618125 33
1795618130 33
1795618135 33
1795618140 33
1795618145 33
1795618150 33
1795618155 33
1795618160 31
1795618165 31
1795618170 31
1795618175 31
```
</details>

---

