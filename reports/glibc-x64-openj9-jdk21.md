---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 12:01:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793897781 30
1793897786 30
1793897791 30
1793897796 30
1793897801 30
1793897806 30
1793897811 30
1793897816 30
1793897821 30
1793897826 30
1793897831 30
1793897836 30
1793897841 30
1793897846 30
1793897851 30
1793897856 30
1793897861 30
1793897866 30
1793897871 30
1793897876 30
```
</details>

---

