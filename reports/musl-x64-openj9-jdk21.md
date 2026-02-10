---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-10 17:36:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 13 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 76-81 cores)</summary>

```
1770762507 76
1770762512 76
1770762517 76
1770762522 76
1770762527 76
1770762532 81
1770762537 81
1770762542 81
1770762547 81
1770762552 81
1770762557 81
1770762562 81
1770762567 81
1770762572 81
1770762577 81
1770762582 81
1770762587 81
1770762592 81
1770762597 81
1770762602 81
```
</details>

---

