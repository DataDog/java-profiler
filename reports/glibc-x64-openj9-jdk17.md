---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:34:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 56-61 cores)</summary>

```
1795015787 57
1795015792 57
1795015797 57
1795015802 57
1795015807 57
1795015812 57
1795015817 57
1795015822 57
1795015827 57
1795015832 57
1795015837 57
1795015842 59
1795015847 59
1795015852 59
1795015857 59
1795015862 59
1795015867 59
1795015872 61
1795015877 61
1795015882 61
```
</details>

---

