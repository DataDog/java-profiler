---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 11:39:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 74-79 cores)</summary>

```
1794328294 74
1794328299 74
1794328304 79
1794328309 79
1794328314 79
1794328319 79
1794328324 79
1794328329 79
1794328334 77
1794328339 77
1794328344 77
1794328349 77
1794328354 77
1794328359 77
1794328364 77
1794328369 77
1794328374 77
1794328379 77
1794328384 77
1794328389 75
```
</details>

---

