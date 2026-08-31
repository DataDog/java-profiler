---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-31 06:40:04 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 80-88 cores)</summary>

```
1788172493 80
1788172498 80
1788172503 80
1788172508 88
1788172513 88
1788172518 88
1788172523 88
1788172528 88
1788172533 88
1788172538 88
1788172543 88
1788172548 88
1788172553 88
1788172558 88
1788172563 88
1788172568 88
1788172573 88
1788172578 88
1788172583 88
1788172588 88
```
</details>

---

