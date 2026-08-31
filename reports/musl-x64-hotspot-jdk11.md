---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-31 06:40:03 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 763 |
| Sample Rate | 12.72/sec |
| Health Score | 795% |
| Threads | 11 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1788172493 81
1788172498 81
1788172503 81
1788172508 81
1788172513 81
1788172518 81
1788172523 81
1788172528 81
1788172533 81
1788172538 81
1788172543 81
1788172548 81
1788172553 81
1788172558 81
1788172563 81
1788172568 81
1788172573 81
1788172578 81
1788172583 81
1788172588 79
```
</details>

---

