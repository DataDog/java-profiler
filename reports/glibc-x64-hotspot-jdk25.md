---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 16:43:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 91-93 cores)</summary>

```
1794001132 91
1794001137 91
1794001142 91
1794001147 91
1794001152 91
1794001157 91
1794001162 91
1794001167 91
1794001172 91
1794001177 91
1794001182 91
1794001187 91
1794001192 91
1794001197 91
1794001202 93
1794001207 93
1794001212 93
1794001217 93
1794001222 93
1794001227 93
```
</details>

---

