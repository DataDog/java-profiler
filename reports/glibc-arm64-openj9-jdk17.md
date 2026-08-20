---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 12:31:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787243274 64
1787243279 64
1787243284 64
1787243289 64
1787243294 64
1787243299 64
1787243304 64
1787243309 64
1787243314 64
1787243319 64
1787243324 64
1787243329 64
1787243334 64
1787243339 64
1787243344 64
1787243349 64
1787243354 64
1787243359 64
1787243364 64
1787243369 64
```
</details>

---

