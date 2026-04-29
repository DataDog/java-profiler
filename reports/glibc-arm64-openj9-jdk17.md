---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-29 10:11:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777471571 59
1777471576 59
1777471581 59
1777471586 59
1777471591 59
1777471596 59
1777471601 59
1777471606 59
1777471611 59
1777471616 59
1777471621 59
1777471626 59
1777471631 59
1777471636 59
1777471641 59
1777471646 59
1777471651 59
1777471656 59
1777471661 59
1777471666 64
```
</details>

---

