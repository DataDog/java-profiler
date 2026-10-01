---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-01 09:06:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1790859737 29
1790859742 29
1790859747 27
1790859752 27
1790859757 30
1790859762 30
1790859767 30
1790859772 30
1790859777 30
1790859782 30
1790859787 30
1790859792 30
1790859797 30
1790859802 32
1790859807 32
1790859812 32
1790859817 32
1790859822 27
1790859827 27
1790859832 27
```
</details>

---

