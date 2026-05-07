---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 12:41:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (3 unique values: 42-44 cores)</summary>

```
1778171843 42
1778171848 42
1778171853 42
1778171858 42
1778171863 42
1778171868 42
1778171873 42
1778171878 44
1778171883 44
1778171888 44
1778171893 44
1778171898 44
1778171903 44
1778171908 43
1778171913 43
1778171918 43
1778171923 43
1778171928 43
1778171933 43
1778171938 43
```
</details>

---

