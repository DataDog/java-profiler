---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 00:56:48 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 8 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 8 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 27-60 cores)</summary>

```
1790052737 50
1790052742 50
1790052747 50
1790052752 50
1790052757 50
1790052762 50
1790052767 50
1790052772 50
1790052777 50
1790052782 50
1790052787 50
1790052792 50
1790052797 50
1790052802 50
1790052807 50
1790052812 60
1790052817 60
1790052822 60
1790052827 60
1790052832 60
```
</details>

---

