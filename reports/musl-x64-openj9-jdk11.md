---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 17:00:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 46-96 cores)</summary>

```
1790110467 46
1790110472 46
1790110477 79
1790110482 79
1790110487 79
1790110492 79
1790110497 79
1790110502 79
1790110507 79
1790110512 79
1790110517 79
1790110522 79
1790110527 79
1790110532 79
1790110537 96
1790110542 96
1790110547 96
1790110552 96
1790110557 96
1790110562 96
```
</details>

---

