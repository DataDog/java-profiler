---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 10:58:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (4 unique values: 34-48 cores)</summary>

```
1787151243 48
1787151248 48
1787151253 48
1787151258 44
1787151263 44
1787151268 44
1787151273 44
1787151278 44
1787151283 44
1787151288 44
1787151293 44
1787151298 39
1787151303 39
1787151308 34
1787151313 34
1787151318 34
1787151323 34
1787151328 34
1787151333 34
1787151338 34
```
</details>

---

