---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-26 01:04:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1787720297 29
1787720302 29
1787720307 29
1787720312 27
1787720317 27
1787720322 27
1787720327 27
1787720333 27
1787720338 27
1787720343 27
1787720348 27
1787720353 27
1787720358 27
1787720363 29
1787720368 29
1787720373 29
1787720378 29
1787720383 29
1787720388 29
1787720393 29
```
</details>

---

