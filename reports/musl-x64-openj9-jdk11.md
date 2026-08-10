---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-10 06:45:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 32-55 cores)</summary>

```
1786358477 53
1786358482 55
1786358487 55
1786358492 55
1786358497 55
1786358502 55
1786358507 55
1786358512 55
1786358517 55
1786358522 55
1786358527 55
1786358532 55
1786358537 35
1786358542 35
1786358547 32
1786358552 32
1786358557 32
1786358562 32
1786358567 32
1786358572 32
```
</details>

---

