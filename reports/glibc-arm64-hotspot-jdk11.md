---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 12:29:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 963 |
| Sample Rate | 16.05/sec |
| Health Score | 1003% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 25-51 cores)</summary>

```
1792513477 25
1792513482 25
1792513487 45
1792513492 45
1792513497 45
1792513502 45
1792513507 45
1792513512 45
1792513517 45
1792513522 45
1792513527 45
1792513532 51
1792513537 51
1792513542 51
1792513547 51
1792513552 51
1792513557 51
1792513562 51
1792513567 51
1792513572 51
```
</details>

---

