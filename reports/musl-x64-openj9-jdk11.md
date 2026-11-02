---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 13:47:26 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 569 |

<details>
<summary>CPU Timeline (2 unique values: 58-59 cores)</summary>

```
1793644960 59
1793644965 59
1793644970 59
1793644975 59
1793644980 59
1793644985 59
1793644990 59
1793644995 59
1793645000 59
1793645005 59
1793645010 59
1793645015 59
1793645020 59
1793645026 59
1793645031 58
1793645036 58
1793645041 58
1793645046 58
1793645051 58
1793645056 58
```
</details>

---

