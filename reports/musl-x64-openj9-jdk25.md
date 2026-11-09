---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 16:19:02 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (4 unique values: 38-76 cores)</summary>

```
1794258881 54
1794258886 55
1794258891 55
1794258896 55
1794258901 55
1794258906 55
1794258911 55
1794258916 76
1794258921 76
1794258926 38
1794258931 38
1794258936 38
1794258941 38
1794258946 38
1794258951 38
1794258956 38
1794258961 38
1794258966 38
1794258971 38
1794258976 38
```
</details>

---

