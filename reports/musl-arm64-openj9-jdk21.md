---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 05:55:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 10 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 12 |
| Allocations | 113 |

<details>
<summary>CPU Timeline (4 unique values: 26-35 cores)</summary>

```
1791539372 26
1791539377 26
1791539382 33
1791539388 33
1791539393 33
1791539398 33
1791539403 35
1791539408 35
1791539413 34
1791539418 34
1791539423 34
1791539428 34
1791539433 34
1791539438 34
1791539443 34
1791539448 34
1791539453 34
1791539458 34
1791539463 34
1791539468 35
```
</details>

---

