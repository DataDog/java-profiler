---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-28 08:25:44 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 255 |
| Sample Rate | 4.25/sec |
| Health Score | 266% |
| Threads | 8 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1787919754 40
1787919759 40
1787919764 40
1787919769 40
1787919774 40
1787919779 40
1787919784 40
1787919789 40
1787919794 40
1787919799 40
1787919804 40
1787919809 40
1787919814 40
1787919819 40
1787919824 40
1787919829 40
1787919834 40
1787919839 40
1787919844 40
1787919849 40
```
</details>

---

