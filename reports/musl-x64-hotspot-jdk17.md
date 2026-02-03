---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-03 09:53:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 56-96 cores)</summary>

```
1770130091 56
1770130096 56
1770130101 56
1770130106 77
1770130111 77
1770130116 77
1770130121 77
1770130126 77
1770130131 77
1770130136 77
1770130141 77
1770130146 77
1770130151 77
1770130156 77
1770130161 77
1770130166 81
1770130171 81
1770130176 81
1770130181 81
1770130186 81
```
</details>

---

