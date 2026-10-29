---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 13:19:43 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 12 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793294016 48
1793294021 48
1793294026 48
1793294031 48
1793294036 48
1793294041 48
1793294046 48
1793294051 48
1793294056 48
1793294061 48
1793294066 48
1793294071 48
1793294076 48
1793294081 48
1793294086 48
1793294091 48
1793294096 48
1793294101 48
1793294106 48
1793294111 48
```
</details>

---

