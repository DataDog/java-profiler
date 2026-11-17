---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 06:43:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 13 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 11 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794915579 51
1794915584 51
1794915589 51
1794915594 51
1794915599 51
1794915604 51
1794915609 51
1794915614 51
1794915619 51
1794915624 51
1794915630 51
1794915635 46
1794915640 46
1794915645 46
1794915650 46
1794915655 46
1794915660 46
1794915665 46
1794915670 46
1794915675 46
```
</details>

---

