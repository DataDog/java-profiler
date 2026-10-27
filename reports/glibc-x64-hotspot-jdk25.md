---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 13:59:53 EDT

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
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 77-96 cores)</summary>

```
1793123684 94
1793123689 94
1793123694 94
1793123699 94
1793123704 94
1793123709 94
1793123714 96
1793123719 96
1793123724 77
1793123729 77
1793123734 77
1793123739 77
1793123744 77
1793123749 77
1793123754 77
1793123759 77
1793123764 77
1793123769 77
1793123774 77
1793123779 77
```
</details>

---

