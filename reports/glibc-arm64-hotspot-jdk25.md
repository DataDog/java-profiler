---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-01 09:06:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (5 unique values: 21-43 cores)</summary>

```
1790859752 21
1790859757 21
1790859762 21
1790859767 21
1790859772 21
1790859777 21
1790859782 30
1790859787 30
1790859792 39
1790859797 39
1790859802 39
1790859807 39
1790859812 39
1790859817 39
1790859822 39
1790859827 39
1790859832 43
1790859837 43
1790859842 43
1790859848 43
```
</details>

---

