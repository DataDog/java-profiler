---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 10:02:50 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 78-84 cores)</summary>

```
1794927447 84
1794927452 84
1794927457 84
1794927462 84
1794927467 84
1794927472 84
1794927477 84
1794927482 84
1794927487 82
1794927492 82
1794927497 82
1794927502 78
1794927507 78
1794927512 78
1794927517 78
1794927522 80
1794927527 80
1794927532 80
1794927537 80
1794927542 80
```
</details>

---

