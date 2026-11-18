---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-18 05:43:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 44-63 cores)</summary>

```
1794998141 58
1794998146 58
1794998151 58
1794998156 58
1794998161 58
1794998166 58
1794998171 58
1794998176 58
1794998181 58
1794998186 58
1794998191 58
1794998196 58
1794998201 58
1794998206 58
1794998211 58
1794998216 58
1794998221 54
1794998226 54
1794998231 54
1794998236 54
```
</details>

---

