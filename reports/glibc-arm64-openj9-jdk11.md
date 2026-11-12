---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 08:53:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 13 |
| Allocations | 177 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794491384 51
1794491389 51
1794491394 51
1794491399 46
1794491404 46
1794491409 46
1794491414 46
1794491419 46
1794491424 46
1794491429 46
1794491434 46
1794491439 46
1794491444 46
1794491449 46
1794491454 46
1794491459 46
1794491464 46
1794491469 51
1794491474 51
1794491479 51
```
</details>

---

