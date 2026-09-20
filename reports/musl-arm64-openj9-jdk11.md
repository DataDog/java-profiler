---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-20 05:46:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 11 |
| Allocations | 189 |

<details>
<summary>CPU Timeline (2 unique values: 34-44 cores)</summary>

```
1789897343 44
1789897348 44
1789897353 44
1789897358 44
1789897363 44
1789897368 44
1789897373 44
1789897378 44
1789897383 44
1789897388 44
1789897393 34
1789897398 34
1789897403 34
1789897408 34
1789897413 34
1789897418 34
1789897423 34
1789897428 34
1789897433 34
1789897439 34
```
</details>

---

