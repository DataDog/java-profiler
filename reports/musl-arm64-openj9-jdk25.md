---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-22 09:38:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 9 |
| Allocations | 92 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 49-64 cores)</summary>

```
1792675912 54
1792675917 64
1792675922 64
1792675927 64
1792675932 64
1792675937 64
1792675942 64
1792675947 64
1792675952 64
1792675957 64
1792675962 64
1792675967 64
1792675972 64
1792675977 54
1792675982 54
1792675987 54
1792675992 54
1792675997 54
1792676002 54
1792676007 54
```
</details>

---

