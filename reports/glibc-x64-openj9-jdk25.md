---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 11:54:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 943 |
| Sample Rate | 15.72/sec |
| Health Score | 982% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1770137309 29
1770137314 28
1770137319 28
1770137324 28
1770137329 28
1770137334 28
1770137339 29
1770137344 29
1770137349 29
1770137354 29
1770137359 29
1770137364 29
1770137369 29
1770137374 32
1770137379 32
1770137384 32
1770137389 32
1770137394 32
1770137399 32
1770137404 29
```
</details>

---

