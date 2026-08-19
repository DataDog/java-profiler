---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 13:19:53 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787159782 29
1787159787 29
1787159792 29
1787159797 34
1787159802 34
1787159807 34
1787159812 34
1787159817 34
1787159822 34
1787159827 34
1787159832 34
1787159837 34
1787159842 34
1787159847 34
1787159852 34
1787159857 34
1787159862 34
1787159867 34
1787159872 34
1787159877 34
```
</details>

---

