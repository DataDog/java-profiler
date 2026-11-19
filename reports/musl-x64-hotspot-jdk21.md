---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 12:16:27 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 40-52 cores)</summary>

```
1795108298 49
1795108303 49
1795108308 49
1795108313 49
1795108318 49
1795108323 49
1795108328 49
1795108333 49
1795108338 49
1795108343 40
1795108348 40
1795108353 40
1795108358 40
1795108363 40
1795108368 40
1795108373 40
1795108378 40
1795108383 40
1795108388 40
1795108393 40
```
</details>

---

