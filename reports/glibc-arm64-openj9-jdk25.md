---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 16:31:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786393569 48
1786393574 48
1786393579 48
1786393584 48
1786393589 48
1786393594 48
1786393599 48
1786393604 48
1786393609 48
1786393614 48
1786393619 53
1786393624 53
1786393629 53
1786393634 53
1786393639 53
1786393644 53
1786393649 53
1786393654 53
1786393659 53
1786393664 53
```
</details>

---

