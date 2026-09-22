---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 07:06:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (6 unique values: 72-96 cores)</summary>

```
1790074979 96
1790074984 96
1790074989 96
1790074994 96
1790074999 96
1790075004 91
1790075009 91
1790075014 76
1790075019 76
1790075024 76
1790075029 76
1790075034 74
1790075039 74
1790075044 74
1790075049 74
1790075054 74
1790075059 74
1790075064 72
1790075069 72
1790075074 72
```
</details>

---

