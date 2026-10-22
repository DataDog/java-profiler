---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 16:51:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 253 |
| Sample Rate | 4.22/sec |
| Health Score | 264% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1792701958 51
1792701963 51
1792701968 51
1792701973 51
1792701978 51
1792701983 51
1792701988 51
1792701993 51
1792701998 51
1792702003 51
1792702008 51
1792702013 51
1792702018 51
1792702023 51
1792702028 51
1792702033 64
1792702039 64
1792702044 64
1792702049 54
1792702054 54
```
</details>

---

