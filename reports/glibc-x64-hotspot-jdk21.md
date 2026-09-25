---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 51-63 cores)</summary>

```
1790336010 51
1790336015 51
1790336020 51
1790336025 51
1790336030 51
1790336035 51
1790336040 51
1790336045 51
1790336050 51
1790336055 51
1790336060 51
1790336065 51
1790336070 61
1790336075 61
1790336080 61
1790336085 61
1790336090 63
1790336095 63
1790336100 63
1790336105 63
```
</details>

---

