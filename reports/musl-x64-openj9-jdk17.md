---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:31:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1795012022 30
1795012027 30
1795012032 30
1795012037 30
1795012042 30
1795012047 32
1795012052 32
1795012057 32
1795012062 32
1795012067 32
1795012072 32
1795012077 32
1795012082 32
1795012087 32
1795012092 30
1795012097 30
1795012102 30
1795012107 30
1795012112 30
1795012117 30
```
</details>

---

