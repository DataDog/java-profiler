---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-18 05:22:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 11 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (5 unique values: 78-96 cores)</summary>

```
1787044569 78
1787044574 78
1787044579 78
1787044584 78
1787044589 80
1787044594 80
1787044599 80
1787044604 80
1787044609 80
1787044614 80
1787044619 80
1787044624 80
1787044629 80
1787044634 80
1787044639 94
1787044644 94
1787044649 94
1787044654 94
1787044659 94
1787044664 94
```
</details>

---

