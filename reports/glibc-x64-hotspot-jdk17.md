---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-05 20:23:04 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (5 unique values: 21-62 cores)</summary>

```
1793927846 29
1793927851 29
1793927856 29
1793927861 29
1793927866 29
1793927871 29
1793927876 29
1793927881 29
1793927886 29
1793927891 29
1793927896 29
1793927901 29
1793927906 29
1793927911 29
1793927916 62
1793927921 62
1793927926 42
1793927931 42
1793927936 42
1793927941 42
```
</details>

---

