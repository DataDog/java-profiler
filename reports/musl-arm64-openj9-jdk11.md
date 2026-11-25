---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 12:23:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 150 |
| Sample Rate | 2.50/sec |
| Health Score | 156% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 966 |
| Sample Rate | 16.10/sec |
| Health Score | 1006% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795627063 64
1795627068 64
1795627073 64
1795627078 64
1795627084 64
1795627089 64
1795627094 64
1795627099 64
1795627104 64
1795627109 64
1795627114 64
1795627119 64
1795627124 64
1795627129 64
1795627134 64
1795627139 64
1795627144 64
1795627149 64
1795627154 64
1795627159 64
```
</details>

---

