---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:06:21 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 897 |
| Sample Rate | 14.95/sec |
| Health Score | 934% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 87-91 cores)</summary>

```
1794592847 89
1794592852 89
1794592857 89
1794592862 89
1794592867 87
1794592872 87
1794592877 87
1794592882 87
1794592887 87
1794592892 87
1794592897 87
1794592902 89
1794592907 89
1794592912 87
1794592917 87
1794592922 87
1794592927 87
1794592932 87
1794592937 87
1794592942 87
```
</details>

---

