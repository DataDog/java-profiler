---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 13:17:10 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1062 |
| Sample Rate | 17.70/sec |
| Health Score | 1106% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 61-78 cores)</summary>

```
1778173870 61
1778173875 61
1778173880 61
1778173885 61
1778173890 61
1778173895 61
1778173900 61
1778173905 61
1778173910 61
1778173915 61
1778173920 76
1778173925 76
1778173930 76
1778173935 78
1778173940 78
1778173945 76
1778173950 76
1778173955 76
1778173960 76
1778173965 76
```
</details>

---

