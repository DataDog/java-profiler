---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 10:05:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 11 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (4 unique values: 41-48 cores)</summary>

```
1787234392 48
1787234397 48
1787234402 48
1787234407 48
1787234412 48
1787234417 48
1787234422 43
1787234427 43
1787234432 43
1787234437 43
1787234442 43
1787234447 43
1787234452 41
1787234457 41
1787234462 46
1787234467 46
1787234472 46
1787234477 46
1787234482 46
1787234487 46
```
</details>

---

