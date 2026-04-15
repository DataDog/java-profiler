---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-15 11:14:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 11 |
| Allocations | 415 |

<details>
<summary>CPU Timeline (3 unique values: 31-49 cores)</summary>

```
1776265818 31
1776265823 31
1776265828 31
1776265833 44
1776265838 44
1776265843 44
1776265848 44
1776265853 44
1776265858 44
1776265863 49
1776265868 49
1776265873 49
1776265878 49
1776265883 49
1776265888 49
1776265893 49
1776265898 49
1776265903 49
1776265908 49
1776265913 49
```
</details>

---

