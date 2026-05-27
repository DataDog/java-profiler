---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-27 06:39:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 949 |
| Sample Rate | 15.82/sec |
| Health Score | 989% |
| Threads | 9 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 35-48 cores)</summary>

```
1779878208 48
1779878213 48
1779878218 48
1779878223 48
1779878228 48
1779878233 48
1779878238 48
1779878243 48
1779878248 48
1779878253 48
1779878258 48
1779878263 48
1779878268 48
1779878273 48
1779878278 48
1779878283 48
1779878288 48
1779878293 48
1779878298 48
1779878303 48
```
</details>

---

