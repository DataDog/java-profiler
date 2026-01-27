---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-01-27 09:51:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 18.43/sec |
| Health Score | 1152% |
| Threads | 10 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 28.13/sec |
| Health Score | 1758% |
| Threads | 13 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (5 unique values: 56-73 cores)</summary>

```
1769524869 57
1769524874 57
1769524879 56
1769524884 56
1769524889 56
1769524894 56
1769524899 73
1769524904 73
1769524909 73
1769524914 73
1769524919 68
1769524924 68
1769524929 68
1769524934 69
1769524939 69
1769524944 69
1769524949 69
1769524954 69
1769524959 69
1769524965 69
```
</details>

---

