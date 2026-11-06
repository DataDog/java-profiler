---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-06 07:08:29 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 11 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 35-37 cores)</summary>

```
1793966613 37
1793966618 37
1793966623 37
1793966628 37
1793966633 37
1793966638 37
1793966643 37
1793966648 37
1793966653 37
1793966658 35
1793966663 35
1793966668 36
1793966674 36
1793966679 36
1793966684 36
1793966689 36
1793966694 36
1793966699 36
1793966704 36
1793966709 36
```
</details>

---

