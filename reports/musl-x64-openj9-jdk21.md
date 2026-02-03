---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 11:55:44 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 12 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 72-91 cores)</summary>

```
1770137478 72
1770137483 72
1770137488 72
1770137493 72
1770137498 72
1770137503 72
1770137508 72
1770137513 77
1770137518 77
1770137523 77
1770137528 77
1770137533 77
1770137538 77
1770137543 77
1770137549 77
1770137554 77
1770137559 77
1770137564 77
1770137569 77
1770137574 77
```
</details>

---

