---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 08:21:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 24-26 cores)</summary>

```
1795698996 24
1795699001 24
1795699006 24
1795699011 26
1795699016 26
1795699021 26
1795699026 26
1795699031 26
1795699036 26
1795699041 26
1795699046 26
1795699051 26
1795699056 26
1795699061 26
1795699066 26
1795699071 26
1795699076 26
1795699081 26
1795699086 26
1795699091 26
```
</details>

---

