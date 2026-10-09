---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 05:55:08 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1791539352 40
1791539357 40
1791539362 40
1791539367 40
1791539372 40
1791539377 40
1791539382 40
1791539387 40
1791539392 40
1791539397 40
1791539402 40
1791539407 40
1791539412 40
1791539418 40
1791539423 40
1791539428 40
1791539433 40
1791539438 40
1791539443 40
1791539448 40
```
</details>

---

