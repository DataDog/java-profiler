---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-26 09:56:36 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 42-57 cores)</summary>

```
1779803445 57
1779803450 57
1779803455 57
1779803460 57
1779803465 57
1779803470 57
1779803475 57
1779803480 57
1779803485 57
1779803490 57
1779803495 57
1779803500 42
1779803505 42
1779803510 42
1779803515 42
1779803520 42
1779803525 42
1779803530 42
1779803535 42
1779803540 42
```
</details>

---

