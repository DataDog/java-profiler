---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-15 03:56:29 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 11-32 cores)</summary>

```
1792050689 11
1792050694 11
1792050699 11
1792050704 11
1792050709 11
1792050714 11
1792050719 11
1792050724 11
1792050729 11
1792050734 32
1792050739 32
1792050744 30
1792050749 30
1792050754 30
1792050759 30
1792050764 30
1792050769 30
1792050774 30
1792050779 30
1792050784 30
```
</details>

---

