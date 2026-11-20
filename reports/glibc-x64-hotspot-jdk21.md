---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-20 07:04:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 66-79 cores)</summary>

```
1795176000 68
1795176005 68
1795176010 68
1795176015 66
1795176020 66
1795176025 66
1795176030 66
1795176035 66
1795176040 66
1795176045 66
1795176050 66
1795176055 66
1795176060 66
1795176065 66
1795176070 66
1795176075 68
1795176080 68
1795176086 68
1795176091 73
1795176096 73
```
</details>

---

