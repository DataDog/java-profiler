---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 01:05:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 15 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793163673 43
1793163678 43
1793163683 43
1793163688 43
1793163693 43
1793163698 43
1793163704 48
1793163709 48
1793163714 48
1793163719 48
1793163724 48
1793163729 48
1793163734 48
1793163739 48
1793163744 48
1793163749 48
1793163754 48
1793163759 48
1793163764 48
1793163769 43
```
</details>

---

