---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-09 21:22:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 91-94 cores)</summary>

```
1786324659 94
1786324664 94
1786324669 94
1786324674 94
1786324679 94
1786324684 94
1786324689 91
1786324694 91
1786324699 91
1786324704 91
1786324709 91
1786324714 91
1786324719 91
1786324724 91
1786324729 91
1786324734 91
1786324739 91
1786324744 91
1786324749 91
1786324754 91
```
</details>

---

