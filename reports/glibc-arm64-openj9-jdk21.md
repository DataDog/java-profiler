---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 07:02:41 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 342 |
| Sample Rate | 5.70/sec |
| Health Score | 356% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 12-14 cores)</summary>

```
1792666511 14
1792666516 14
1792666521 14
1792666526 14
1792666531 12
1792666536 12
1792666541 12
1792666546 12
1792666551 12
1792666556 12
1792666561 12
1792666566 12
1792666571 12
1792666577 12
1792666582 12
1792666587 12
1792666592 12
1792666597 12
1792666602 12
1792666607 12
```
</details>

---

