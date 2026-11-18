---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:31:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 893 |
| Sample Rate | 14.88/sec |
| Health Score | 930% |
| Threads | 9 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1795012032 63
1795012037 63
1795012042 63
1795012047 63
1795012052 63
1795012057 63
1795012062 63
1795012067 63
1795012072 63
1795012077 63
1795012082 65
1795012087 65
1795012092 65
1795012097 65
1795012102 65
1795012107 65
1795012112 65
1795012117 65
1795012122 65
1795012127 65
```
</details>

---

