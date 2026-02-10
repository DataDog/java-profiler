---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-10 17:36:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (3 unique values: 19-23 cores)</summary>

```
1770762522 23
1770762527 23
1770762532 23
1770762537 23
1770762542 23
1770762547 23
1770762552 23
1770762557 23
1770762562 23
1770762567 23
1770762572 23
1770762577 23
1770762582 19
1770762587 19
1770762592 19
1770762597 19
1770762602 19
1770762607 19
1770762612 19
1770762617 19
```
</details>

---

