---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 10:31:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1790346387 36
1790346392 36
1790346397 36
1790346402 36
1790346407 36
1790346412 36
1790346417 36
1790346422 36
1790346427 36
1790346432 36
1790346437 36
1790346442 36
1790346447 36
1790346452 36
1790346457 36
1790346462 36
1790346467 36
1790346472 36
1790346477 36
1790346482 36
```
</details>

---

