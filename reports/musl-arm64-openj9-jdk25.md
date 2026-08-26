---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-26 16:19:34 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 14 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (2 unique values: 32-44 cores)</summary>

```
1787775237 44
1787775242 44
1787775247 44
1787775252 44
1787775257 44
1787775262 44
1787775267 44
1787775272 44
1787775277 44
1787775282 44
1787775287 44
1787775292 44
1787775297 44
1787775302 44
1787775307 44
1787775312 32
1787775317 32
1787775322 32
1787775327 32
1787775332 32
```
</details>

---

