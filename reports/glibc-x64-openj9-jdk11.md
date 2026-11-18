---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 14:19:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (5 unique values: 69-81 cores)</summary>

```
1795029324 79
1795029329 79
1795029334 79
1795029339 79
1795029344 79
1795029349 79
1795029354 79
1795029359 81
1795029364 81
1795029369 81
1795029374 81
1795029379 81
1795029384 73
1795029389 73
1795029394 73
1795029399 73
1795029404 73
1795029409 73
1795029414 71
1795029419 71
```
</details>

---

