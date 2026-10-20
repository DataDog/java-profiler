---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 05:55:26 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1049 |
| Sample Rate | 17.48/sec |
| Health Score | 1092% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1792489891 48
1792489896 43
1792489901 43
1792489906 43
1792489911 43
1792489916 43
1792489921 43
1792489926 43
1792489931 43
1792489936 38
1792489941 38
1792489946 38
1792489951 38
1792489956 43
1792489961 43
1792489966 43
1792489971 43
1792489976 38
1792489981 38
1792489986 38
```
</details>

---

