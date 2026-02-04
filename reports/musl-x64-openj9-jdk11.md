---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-04 07:50:53 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1020 |
| Sample Rate | 17.00/sec |
| Health Score | 1062% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1770208938 86
1770208943 86
1770208948 86
1770208953 86
1770208958 86
1770208963 86
1770208968 86
1770208973 86
1770208978 86
1770208983 86
1770208988 86
1770208993 86
1770208998 86
1770209003 86
1770209008 86
1770209013 91
1770209018 91
1770209023 91
1770209028 96
1770209033 96
```
</details>

---

