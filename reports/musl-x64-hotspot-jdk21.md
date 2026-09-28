---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 06:45:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 12-16 cores)</summary>

```
1790592069 14
1790592074 14
1790592079 14
1790592084 14
1790592089 14
1790592094 14
1790592099 14
1790592104 14
1790592109 14
1790592114 14
1790592119 14
1790592124 14
1790592129 14
1790592134 14
1790592139 14
1790592144 14
1790592149 14
1790592154 14
1790592159 12
1790592164 12
```
</details>

---

