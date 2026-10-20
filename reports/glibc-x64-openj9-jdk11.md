---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 17:52:26 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 27-32 cores)</summary>

```
1792532735 27
1792532740 27
1792532745 27
1792532750 27
1792532755 27
1792532760 27
1792532765 27
1792532770 29
1792532775 29
1792532780 29
1792532785 29
1792532790 29
1792532795 32
1792532800 32
1792532805 32
1792532810 32
1792532815 32
1792532820 32
1792532825 32
1792532830 32
```
</details>

---

