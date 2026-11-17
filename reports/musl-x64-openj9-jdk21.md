---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-17 08:01:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1794920126 92
1794920131 92
1794920136 92
1794920141 92
1794920146 92
1794920151 92
1794920156 92
1794920161 94
1794920166 94
1794920171 92
1794920176 92
1794920181 92
1794920186 92
1794920191 92
1794920196 92
1794920201 94
1794920206 94
1794920211 94
1794920216 94
1794920221 94
```
</details>

---

