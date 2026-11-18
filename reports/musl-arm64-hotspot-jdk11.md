---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:31:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 10 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 22-34 cores)</summary>

```
1795008270 29
1795008275 29
1795008280 29
1795008285 29
1795008290 29
1795008295 29
1795008300 34
1795008305 34
1795008310 34
1795008315 34
1795008320 34
1795008325 34
1795008330 34
1795008335 34
1795008340 22
1795008345 22
1795008350 22
1795008355 22
1795008360 22
1795008365 22
```
</details>

---

