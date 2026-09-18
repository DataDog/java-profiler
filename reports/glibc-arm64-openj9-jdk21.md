---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:34:33 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1789716467 44
1789716472 44
1789716477 44
1789716482 44
1789716487 44
1789716492 44
1789716497 44
1789716502 44
1789716507 44
1789716512 44
1789716517 44
1789716522 44
1789716527 44
1789716532 44
1789716537 44
1789716542 44
1789716547 44
1789716552 44
1789716557 44
1789716562 44
```
</details>

---

