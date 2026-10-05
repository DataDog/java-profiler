---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-05 11:50:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 306 |
| Sample Rate | 5.10/sec |
| Health Score | 319% |
| Threads | 13 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791215125 43
1791215130 43
1791215135 48
1791215140 48
1791215145 48
1791215150 48
1791215155 48
1791215160 48
1791215165 48
1791215170 48
1791215176 48
1791215181 48
1791215186 48
1791215191 48
1791215196 48
1791215201 48
1791215206 48
1791215211 48
1791215216 48
1791215221 48
```
</details>

---

