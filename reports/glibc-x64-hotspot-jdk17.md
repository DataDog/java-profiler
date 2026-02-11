---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-11 11:22:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 324 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1770826591 90
1770826596 90
1770826601 95
1770826606 95
1770826611 95
1770826616 95
1770826621 95
1770826626 95
1770826631 95
1770826636 96
1770826641 96
1770826646 96
1770826651 96
1770826656 96
1770826661 96
1770826666 96
1770826671 96
1770826676 96
1770826681 96
1770826686 96
```
</details>

---

