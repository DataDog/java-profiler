---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-25 21:28:10 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 67-88 cores)</summary>

```
1792977813 75
1792977818 75
1792977823 75
1792977828 75
1792977833 75
1792977838 75
1792977843 75
1792977848 75
1792977853 67
1792977858 67
1792977863 67
1792977868 67
1792977873 67
1792977878 67
1792977883 67
1792977888 88
1792977893 88
1792977898 88
1792977903 69
1792977908 69
```
</details>

---

