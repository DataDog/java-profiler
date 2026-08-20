---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 06:18:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 895 |
| Sample Rate | 14.92/sec |
| Health Score | 932% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787220881 96
1787220886 96
1787220891 96
1787220896 96
1787220901 96
1787220906 94
1787220911 94
1787220916 94
1787220921 94
1787220926 94
1787220931 94
1787220936 94
1787220941 94
1787220946 94
1787220951 94
1787220956 94
1787220961 94
1787220966 94
1787220971 94
1787220976 94
```
</details>

---

