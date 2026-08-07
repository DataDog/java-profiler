---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-07 12:24:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 12 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 30-51 cores)</summary>

```
1786119594 30
1786119599 51
1786119604 51
1786119609 51
1786119614 51
1786119619 51
1786119624 51
1786119629 51
1786119634 51
1786119639 51
1786119644 51
1786119649 51
1786119654 51
1786119659 51
1786119664 51
1786119669 51
1786119674 51
1786119679 51
1786119684 51
1786119689 51
```
</details>

---

