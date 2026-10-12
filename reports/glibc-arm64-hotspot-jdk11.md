---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 03:21:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 47 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791789376 40
1791789381 40
1791789386 40
1791789391 40
1791789396 40
1791789401 40
1791789406 40
1791789411 40
1791789416 40
1791789421 40
1791789426 40
1791789431 40
1791789436 40
1791789441 40
1791789446 40
1791789451 40
1791789456 40
1791789461 40
1791789466 40
1791789471 40
```
</details>

---

