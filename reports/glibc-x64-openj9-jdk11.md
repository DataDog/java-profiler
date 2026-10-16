---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-16 05:17:22 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 893 |
| Sample Rate | 14.88/sec |
| Health Score | 930% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 73-78 cores)</summary>

```
1792141940 75
1792141945 78
1792141950 78
1792141955 78
1792141960 78
1792141965 78
1792141970 78
1792141975 78
1792141980 78
1792141985 78
1792141990 76
1792141995 76
1792142000 76
1792142005 76
1792142010 76
1792142015 76
1792142020 76
1792142025 76
1792142030 76
1792142035 76
```
</details>

---

