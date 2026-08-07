---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 05:50:46 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 15 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1786095976 32
1786095981 32
1786095986 32
1786095991 32
1786095996 32
1786096001 32
1786096006 32
1786096011 32
1786096016 32
1786096021 31
1786096026 31
1786096031 31
1786096036 31
1786096041 31
1786096046 31
1786096051 31
1786096056 31
1786096061 31
1786096066 31
1786096071 31
```
</details>

---

