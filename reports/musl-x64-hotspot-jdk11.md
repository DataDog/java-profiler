---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 09:54:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 786 |
| Sample Rate | 13.10/sec |
| Health Score | 819% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1790257767 88
1790257772 88
1790257777 88
1790257782 88
1790257787 88
1790257792 88
1790257797 88
1790257802 88
1790257807 88
1790257812 86
1790257817 86
1790257822 86
1790257827 86
1790257832 86
1790257837 86
1790257842 86
1790257847 88
1790257852 88
1790257857 88
1790257862 88
```
</details>

---

