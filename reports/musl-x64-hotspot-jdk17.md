---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-09-17 15:34:00 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 89-91 cores)</summary>

```
1789673345 89
1789673350 89
1789673355 89
1789673360 89
1789673365 89
1789673370 89
1789673375 89
1789673380 89
1789673385 89
1789673390 89
1789673395 91
1789673400 91
1789673405 91
1789673410 91
1789673415 91
1789673420 91
1789673425 91
1789673430 91
1789673435 91
1789673440 91
```
</details>

---

