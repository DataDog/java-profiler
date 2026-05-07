---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 12:39:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 50-60 cores)</summary>

```
1778171735 60
1778171740 60
1778171745 60
1778171750 60
1778171755 60
1778171760 60
1778171765 60
1778171770 60
1778171775 50
1778171780 50
1778171785 55
1778171790 55
1778171795 55
1778171800 55
1778171805 55
1778171810 55
1778171815 55
1778171820 55
1778171825 55
1778171830 55
```
</details>

---

