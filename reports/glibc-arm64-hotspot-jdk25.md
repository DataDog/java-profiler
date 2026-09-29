---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 06:07:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 9 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (1 unique values: 25-25 cores)</summary>

```
1790675871 25
1790675876 25
1790675881 25
1790675886 25
1790675891 25
1790675896 25
1790675901 25
1790675906 25
1790675911 25
1790675916 25
1790675921 25
1790675926 25
1790675931 25
1790675936 25
1790675941 25
1790675946 25
1790675951 25
1790675956 25
1790675961 25
1790675966 25
```
</details>

---

