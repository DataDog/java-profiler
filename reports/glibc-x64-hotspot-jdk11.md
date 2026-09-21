---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 08:08:20 EDT

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1789992176 74
1789992181 74
1789992186 74
1789992191 74
1789992196 74
1789992201 74
1789992206 74
1789992211 74
1789992216 74
1789992221 74
1789992226 74
1789992231 76
1789992236 76
1789992241 76
1789992246 76
1789992251 76
1789992256 76
1789992261 76
1789992266 76
1789992271 76
```
</details>

---

