---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 19:51:06 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 429 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 43-96 cores)</summary>

```
1793404077 43
1793404082 43
1793404087 43
1793404092 43
1793404097 43
1793404102 43
1793404107 43
1793404112 43
1793404117 43
1793404122 43
1793404127 43
1793404132 43
1793404137 43
1793404142 43
1793404147 43
1793404152 43
1793404157 76
1793404162 76
1793404167 79
1793404172 79
```
</details>

---

