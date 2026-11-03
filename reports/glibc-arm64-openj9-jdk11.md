---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 14:44:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 14 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 43-51 cores)</summary>

```
1793734853 45
1793734858 45
1793734863 43
1793734868 43
1793734873 43
1793734878 43
1793734883 43
1793734888 43
1793734893 43
1793734898 43
1793734903 43
1793734908 43
1793734913 43
1793734918 43
1793734923 43
1793734928 43
1793734933 43
1793734938 43
1793734943 51
1793734948 51
```
</details>

---

