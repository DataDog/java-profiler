---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-07 05:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 15 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 10-14 cores)</summary>

```
1786095971 10
1786095976 10
1786095981 10
1786095986 10
1786095991 10
1786095996 10
1786096001 10
1786096006 14
1786096011 14
1786096016 14
1786096021 14
1786096026 14
1786096031 14
1786096036 14
1786096041 14
1786096046 14
1786096051 14
1786096056 14
1786096061 14
1786096066 14
```
</details>

---

