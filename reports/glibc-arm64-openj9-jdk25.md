---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 09:28:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 740 |
| Sample Rate | 12.33/sec |
| Health Score | 771% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776950575 64
1776950580 64
1776950586 64
1776950591 64
1776950596 64
1776950601 64
1776950606 64
1776950611 64
1776950616 64
1776950621 64
1776950626 64
1776950631 64
1776950636 64
1776950641 64
1776950646 64
1776950651 64
1776950656 64
1776950661 64
1776950666 64
1776950671 64
```
</details>

---

