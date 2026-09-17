---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 18:03:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (4 unique values: 74-96 cores)</summary>

```
1789682159 76
1789682164 76
1789682169 76
1789682174 76
1789682179 74
1789682184 74
1789682189 74
1789682194 74
1789682199 74
1789682204 74
1789682209 74
1789682214 74
1789682219 94
1789682224 94
1789682229 94
1789682234 94
1789682239 94
1789682244 94
1789682249 96
1789682254 96
```
</details>

---

