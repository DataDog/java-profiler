---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:59:05 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (5 unique values: 59-67 cores)</summary>

```
1794999149 67
1794999154 67
1794999159 65
1794999164 65
1794999169 65
1794999174 65
1794999179 65
1794999184 65
1794999189 65
1794999194 65
1794999200 59
1794999205 59
1794999210 59
1794999215 59
1794999220 59
1794999225 59
1794999230 59
1794999235 59
1794999240 59
1794999245 59
```
</details>

---

