---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 00:00:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 810 |
| Sample Rate | 13.50/sec |
| Health Score | 844% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 8-25 cores)</summary>

```
1795409781 25
1795409786 8
1795409791 8
1795409796 8
1795409801 8
1795409806 8
1795409811 8
1795409816 8
1795409821 8
1795409826 8
1795409831 8
1795409836 8
1795409841 8
1795409846 8
1795409851 8
1795409856 8
1795409861 8
1795409866 8
1795409871 8
1795409876 8
```
</details>

---

