---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 13:50:11 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 14 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 36-53 cores)</summary>

```
1793731584 36
1793731589 36
1793731594 36
1793731599 36
1793731604 36
1793731609 36
1793731614 36
1793731619 36
1793731624 36
1793731629 53
1793731634 53
1793731639 53
1793731644 53
1793731649 53
1793731654 53
1793731659 53
1793731664 53
1793731669 53
1793731674 53
1793731679 53
```
</details>

---

