---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 09:37:56 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 86-96 cores)</summary>

```
1788528788 92
1788528793 94
1788528798 94
1788528803 94
1788528808 94
1788528813 94
1788528818 96
1788528823 96
1788528828 96
1788528833 96
1788528838 96
1788528843 96
1788528848 96
1788528853 96
1788528858 96
1788528863 96
1788528868 96
1788528873 96
1788528878 86
1788528883 86
```
</details>

---

