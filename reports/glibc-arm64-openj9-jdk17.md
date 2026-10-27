---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-27 11:01:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793112924 48
1793112929 48
1793112934 48
1793112939 48
1793112944 48
1793112949 48
1793112954 48
1793112959 48
1793112964 48
1793112969 48
1793112974 48
1793112979 48
1793112984 48
1793112989 48
1793112994 48
1793112999 48
1793113004 48
1793113009 48
1793113014 48
1793113019 48
```
</details>

---

