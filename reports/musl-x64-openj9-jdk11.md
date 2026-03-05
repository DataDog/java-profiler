---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-05 13:29:25 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 9 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 29-64 cores)</summary>

```
1772735010 29
1772735015 29
1772735020 29
1772735025 29
1772735030 29
1772735035 29
1772735040 29
1772735045 29
1772735050 29
1772735055 29
1772735060 29
1772735065 29
1772735070 29
1772735075 29
1772735080 29
1772735085 64
1772735090 64
1772735095 46
1772735100 46
1772735105 46
```
</details>

---

