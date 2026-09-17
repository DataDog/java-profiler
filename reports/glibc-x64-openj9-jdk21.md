---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:53:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1789667218 30
1789667223 30
1789667228 30
1789667233 30
1789667238 30
1789667243 32
1789667248 32
1789667253 11
1789667258 11
1789667263 11
1789667268 11
1789667273 11
1789667278 11
1789667283 11
1789667288 11
1789667293 11
1789667298 11
1789667303 11
1789667308 11
1789667313 11
```
</details>

---

