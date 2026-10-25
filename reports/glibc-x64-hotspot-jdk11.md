---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-25 06:56:10 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1792925307 94
1792925312 94
1792925317 94
1792925322 94
1792925327 94
1792925333 92
1792925338 92
1792925343 92
1792925348 92
1792925353 92
1792925358 92
1792925363 94
1792925368 94
1792925373 94
1792925378 96
1792925383 96
1792925388 96
1792925393 96
1792925398 96
1792925403 96
```
</details>

---

