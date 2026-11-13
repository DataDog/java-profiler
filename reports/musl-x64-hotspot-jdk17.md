---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 11:44:56 EST

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
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 80-88 cores)</summary>

```
1794587964 80
1794587969 80
1794587974 80
1794587979 80
1794587985 80
1794587990 80
1794587995 80
1794588000 80
1794588005 80
1794588010 80
1794588015 80
1794588020 80
1794588025 80
1794588030 80
1794588035 80
1794588040 80
1794588045 80
1794588050 88
1794588055 88
1794588060 88
```
</details>

---

