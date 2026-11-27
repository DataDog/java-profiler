---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-27 07:48:12 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (2 unique values: 19-21 cores)</summary>

```
1795783417 21
1795783422 21
1795783427 21
1795783432 21
1795783437 19
1795783442 19
1795783447 19
1795783452 19
1795783457 19
1795783462 19
1795783467 19
1795783472 19
1795783477 19
1795783482 19
1795783487 19
1795783492 19
1795783497 19
1795783502 19
1795783507 19
1795783512 19
```
</details>

---

