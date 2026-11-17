---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 13:29:12 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 11 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (5 unique values: 67-90 cores)</summary>

```
1794939900 80
1794939905 80
1794939910 80
1794939915 80
1794939920 80
1794939925 80
1794939930 82
1794939935 82
1794939940 82
1794939945 82
1794939950 82
1794939955 82
1794939960 82
1794939965 82
1794939970 82
1794939975 90
1794939980 90
1794939985 90
1794939990 90
1794939995 67
```
</details>

---

