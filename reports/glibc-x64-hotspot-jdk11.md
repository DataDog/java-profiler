---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 17:28:30 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 864 |
| Sample Rate | 14.40/sec |
| Health Score | 900% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 66-75 cores)</summary>

```
1789680145 66
1789680150 66
1789680155 66
1789680160 66
1789680165 66
1789680170 66
1789680175 66
1789680180 66
1789680185 66
1789680190 66
1789680195 66
1789680200 66
1789680205 66
1789680210 66
1789680215 75
1789680220 75
1789680225 73
1789680230 73
1789680235 73
1789680240 73
```
</details>

---

