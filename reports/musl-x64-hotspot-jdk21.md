---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:21:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (3 unique values: 29-68 cores)</summary>

```
1795641273 29
1795641278 29
1795641283 66
1795641288 66
1795641293 66
1795641298 66
1795641303 68
1795641308 68
1795641313 68
1795641318 68
1795641323 66
1795641328 66
1795641333 66
1795641338 66
1795641343 66
1795641348 66
1795641353 66
1795641358 66
1795641363 66
1795641368 66
```
</details>

---

