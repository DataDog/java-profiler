---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:29:25 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 12 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (3 unique values: 69-80 cores)</summary>

```
1772735018 80
1772735023 80
1772735028 80
1772735033 80
1772735038 80
1772735043 80
1772735048 80
1772735053 80
1772735058 80
1772735063 80
1772735068 80
1772735073 80
1772735078 80
1772735083 80
1772735088 80
1772735094 80
1772735099 80
1772735104 80
1772735109 69
1772735114 69
```
</details>

---

