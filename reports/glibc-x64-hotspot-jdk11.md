---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 05:39:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 9 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1795170689 63
1795170694 63
1795170699 63
1795170704 63
1795170709 63
1795170714 63
1795170719 63
1795170724 63
1795170729 63
1795170734 63
1795170739 63
1795170744 61
1795170749 61
1795170754 61
1795170759 61
1795170764 61
1795170769 61
1795170774 61
1795170779 61
1795170784 61
```
</details>

---

