---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 05:35:54 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 11 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1794997817 34
1794997822 34
1794997827 34
1794997832 34
1794997837 34
1794997842 34
1794997847 34
1794997852 34
1794997857 34
1794997862 32
1794997867 32
1794997872 32
1794997877 32
1794997882 32
1794997887 32
1794997892 32
1794997897 32
1794997902 32
1794997907 34
1794997912 34
```
</details>

---

