---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:00:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (4 unique values: 42-64 cores)</summary>

```
1795618513 47
1795618518 47
1795618523 47
1795618528 42
1795618533 42
1795618538 59
1795618543 59
1795618548 59
1795618553 59
1795618558 59
1795618563 59
1795618568 59
1795618573 59
1795618578 59
1795618583 59
1795618588 59
1795618593 59
1795618598 59
1795618603 64
1795618608 64
```
</details>

---

