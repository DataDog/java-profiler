---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ❌ FAIL

**Date:** 2026-11-17 08:47:51 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 68-74 cores)</summary>

```
1794922828 70
1794922833 70
1794922838 70
1794922843 70
1794922848 70
1794922853 70
1794922858 68
1794922863 68
1794922868 68
1794922873 68
1794922878 74
1794922883 74
1794922888 74
1794922893 74
1794922898 74
1794922903 74
1794922908 74
1794922913 74
1794922918 74
1794922923 74
```
</details>

---

