---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:32:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
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
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 331 |
| Sample Rate | 5.52/sec |
| Health Score | 345% |
| Threads | 11 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793615292 48
1793615297 48
1793615302 48
1793615307 48
1793615312 48
1793615318 48
1793615323 48
1793615328 48
1793615333 48
1793615338 48
1793615343 48
1793615348 48
1793615353 48
1793615358 48
1793615363 48
1793615368 48
1793615373 48
1793615378 48
1793615383 48
1793615388 48
```
</details>

---

