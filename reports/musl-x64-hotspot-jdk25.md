---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 14:24:18 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (5 unique values: 66-72 cores)</summary>

```
1791397175 67
1791397180 67
1791397185 67
1791397190 67
1791397195 67
1791397200 72
1791397205 72
1791397210 70
1791397215 70
1791397220 70
1791397225 70
1791397230 70
1791397235 70
1791397240 70
1791397245 68
1791397250 68
1791397255 66
1791397260 66
1791397265 66
1791397270 66
```
</details>

---

