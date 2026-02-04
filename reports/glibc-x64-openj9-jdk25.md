---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 14:09:43 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 11 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 891 |
| Sample Rate | 14.85/sec |
| Health Score | 928% |
| Threads | 13 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 47-52 cores)</summary>

```
1770231813 47
1770231818 47
1770231823 47
1770231828 47
1770231833 47
1770231838 47
1770231843 47
1770231848 47
1770231853 47
1770231858 47
1770231863 47
1770231868 47
1770231873 47
1770231878 47
1770231883 47
1770231888 47
1770231893 47
1770231898 52
1770231903 52
1770231908 48
```
</details>

---

