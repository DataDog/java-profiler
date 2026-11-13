---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:00:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 9 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1794581682 46
1794581687 46
1794581692 51
1794581697 51
1794581702 51
1794581707 51
1794581712 51
1794581717 51
1794581722 51
1794581727 51
1794581732 51
1794581737 51
1794581742 51
1794581747 51
1794581752 51
1794581757 51
1794581762 51
1794581767 64
1794581772 64
1794581777 64
```
</details>

---

