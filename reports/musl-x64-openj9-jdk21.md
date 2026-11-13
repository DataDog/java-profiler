---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:00:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (4 unique values: 80-96 cores)</summary>

```
1794581672 80
1794581677 80
1794581682 80
1794581687 80
1794581692 80
1794581697 80
1794581702 80
1794581707 80
1794581712 80
1794581717 80
1794581722 80
1794581727 80
1794581732 80
1794581737 80
1794581742 80
1794581747 80
1794581752 84
1794581757 84
1794581762 84
1794581767 84
```
</details>

---

