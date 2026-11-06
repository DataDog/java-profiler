---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-06 16:43:55 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1794001112 77
1794001117 77
1794001122 77
1794001127 77
1794001132 79
1794001137 79
1794001142 79
1794001147 79
1794001152 79
1794001157 79
1794001162 79
1794001167 79
1794001172 79
1794001177 79
1794001182 79
1794001187 79
1794001192 79
1794001197 79
1794001202 79
1794001207 79
```
</details>

---

