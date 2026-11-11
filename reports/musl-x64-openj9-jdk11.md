---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 07:14:39 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 963 |
| Sample Rate | 16.05/sec |
| Health Score | 1003% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1794398958 27
1794398963 27
1794398968 32
1794398973 32
1794398978 32
1794398983 32
1794398988 32
1794398993 32
1794398998 32
1794399003 32
1794399008 32
1794399013 32
1794399018 32
1794399023 32
1794399028 32
1794399033 32
1794399038 32
1794399043 32
1794399048 32
1794399053 32
```
</details>

---

