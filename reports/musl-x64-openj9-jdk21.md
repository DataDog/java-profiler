---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-28 12:10:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 52-58 cores)</summary>

```
1777392269 58
1777392274 58
1777392279 58
1777392284 53
1777392289 53
1777392294 53
1777392299 53
1777392304 53
1777392309 53
1777392314 57
1777392319 57
1777392324 52
1777392329 52
1777392334 52
1777392339 52
1777392344 52
1777392349 52
1777392354 52
1777392359 52
1777392364 52
```
</details>

---

