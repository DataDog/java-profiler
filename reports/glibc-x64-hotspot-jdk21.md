---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:20:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 64-73 cores)</summary>

```
1786526131 66
1786526136 66
1786526141 66
1786526146 66
1786526151 66
1786526156 66
1786526161 66
1786526166 64
1786526171 64
1786526176 64
1786526181 64
1786526186 64
1786526191 64
1786526196 64
1786526201 64
1786526206 71
1786526211 71
1786526216 73
1786526221 73
1786526226 73
```
</details>

---

