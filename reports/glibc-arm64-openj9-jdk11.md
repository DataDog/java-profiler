---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-23 13:49:21 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 8 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 10 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 41-46 cores)</summary>

```
1792777547 41
1792777552 41
1792777557 41
1792777562 46
1792777567 46
1792777572 46
1792777577 46
1792777582 41
1792777587 41
1792777592 41
1792777597 41
1792777602 41
1792777607 41
1792777612 41
1792777617 41
1792777622 41
1792777627 41
1792777632 41
1792777637 41
1792777642 41
```
</details>

---

