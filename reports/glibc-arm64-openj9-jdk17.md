---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-26 09:45:32 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 308 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 32-36 cores)</summary>

```
1787751632 36
1787751637 36
1787751642 36
1787751647 36
1787751652 36
1787751657 36
1787751662 36
1787751667 36
1787751672 36
1787751677 36
1787751682 36
1787751687 36
1787751692 36
1787751697 36
1787751702 36
1787751707 36
1787751712 36
1787751717 36
1787751722 36
1787751727 36
```
</details>

---

