---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 03:38:43 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 8 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1777275266 64
1777275271 64
1777275276 64
1777275281 64
1777275286 64
1777275291 64
1777275296 64
1777275301 64
1777275306 64
1777275311 64
1777275316 64
1777275321 64
1777275326 64
1777275331 64
1777275336 64
1777275341 64
1777275347 64
1777275352 64
1777275357 64
1777275362 64
```
</details>

---

