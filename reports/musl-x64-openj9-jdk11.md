---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 07:57:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 8 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 52-56 cores)</summary>

```
1793274788 52
1793274793 52
1793274798 52
1793274803 54
1793274808 54
1793274813 54
1793274818 54
1793274823 54
1793274828 54
1793274833 54
1793274838 54
1793274843 54
1793274848 54
1793274853 54
1793274858 54
1793274863 54
1793274868 54
1793274873 54
1793274878 54
1793274883 54
```
</details>

---

