---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-28 01:05:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 11 |
| Allocations | 151 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793163674 43
1793163679 43
1793163684 43
1793163689 43
1793163694 43
1793163699 43
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
1793163764 43
1793163769 43
```
</details>

---

