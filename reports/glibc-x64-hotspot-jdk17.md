---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-11 18:29:49 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 820 |
| Sample Rate | 13.67/sec |
| Health Score | 854% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1008 |
| Sample Rate | 16.80/sec |
| Health Score | 1050% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1778538169 82
1778538174 82
1778538179 82
1778538184 82
1778538189 82
1778538194 84
1778538199 84
1778538204 84
1778538209 84
1778538214 84
1778538219 84
1778538224 84
1778538229 84
1778538234 84
1778538239 84
1778538244 84
1778538249 84
1778538254 84
1778538259 84
1778538264 84
```
</details>

---

