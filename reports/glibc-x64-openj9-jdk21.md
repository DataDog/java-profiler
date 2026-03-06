---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-06 04:52:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 8 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 9 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 16-28 cores)</summary>

```
1772790339 20
1772790344 20
1772790349 20
1772790354 20
1772790359 20
1772790364 20
1772790369 20
1772790374 20
1772790379 20
1772790384 20
1772790389 20
1772790394 20
1772790399 20
1772790404 20
1772790409 16
1772790414 16
1772790419 16
1772790424 16
1772790429 16
1772790434 25
```
</details>

---

