---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-30 21:21:12 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 10 |
| Allocations | 111 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788138977 43
1788138982 43
1788138987 43
1788138992 43
1788138997 43
1788139002 43
1788139007 43
1788139012 43
1788139017 48
1788139022 48
1788139027 48
1788139032 48
1788139037 48
1788139042 48
1788139047 48
1788139052 48
1788139057 48
1788139062 48
1788139067 48
1788139072 48
```
</details>

---

