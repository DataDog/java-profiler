---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 10:58:56 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787151306 96
1787151311 94
1787151316 94
1787151321 94
1787151326 94
1787151331 94
1787151336 94
1787151341 96
1787151346 96
1787151351 96
1787151356 96
1787151361 96
1787151366 96
1787151371 96
1787151376 96
1787151381 96
1787151386 96
1787151391 94
1787151396 94
1787151401 94
```
</details>

---

