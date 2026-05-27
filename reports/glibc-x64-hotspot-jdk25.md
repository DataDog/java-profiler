---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-27 06:39:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 66 |
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
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 11-66 cores)</summary>

```
1779878176 25
1779878181 25
1779878186 25
1779878191 25
1779878196 25
1779878201 25
1779878206 25
1779878211 25
1779878216 11
1779878221 11
1779878226 11
1779878231 11
1779878236 11
1779878241 11
1779878246 11
1779878251 11
1779878256 21
1779878261 21
1779878266 21
1779878271 21
```
</details>

---

