---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-02 11:44:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1788363439 48
1788363444 47
1788363449 47
1788363454 47
1788363459 47
1788363464 47
1788363469 47
1788363474 47
1788363479 47
1788363484 47
1788363489 47
1788363494 48
1788363499 48
1788363504 43
1788363509 43
1788363514 43
1788363519 43
1788363524 43
1788363530 43
1788363535 43
```
</details>

---

