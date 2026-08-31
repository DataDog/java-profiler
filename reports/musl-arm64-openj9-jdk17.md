---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-30 21:21:12 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 10 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788138982 43
1788138987 43
1788138992 43
1788138997 43
1788139002 43
1788139007 43
1788139012 43
1788139017 43
1788139022 43
1788139027 43
1788139032 43
1788139037 43
1788139042 43
1788139047 48
1788139052 48
1788139057 48
1788139062 48
1788139067 48
1788139072 48
1788139077 48
```
</details>

---

