---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-18 01:04:34 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1792299682 34
1792299687 34
1792299692 34
1792299697 34
1792299702 34
1792299707 34
1792299712 34
1792299717 34
1792299722 34
1792299727 34
1792299732 34
1792299737 34
1792299742 34
1792299747 34
1792299752 34
1792299757 29
1792299762 29
1792299767 29
1792299772 29
1792299777 29
```
</details>

---

