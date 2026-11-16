---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 05:18:24 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 11 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 69-89 cores)</summary>

```
1794823863 89
1794823868 89
1794823873 89
1794823878 89
1794823883 89
1794823888 89
1794823893 89
1794823898 89
1794823904 89
1794823909 89
1794823914 89
1794823919 89
1794823924 89
1794823929 89
1794823934 89
1794823939 89
1794823944 77
1794823949 77
1794823954 77
1794823959 77
```
</details>

---

