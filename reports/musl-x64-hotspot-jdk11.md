---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 09:14:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 9 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1786367345 64
1786367350 64
1786367355 64
1786367360 64
1786367365 64
1786367370 64
1786367375 64
1786367380 62
1786367385 62
1786367390 60
1786367395 60
1786367400 60
1786367405 60
1786367410 60
1786367415 60
1786367420 60
1786367425 60
1786367430 60
1786367435 60
1786367440 60
```
</details>

---

