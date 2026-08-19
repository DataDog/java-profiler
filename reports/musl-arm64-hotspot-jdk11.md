---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-19 13:04:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 13 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1787158802 43
1787158807 43
1787158812 43
1787158817 43
1787158822 43
1787158827 43
1787158832 41
1787158837 41
1787158842 41
1787158847 41
1787158852 41
1787158857 41
1787158862 41
1787158867 41
1787158872 41
1787158877 41
1787158882 43
1787158887 43
1787158892 43
1787158897 43
```
</details>

---

