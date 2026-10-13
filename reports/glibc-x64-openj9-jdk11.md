---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 10:31:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 8 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 71-77 cores)</summary>

```
1791901632 77
1791901637 77
1791901642 77
1791901647 77
1791901652 77
1791901657 77
1791901662 77
1791901667 77
1791901672 77
1791901677 77
1791901682 77
1791901687 75
1791901692 75
1791901697 75
1791901702 75
1791901707 75
1791901712 75
1791901717 75
1791901722 75
1791901727 75
```
</details>

---

