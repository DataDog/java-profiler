---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:28:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 58-70 cores)</summary>

```
1795706631 68
1795706636 68
1795706641 68
1795706646 68
1795706651 68
1795706656 68
1795706661 68
1795706666 68
1795706671 68
1795706676 68
1795706681 68
1795706686 70
1795706691 70
1795706696 58
1795706701 58
1795706706 58
1795706711 58
1795706716 58
1795706721 58
1795706726 58
```
</details>

---

