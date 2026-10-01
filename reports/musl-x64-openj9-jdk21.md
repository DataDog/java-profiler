---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-01 00:59:51 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1790830458 25
1790830463 25
1790830468 25
1790830473 25
1790830478 25
1790830483 25
1790830488 25
1790830493 27
1790830498 27
1790830503 27
1790830508 27
1790830513 27
1790830518 27
1790830523 27
1790830528 27
1790830533 27
1790830538 27
1790830543 27
1790830548 27
1790830553 27
```
</details>

---

