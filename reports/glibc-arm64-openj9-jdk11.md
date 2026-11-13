---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794569554 48
1794569559 48
1794569564 48
1794569569 48
1794569574 48
1794569579 48
1794569584 48
1794569589 48
1794569594 48
1794569599 48
1794569604 48
1794569609 48
1794569614 48
1794569619 48
1794569624 48
1794569629 48
1794569634 48
1794569639 48
1794569644 48
1794569649 48
```
</details>

---

