---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:54:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1789667218 64
1789667223 64
1789667228 64
1789667233 64
1789667238 64
1789667243 64
1789667248 64
1789667253 64
1789667258 64
1789667263 62
1789667268 62
1789667273 62
1789667278 62
1789667283 62
1789667288 62
1789667293 62
1789667298 62
1789667303 60
1789667308 60
1789667313 60
```
</details>

---

