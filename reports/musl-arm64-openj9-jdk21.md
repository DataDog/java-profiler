---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:38:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 12 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 11 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792675922 48
1792675927 48
1792675932 48
1792675937 48
1792675942 48
1792675947 48
1792675952 48
1792675957 48
1792675962 48
1792675967 48
1792675972 48
1792675977 48
1792675982 48
1792675987 48
1792675992 48
1792675997 48
1792676002 48
1792676007 48
1792676012 48
1792676017 48
```
</details>

---

