---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-12 10:27:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 886 |
| Sample Rate | 14.77/sec |
| Health Score | 923% |
| Threads | 12 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 62-67 cores)</summary>

```
1773325304 62
1773325309 62
1773325314 62
1773325319 62
1773325324 62
1773325329 64
1773325334 64
1773325339 67
1773325344 67
1773325349 67
1773325354 67
1773325359 67
1773325364 67
1773325369 67
1773325374 67
1773325379 67
1773325384 67
1773325389 67
1773325394 67
1773325399 67
```
</details>

---

