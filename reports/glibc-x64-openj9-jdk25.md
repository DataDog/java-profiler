---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-10 17:36:42 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 12 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 91-96 cores)</summary>

```
1770762517 96
1770762522 96
1770762527 96
1770762532 96
1770762537 96
1770762542 96
1770762547 96
1770762552 96
1770762557 96
1770762562 96
1770762567 96
1770762572 96
1770762577 96
1770762582 96
1770762587 94
1770762592 94
1770762597 94
1770762602 94
1770762607 92
1770762612 92
```
</details>

---

