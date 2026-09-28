---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 15:02:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1790621847 40
1790621852 40
1790621857 40
1790621862 40
1790621867 40
1790621872 40
1790621877 40
1790621882 40
1790621887 40
1790621892 40
1790621897 40
1790621902 35
1790621907 35
1790621912 35
1790621917 35
1790621922 35
1790621927 35
1790621932 35
1790621937 35
1790621942 35
```
</details>

---

