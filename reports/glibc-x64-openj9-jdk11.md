---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-25 08:42:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 8 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 43-65 cores)</summary>

```
1787661453 65
1787661458 65
1787661463 65
1787661468 65
1787661473 65
1787661478 45
1787661483 45
1787661488 45
1787661493 45
1787661498 45
1787661503 45
1787661508 45
1787661513 45
1787661518 45
1787661523 45
1787661528 45
1787661533 45
1787661538 43
1787661543 43
1787661548 43
```
</details>

---

