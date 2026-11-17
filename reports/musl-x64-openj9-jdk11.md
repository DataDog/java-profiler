---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 12:07:22 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 966 |
| Sample Rate | 16.10/sec |
| Health Score | 1006% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1794934950 79
1794934955 79
1794934960 79
1794934965 79
1794934970 79
1794934975 79
1794934980 79
1794934985 79
1794934990 79
1794934995 79
1794935000 79
1794935006 79
1794935011 79
1794935016 79
1794935021 79
1794935026 79
1794935031 79
1794935036 77
1794935041 77
1794935046 77
```
</details>

---

