---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-28 08:40:06 EDT

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
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (6 unique values: 30-48 cores)</summary>

```
1787920554 48
1787920559 48
1787920564 37
1787920569 37
1787920574 37
1787920579 37
1787920584 37
1787920589 37
1787920594 32
1787920599 32
1787920604 30
1787920609 30
1787920614 30
1787920619 30
1787920624 32
1787920629 32
1787920634 32
1787920639 32
1787920644 32
1787920649 32
```
</details>

---

