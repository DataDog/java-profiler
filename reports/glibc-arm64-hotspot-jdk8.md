---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 05:46:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 31-38 cores)</summary>

```
1795084977 38
1795084982 38
1795084987 31
1795084992 31
1795084997 31
1795085002 31
1795085007 31
1795085012 31
1795085017 31
1795085022 31
1795085027 31
1795085032 31
1795085037 31
1795085042 31
1795085047 31
1795085052 31
1795085057 33
1795085062 33
1795085067 33
1795085072 33
```
</details>

---

