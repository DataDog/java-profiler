---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 08:29:47 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1016 |
| Sample Rate | 16.93/sec |
| Health Score | 1058% |
| Threads | 10 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 52-57 cores)</summary>

```
1778588583 52
1778588588 52
1778588593 52
1778588598 52
1778588603 57
1778588608 57
1778588613 57
1778588618 57
1778588623 57
1778588628 57
1778588633 57
1778588638 57
1778588643 57
1778588648 57
1778588653 57
1778588658 57
1778588663 57
1778588668 57
1778588673 57
1778588678 57
```
</details>

---

