---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-20 06:18:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 12 |
| Allocations | 166 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 6 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787220886 43
1787220891 43
1787220896 43
1787220901 43
1787220906 43
1787220911 48
1787220916 48
1787220921 48
1787220926 48
1787220931 48
1787220936 48
1787220941 48
1787220946 48
1787220951 48
1787220956 48
1787220961 48
1787220966 48
1787220971 48
1787220976 48
1787220981 48
```
</details>

---

