---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 12:18:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 54-65 cores)</summary>

```
1795626778 65
1795626783 65
1795626788 65
1795626793 65
1795626798 65
1795626803 65
1795626808 65
1795626813 65
1795626818 65
1795626823 54
1795626828 54
1795626833 54
1795626838 54
1795626843 54
1795626848 54
1795626853 54
1795626858 54
1795626863 54
1795626868 54
1795626873 54
```
</details>

---

