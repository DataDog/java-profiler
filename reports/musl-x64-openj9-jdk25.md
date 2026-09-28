---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 14:12:57 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 29-30 cores)</summary>

```
1790618966 30
1790618971 30
1790618976 30
1790618981 30
1790618986 30
1790618991 30
1790618996 29
1790619001 29
1790619006 29
1790619011 29
1790619016 29
1790619021 29
1790619026 29
1790619031 29
1790619036 29
1790619041 29
1790619046 29
1790619051 29
1790619056 30
1790619061 30
```
</details>

---

