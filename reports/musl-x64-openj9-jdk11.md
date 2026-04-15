---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 11:14:28 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 967 |
| Sample Rate | 16.12/sec |
| Health Score | 1007% |
| Threads | 12 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (6 unique values: 76-85 cores)</summary>

```
1776265786 84
1776265791 84
1776265796 84
1776265801 82
1776265806 82
1776265811 84
1776265816 84
1776265821 84
1776265826 84
1776265831 84
1776265836 85
1776265841 85
1776265846 85
1776265851 83
1776265856 83
1776265861 83
1776265866 83
1776265871 78
1776265876 78
1776265881 78
```
</details>

---

