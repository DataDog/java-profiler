---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-12 09:25:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 39-51 cores)</summary>

```
1791811269 51
1791811274 51
1791811279 51
1791811284 51
1791811289 51
1791811294 51
1791811299 51
1791811304 46
1791811309 46
1791811314 41
1791811319 41
1791811324 41
1791811329 41
1791811334 41
1791811339 41
1791811344 41
1791811349 41
1791811354 39
1791811359 39
1791811364 39
```
</details>

---

