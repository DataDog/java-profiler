---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 09:28:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (4 unique values: 57-66 cores)</summary>

```
1776950569 63
1776950574 63
1776950579 63
1776950584 63
1776950589 63
1776950594 63
1776950599 63
1776950604 57
1776950609 57
1776950614 57
1776950619 57
1776950624 57
1776950629 57
1776950634 57
1776950639 57
1776950644 57
1776950649 57
1776950654 66
1776950659 66
1776950664 66
```
</details>

---

