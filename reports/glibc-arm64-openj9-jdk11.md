---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 14:00:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 9 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (4 unique values: 44-64 cores)</summary>

```
1792518939 46
1792518944 46
1792518949 46
1792518954 46
1792518959 51
1792518964 51
1792518969 51
1792518974 51
1792518979 51
1792518984 51
1792518989 51
1792518994 51
1792518999 51
1792519004 51
1792519009 51
1792519014 51
1792519019 51
1792519024 51
1792519029 51
1792519034 51
```
</details>

---

