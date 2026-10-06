---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 06:41:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 53-64 cores)</summary>

```
1791282966 53
1791282971 53
1791282976 53
1791282981 53
1791282986 53
1791282991 53
1791282996 53
1791283001 53
1791283006 53
1791283011 64
1791283016 64
1791283021 64
1791283026 64
1791283031 64
1791283036 64
1791283041 64
1791283046 64
1791283051 64
1791283056 64
1791283061 64
```
</details>

---

