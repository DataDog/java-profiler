---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-26 16:19:33 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787775232 32
1787775237 32
1787775242 32
1787775247 32
1787775252 32
1787775257 32
1787775262 32
1787775267 32
1787775272 32
1787775277 32
1787775282 32
1787775287 32
1787775292 32
1787775297 32
1787775302 32
1787775307 32
1787775312 32
1787775317 32
1787775322 32
1787775327 32
```
</details>

---

