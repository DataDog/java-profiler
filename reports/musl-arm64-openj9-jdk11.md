---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:16:27 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1104 |
| Sample Rate | 18.40/sec |
| Health Score | 1150% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1795108256 29
1795108261 29
1795108266 29
1795108271 29
1795108276 29
1795108281 29
1795108286 29
1795108291 29
1795108296 24
1795108301 24
1795108306 24
1795108311 24
1795108316 24
1795108321 24
1795108326 24
1795108331 24
1795108336 24
1795108341 24
1795108346 24
1795108351 24
```
</details>

---

