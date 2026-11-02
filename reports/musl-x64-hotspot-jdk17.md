---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 10:41:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1793633803 32
1793633808 32
1793633813 32
1793633818 32
1793633823 32
1793633828 32
1793633833 32
1793633838 32
1793633843 32
1793633848 32
1793633853 32
1793633858 32
1793633863 32
1793633868 32
1793633873 30
1793633878 30
1793633883 30
1793633888 30
1793633893 30
1793633898 30
```
</details>

---

