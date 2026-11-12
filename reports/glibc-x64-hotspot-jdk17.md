---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:57:34 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (6 unique values: 81-91 cores)</summary>

```
1794498708 83
1794498713 81
1794498718 81
1794498723 81
1794498728 81
1794498733 81
1794498738 86
1794498743 86
1794498749 86
1794498754 88
1794498759 88
1794498764 88
1794498769 90
1794498774 90
1794498779 90
1794498784 90
1794498789 90
1794498794 90
1794498799 90
1794498804 90
```
</details>

---

