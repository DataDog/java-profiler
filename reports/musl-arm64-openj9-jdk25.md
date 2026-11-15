---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 18:26:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794784924 48
1794784929 48
1794784934 48
1794784939 48
1794784944 48
1794784949 48
1794784954 48
1794784959 48
1794784964 48
1794784969 48
1794784974 48
1794784979 48
1794784984 48
1794784989 48
1794784994 48
1794784999 48
1794785004 48
1794785009 48
1794785014 48
1794785019 48
```
</details>

---

