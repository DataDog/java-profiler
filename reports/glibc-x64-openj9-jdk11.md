---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 09:51:41 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 991 |
| Sample Rate | 16.52/sec |
| Health Score | 1032% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793630793 32
1793630798 32
1793630803 32
1793630808 32
1793630813 32
1793630818 32
1793630823 32
1793630828 32
1793630833 32
1793630838 32
1793630843 32
1793630848 32
1793630853 32
1793630858 32
1793630863 32
1793630868 32
1793630873 32
1793630878 32
1793630883 32
1793630888 32
```
</details>

---

