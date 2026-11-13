---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:28:31 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 55-58 cores)</summary>

```
1794572472 55
1794572477 55
1794572482 55
1794572487 55
1794572492 55
1794572497 55
1794572502 55
1794572507 55
1794572512 55
1794572517 55
1794572522 55
1794572527 55
1794572532 58
1794572537 58
1794572542 58
1794572547 58
1794572552 56
1794572557 56
1794572562 56
1794572567 56
```
</details>

---

