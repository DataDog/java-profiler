---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 09:06:23 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 9 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 19-27 cores)</summary>

```
1790859727 27
1790859732 27
1790859737 27
1790859742 27
1790859747 27
1790859752 27
1790859757 27
1790859762 27
1790859767 27
1790859772 27
1790859777 27
1790859782 27
1790859787 27
1790859792 27
1790859797 27
1790859802 27
1790859807 27
1790859812 27
1790859817 19
1790859822 19
```
</details>

---

