---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-27 08:39:20 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (3 unique values: 48-52 cores)</summary>

```
1795786425 48
1795786430 48
1795786435 48
1795786440 48
1795786445 48
1795786450 48
1795786455 48
1795786460 48
1795786465 48
1795786470 48
1795786475 48
1795786480 48
1795786485 48
1795786490 48
1795786495 48
1795786500 52
1795786505 52
1795786510 50
1795786515 50
1795786520 50
```
</details>

---

