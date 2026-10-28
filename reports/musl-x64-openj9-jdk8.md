---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:12:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 23-30 cores)</summary>

```
1793185766 28
1793185771 28
1793185776 28
1793185781 28
1793185786 28
1793185791 28
1793185796 30
1793185801 30
1793185806 28
1793185811 28
1793185816 28
1793185821 28
1793185826 28
1793185831 28
1793185836 28
1793185841 28
1793185846 28
1793185851 30
1793185856 30
1793185861 28
```
</details>

---

