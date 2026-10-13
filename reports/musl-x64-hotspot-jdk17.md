---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-13 13:24:03 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 81-86 cores)</summary>

```
1791912017 81
1791912022 81
1791912027 81
1791912032 86
1791912037 86
1791912042 86
1791912047 84
1791912052 84
1791912057 84
1791912062 82
1791912067 82
1791912072 82
1791912077 82
1791912082 82
1791912087 82
1791912092 82
1791912097 84
1791912102 84
1791912107 84
1791912112 84
```
</details>

---

