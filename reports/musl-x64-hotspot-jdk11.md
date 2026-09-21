---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 08:08:22 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1789992181 32
1789992186 32
1789992191 32
1789992196 32
1789992201 32
1789992206 32
1789992211 27
1789992216 27
1789992221 27
1789992226 27
1789992231 27
1789992236 27
1789992241 27
1789992246 27
1789992251 27
1789992256 27
1789992261 27
1789992266 27
1789992271 27
1789992276 27
```
</details>

---

