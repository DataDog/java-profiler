---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 19:10:08 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 71-94 cores)</summary>

```
1789686356 73
1789686361 73
1789686366 73
1789686371 73
1789686376 73
1789686381 73
1789686386 71
1789686391 71
1789686396 71
1789686401 71
1789686406 71
1789686411 79
1789686416 79
1789686421 92
1789686426 92
1789686431 92
1789686436 92
1789686441 92
1789686446 92
1789686451 94
```
</details>

---

