---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:08:15 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 915 |
| Sample Rate | 15.25/sec |
| Health Score | 953% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (4 unique values: 79-82 cores)</summary>

```
1794567776 81
1794567781 81
1794567786 81
1794567791 81
1794567796 81
1794567801 81
1794567806 81
1794567811 81
1794567816 81
1794567821 81
1794567826 81
1794567831 79
1794567836 79
1794567841 79
1794567846 82
1794567851 82
1794567856 82
1794567861 80
1794567866 80
1794567871 80
```
</details>

---

