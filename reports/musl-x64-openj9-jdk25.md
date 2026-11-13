---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 09:46:24 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 8 |
| Allocations | 441 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794580879 30
1794580884 30
1794580889 30
1794580894 30
1794580899 30
1794580904 30
1794580909 30
1794580914 30
1794580919 30
1794580924 30
1794580929 30
1794580934 30
1794580939 30
1794580944 30
1794580949 30
1794580954 30
1794580959 32
1794580964 32
1794580969 32
1794580974 32
```
</details>

---

