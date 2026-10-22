---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 04:49:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 9 |
| Allocations | 146 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1792658573 43
1792658578 43
1792658583 43
1792658588 43
1792658593 43
1792658598 43
1792658603 43
1792658608 43
1792658613 43
1792658618 43
1792658623 43
1792658628 43
1792658633 43
1792658638 43
1792658643 43
1792658648 43
1792658653 38
1792658658 38
1792658663 38
1792658668 38
```
</details>

---

