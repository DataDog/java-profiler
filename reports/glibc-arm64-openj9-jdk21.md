---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 01:02:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 7 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 14 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1786942367 59
1786942372 59
1786942377 59
1786942382 59
1786942387 59
1786942392 59
1786942397 64
1786942402 64
1786942407 64
1786942412 64
1786942417 64
1786942422 64
1786942427 64
1786942432 64
1786942437 64
1786942442 64
1786942447 64
1786942452 64
1786942457 64
1786942462 64
```
</details>

---

