---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 08:20:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 33-40 cores)</summary>

```
1792584844 33
1792584849 33
1792584854 33
1792584859 33
1792584864 33
1792584869 33
1792584874 33
1792584879 33
1792584884 33
1792584889 33
1792584894 33
1792584899 33
1792584904 33
1792584909 33
1792584914 33
1792584919 36
1792584924 36
1792584929 36
1792584934 36
1792584939 36
```
</details>

---

