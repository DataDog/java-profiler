---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-25 00:58:50 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (6 unique values: 38-52 cores)</summary>

```
1790312066 52
1790312071 44
1790312076 44
1790312081 48
1790312086 48
1790312091 48
1790312096 50
1790312101 50
1790312106 50
1790312111 50
1790312116 52
1790312121 52
1790312126 52
1790312131 48
1790312136 48
1790312141 38
1790312146 38
1790312151 38
1790312156 38
1790312161 38
```
</details>

---

