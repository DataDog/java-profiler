---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 11:03:30 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1787669818 91
1787669823 91
1787669828 91
1787669833 91
1787669838 91
1787669843 96
1787669848 96
1787669853 94
1787669858 94
1787669863 94
1787669868 94
1787669873 94
1787669878 94
1787669883 94
1787669888 94
1787669893 96
1787669898 96
1787669903 96
1787669908 96
1787669913 96
```
</details>

---

