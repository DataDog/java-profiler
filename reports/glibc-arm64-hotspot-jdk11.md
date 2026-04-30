---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 06:13:48 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 10 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777543674 64
1777543679 64
1777543684 64
1777543689 64
1777543694 64
1777543699 64
1777543704 64
1777543709 64
1777543714 64
1777543719 64
1777543724 64
1777543729 64
1777543734 64
1777543739 64
1777543744 64
1777543749 64
1777543754 64
1777543759 64
1777543764 64
1777543769 64
```
</details>

---

