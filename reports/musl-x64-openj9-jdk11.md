---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 12:19:06 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 554 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1794590087 89
1794590092 89
1794590097 89
1794590102 89
1794590107 94
1794590112 94
1794590117 94
1794590122 94
1794590127 94
1794590132 94
1794590137 94
1794590142 94
1794590147 94
1794590152 94
1794590157 94
1794590162 96
1794590167 96
1794590172 96
1794590177 96
1794590182 96
```
</details>

---

