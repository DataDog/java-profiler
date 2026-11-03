---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:22:17 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1793722589 60
1793722594 60
1793722599 60
1793722604 60
1793722609 60
1793722614 60
1793722619 60
1793722624 60
1793722629 60
1793722634 60
1793722639 60
1793722644 60
1793722649 60
1793722654 60
1793722659 60
1793722664 60
1793722669 60
1793722674 62
1793722679 62
1793722684 62
```
</details>

---

