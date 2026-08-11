---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 09:33:17 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 87-92 cores)</summary>

```
1786454949 89
1786454954 89
1786454959 89
1786454964 89
1786454969 90
1786454974 90
1786454979 90
1786454984 90
1786454989 92
1786454994 92
1786454999 92
1786455004 92
1786455009 92
1786455014 92
1786455019 92
1786455024 92
1786455029 92
1786455034 92
1786455039 92
1786455044 92
```
</details>

---

