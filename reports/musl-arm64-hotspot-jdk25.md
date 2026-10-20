---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 05:55:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 11 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 46-64 cores)</summary>

```
1792489889 46
1792489894 51
1792489899 51
1792489904 51
1792489909 51
1792489914 51
1792489919 51
1792489924 51
1792489929 51
1792489934 51
1792489939 51
1792489944 51
1792489949 51
1792489954 51
1792489959 51
1792489964 51
1792489969 51
1792489974 51
1792489979 51
1792489984 51
```
</details>

---

