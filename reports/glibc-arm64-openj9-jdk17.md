---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 05:55:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1792489881 48
1792489886 48
1792489891 48
1792489896 48
1792489901 43
1792489906 43
1792489911 43
1792489916 43
1792489921 43
1792489926 43
1792489931 43
1792489936 43
1792489941 43
1792489946 43
1792489951 43
1792489956 48
1792489962 48
1792489967 47
1792489972 47
1792489977 47
```
</details>

---

