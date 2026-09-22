---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 17:00:42 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 344 |
| Sample Rate | 5.73/sec |
| Health Score | 358% |
| Threads | 9 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790110496 45
1790110501 45
1790110506 50
1790110511 50
1790110516 50
1790110521 50
1790110526 50
1790110531 50
1790110536 50
1790110541 50
1790110546 45
1790110551 45
1790110556 45
1790110561 45
1790110566 45
1790110571 45
1790110576 45
1790110581 45
1790110586 45
1790110591 45
```
</details>

---

