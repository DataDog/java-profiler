---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:52:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (6 unique values: 60-81 cores)</summary>

```
1795013150 79
1795013155 79
1795013160 79
1795013165 81
1795013170 81
1795013175 81
1795013180 81
1795013185 81
1795013190 81
1795013195 81
1795013200 70
1795013205 70
1795013210 72
1795013215 72
1795013220 63
1795013225 63
1795013230 63
1795013235 63
1795013240 63
1795013245 63
```
</details>

---

