---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-24 17:04:01 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 8 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1777064251 32
1777064256 32
1777064261 32
1777064266 32
1777064271 32
1777064276 32
1777064281 32
1777064286 32
1777064291 32
1777064296 32
1777064301 32
1777064306 32
1777064311 32
1777064316 32
1777064321 32
1777064326 32
1777064331 32
1777064336 32
1777064341 32
1777064346 32
```
</details>

---

