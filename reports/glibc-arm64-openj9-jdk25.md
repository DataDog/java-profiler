---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 18:48:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 13 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794267832 31
1794267837 31
1794267842 31
1794267847 31
1794267852 31
1794267857 31
1794267862 31
1794267867 31
1794267872 31
1794267877 31
1794267882 36
1794267887 36
1794267892 36
1794267897 36
1794267902 36
1794267907 36
1794267912 36
1794267917 36
1794267922 36
1794267927 36
```
</details>

---

