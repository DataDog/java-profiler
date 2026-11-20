---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:12:25 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 11 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (3 unique values: 29-64 cores)</summary>

```
1795194443 49
1795194448 49
1795194453 49
1795194458 49
1795194463 49
1795194468 49
1795194473 49
1795194478 49
1795194483 49
1795194488 49
1795194493 49
1795194498 49
1795194503 49
1795194508 49
1795194513 49
1795194518 49
1795194523 64
1795194528 64
1795194533 64
1795194538 64
```
</details>

---

