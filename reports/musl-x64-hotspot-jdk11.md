---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-05 13:29:25 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 41-51 cores)</summary>

```
1772734990 45
1772734995 41
1772735000 41
1772735005 41
1772735010 41
1772735015 41
1772735020 41
1772735025 41
1772735030 41
1772735035 41
1772735040 41
1772735045 43
1772735050 43
1772735055 43
1772735060 43
1772735065 43
1772735070 43
1772735075 43
1772735080 43
1772735085 47
```
</details>

---

