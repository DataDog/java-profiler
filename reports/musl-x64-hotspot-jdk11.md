---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 05:52:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 9 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (4 unique values: 47-57 cores)</summary>

```
1795517125 47
1795517130 47
1795517135 49
1795517140 49
1795517145 49
1795517150 49
1795517155 49
1795517160 49
1795517165 49
1795517170 49
1795517175 49
1795517180 49
1795517185 49
1795517190 49
1795517195 47
1795517200 47
1795517205 47
1795517210 47
1795517215 47
1795517220 47
```
</details>

---

