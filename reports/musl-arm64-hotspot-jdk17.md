---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-16 14:42:44 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 11 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (2 unique values: 26-28 cores)</summary>

```
1786905532 28
1786905537 28
1786905542 28
1786905547 28
1786905552 28
1786905557 28
1786905562 28
1786905567 28
1786905572 28
1786905577 28
1786905582 28
1786905587 28
1786905592 28
1786905597 28
1786905602 28
1786905607 28
1786905612 28
1786905617 28
1786905622 28
1786905627 26
```
</details>

---

