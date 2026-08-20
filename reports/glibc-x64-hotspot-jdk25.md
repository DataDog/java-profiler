---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 12:31:53 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (5 unique values: 71-79 cores)</summary>

```
1787243190 71
1787243195 71
1787243200 71
1787243205 71
1787243210 71
1787243215 71
1787243220 71
1787243225 71
1787243230 71
1787243235 73
1787243240 73
1787243245 71
1787243250 71
1787243255 71
1787243260 75
1787243265 75
1787243270 75
1787243275 75
1787243280 77
1787243285 77
```
</details>

---

