---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-08 09:54:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 9 |
| Allocations | 420 |

<details>
<summary>CPU Timeline (4 unique values: 13-25 cores)</summary>

```
1775656133 13
1775656138 13
1775656143 15
1775656148 15
1775656153 15
1775656158 15
1775656163 15
1775656168 15
1775656173 15
1775656178 15
1775656183 15
1775656188 15
1775656193 20
1775656198 20
1775656203 20
1775656208 20
1775656213 25
1775656218 25
1775656223 25
1775656228 25
```
</details>

---

