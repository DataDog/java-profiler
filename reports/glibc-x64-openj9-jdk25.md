---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:18:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1795626773 64
1795626778 64
1795626783 64
1795626788 64
1795626793 64
1795626798 64
1795626803 64
1795626808 64
1795626813 64
1795626818 64
1795626823 64
1795626828 64
1795626833 64
1795626838 64
1795626843 64
1795626848 64
1795626853 64
1795626858 64
1795626863 64
1795626868 64
```
</details>

---

