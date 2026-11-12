---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:09:39 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1794495887 87
1794495892 87
1794495897 87
1794495902 87
1794495907 87
1794495913 91
1794495918 91
1794495923 91
1794495928 91
1794495933 89
1794495938 89
1794495943 89
1794495948 89
1794495953 89
1794495958 89
1794495963 89
1794495968 89
1794495973 89
1794495978 89
1794495983 89
```
</details>

---

