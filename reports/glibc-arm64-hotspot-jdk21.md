---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-19 22:04:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 301 |
| Sample Rate | 5.02/sec |
| Health Score | 314% |
| Threads | 15 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787191218 43
1787191223 43
1787191228 43
1787191233 43
1787191238 43
1787191243 43
1787191248 43
1787191253 43
1787191258 43
1787191263 43
1787191268 43
1787191273 43
1787191278 43
1787191283 43
1787191288 43
1787191293 43
1787191298 48
1787191303 48
1787191308 48
1787191313 48
```
</details>

---

