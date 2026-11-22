---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 05:47:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 9 |
| Allocations | 123 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795344226 59
1795344231 59
1795344236 59
1795344241 59
1795344246 59
1795344251 64
1795344256 64
1795344261 59
1795344266 59
1795344271 59
1795344276 59
1795344281 59
1795344286 59
1795344291 59
1795344296 59
1795344301 59
1795344306 59
1795344311 59
1795344316 59
1795344321 59
```
</details>

---

