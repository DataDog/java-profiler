---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:30:44 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 857 |
| Sample Rate | 14.28/sec |
| Health Score | 892% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 79-87 cores)</summary>

```
1795012047 87
1795012052 87
1795012057 87
1795012062 87
1795012067 87
1795012072 87
1795012077 87
1795012082 87
1795012087 87
1795012092 87
1795012097 81
1795012102 81
1795012107 81
1795012112 81
1795012117 81
1795012122 81
1795012127 81
1795012132 81
1795012137 81
1795012142 81
```
</details>

---

