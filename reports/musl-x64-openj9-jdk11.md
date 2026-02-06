---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-06 09:56:51 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (2 unique values: 86-96 cores)</summary>

```
1770389494 96
1770389499 96
1770389504 96
1770389509 96
1770389514 96
1770389519 96
1770389524 96
1770389529 96
1770389534 96
1770389539 86
1770389544 86
1770389549 86
1770389554 86
1770389559 86
1770389564 86
1770389569 86
1770389574 86
1770389579 86
1770389584 86
1770389589 86
```
</details>

---

