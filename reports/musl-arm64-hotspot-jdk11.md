---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:13:40 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795194483 50
1795194488 50
1795194493 50
1795194498 50
1795194503 50
1795194508 50
1795194513 50
1795194518 50
1795194523 50
1795194528 50
1795194533 50
1795194538 50
1795194543 50
1795194548 50
1795194553 50
1795194558 50
1795194563 50
1795194568 50
1795194573 50
1795194578 50
```
</details>

---

