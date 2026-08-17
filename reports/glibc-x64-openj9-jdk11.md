---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:10:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 82-96 cores)</summary>

```
1786971574 96
1786971579 96
1786971584 84
1786971589 84
1786971594 84
1786971599 84
1786971604 84
1786971609 84
1786971614 84
1786971619 84
1786971624 82
1786971629 82
1786971634 82
1786971639 82
1786971644 82
1786971649 82
1786971654 82
1786971659 82
1786971664 82
1786971669 82
```
</details>

---

