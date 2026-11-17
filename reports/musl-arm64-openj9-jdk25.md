---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 08:47:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 12 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1794922963 51
1794922968 51
1794922973 51
1794922978 51
1794922983 51
1794922988 51
1794922993 51
1794922998 51
1794923003 51
1794923008 51
1794923013 51
1794923018 51
1794923023 51
1794923028 51
1794923033 51
1794923038 51
1794923043 51
1794923048 51
1794923053 51
1794923058 51
```
</details>

---

