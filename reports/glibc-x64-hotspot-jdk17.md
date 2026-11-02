---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 13:05:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 10 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (4 unique values: 34-55 cores)</summary>

```
1793642472 51
1793642477 51
1793642482 51
1793642487 51
1793642492 51
1793642497 53
1793642502 53
1793642507 53
1793642512 55
1793642517 55
1793642522 34
1793642527 34
1793642532 34
1793642537 34
1793642542 34
1793642547 34
1793642552 34
1793642557 34
1793642562 34
1793642567 34
```
</details>

---

