---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 17:27:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 86-96 cores)</summary>

```
1792704140 88
1792704145 88
1792704150 86
1792704155 86
1792704160 86
1792704165 86
1792704170 86
1792704175 90
1792704180 90
1792704185 90
1792704190 90
1792704195 90
1792704200 90
1792704205 90
1792704210 90
1792704215 90
1792704220 90
1792704225 90
1792704230 90
1792704235 92
```
</details>

---

