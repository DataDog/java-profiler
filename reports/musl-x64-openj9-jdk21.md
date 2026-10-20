---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 13:18:14 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 866 |
| Sample Rate | 14.43/sec |
| Health Score | 902% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (4 unique values: 80-90 cores)</summary>

```
1792516385 90
1792516390 90
1792516395 90
1792516400 88
1792516405 88
1792516410 88
1792516415 88
1792516420 88
1792516425 88
1792516430 88
1792516435 88
1792516440 88
1792516445 88
1792516450 80
1792516455 80
1792516460 82
1792516465 82
1792516470 82
1792516475 82
1792516480 82
```
</details>

---

