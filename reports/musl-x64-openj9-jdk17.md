---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 13:39:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1003 |
| Sample Rate | 16.72/sec |
| Health Score | 1045% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 86-90 cores)</summary>

```
1773250206 90
1773250211 90
1773250216 90
1773250221 90
1773250226 90
1773250231 90
1773250236 90
1773250241 86
1773250246 86
1773250251 86
1773250256 86
1773250261 86
1773250266 86
1773250271 86
1773250276 86
1773250281 86
1773250286 86
1773250291 86
1773250296 86
1773250301 86
```
</details>

---

