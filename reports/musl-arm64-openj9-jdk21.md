---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-01 23:46:57 EST

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 9-9 cores)</summary>

```
1793594478 9
1793594483 9
1793594488 9
1793594493 9
1793594498 9
1793594503 9
1793594508 9
1793594513 9
1793594518 9
1793594523 9
1793594528 9
1793594533 9
1793594538 9
1793594543 9
1793594548 9
1793594553 9
1793594558 9
1793594563 9
1793594568 9
1793594573 9
```
</details>

---

