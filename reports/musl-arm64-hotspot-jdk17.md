---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 09:54:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 13 |
| Allocations | 166 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1790257777 48
1790257782 48
1790257787 48
1790257792 48
1790257797 48
1790257802 48
1790257807 48
1790257812 48
1790257817 48
1790257822 48
1790257827 48
1790257832 48
1790257837 48
1790257842 48
1790257847 48
1790257852 48
1790257857 48
1790257862 48
1790257867 48
1790257872 48
```
</details>

---

