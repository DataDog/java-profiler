---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-13 04:00:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 32-34 cores)</summary>

```
1786607762 33
1786607767 33
1786607773 33
1786607778 33
1786607783 33
1786607788 33
1786607793 33
1786607798 34
1786607803 34
1786607808 34
1786607813 34
1786607818 34
1786607823 34
1786607828 34
1786607833 34
1786607838 34
1786607843 34
1786607848 34
1786607853 34
1786607858 34
```
</details>

---

