---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-21 16:06:32 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 12 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 8 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792612866 46
1792612871 46
1792612876 46
1792612881 46
1792612886 46
1792612891 46
1792612896 46
1792612901 46
1792612906 46
1792612911 46
1792612916 51
1792612921 51
1792612926 51
1792612931 51
1792612936 51
1792612941 51
1792612946 51
1792612951 51
1792612956 51
1792612961 51
```
</details>

---

