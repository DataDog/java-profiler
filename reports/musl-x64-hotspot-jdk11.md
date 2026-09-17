---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 13:54:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 8 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 17-32 cores)</summary>

```
1789667258 17
1789667263 32
1789667268 32
1789667273 32
1789667278 32
1789667283 32
1789667288 32
1789667293 32
1789667298 32
1789667303 32
1789667308 32
1789667313 32
1789667318 32
1789667323 32
1789667328 32
1789667333 32
1789667338 32
1789667343 32
1789667348 32
1789667353 32
```
</details>

---

