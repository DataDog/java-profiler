---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 05:15:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 28-59 cores)</summary>

```
1795514961 41
1795514966 57
1795514971 57
1795514976 58
1795514981 58
1795514986 58
1795514991 58
1795514996 58
1795515001 59
1795515006 59
1795515011 59
1795515016 59
1795515021 59
1795515026 59
1795515031 59
1795515036 59
1795515041 59
1795515046 59
1795515051 59
1795515056 59
```
</details>

---

