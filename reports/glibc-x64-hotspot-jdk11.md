---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 19:24:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (6 unique values: 69-78 cores)</summary>

```
1778541632 74
1778541637 74
1778541642 78
1778541647 78
1778541652 78
1778541657 78
1778541662 72
1778541667 72
1778541672 72
1778541677 72
1778541682 72
1778541687 76
1778541692 76
1778541697 71
1778541702 71
1778541707 71
1778541712 71
1778541717 71
1778541722 71
1778541727 69
```
</details>

---

