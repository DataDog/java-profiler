---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 12:31:52 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 12 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787243223 34
1787243228 34
1787243233 34
1787243238 34
1787243243 34
1787243248 34
1787243253 34
1787243258 34
1787243263 34
1787243268 34
1787243273 29
1787243278 29
1787243283 29
1787243288 29
1787243293 29
1787243298 29
1787243303 29
1787243308 29
1787243313 29
1787243318 29
```
</details>

---

