---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:18:56 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 76-78 cores)</summary>

```
1795626788 78
1795626793 78
1795626798 76
1795626803 76
1795626808 76
1795626813 76
1795626818 76
1795626823 76
1795626828 76
1795626833 76
1795626838 76
1795626843 76
1795626848 76
1795626853 76
1795626858 76
1795626863 76
1795626868 76
1795626873 76
1795626878 76
1795626883 76
```
</details>

---

