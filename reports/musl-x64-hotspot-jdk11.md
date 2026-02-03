---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 09:59:32 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 26-30 cores)</summary>

```
1770130530 30
1770130535 30
1770130540 30
1770130545 30
1770130550 30
1770130555 30
1770130560 30
1770130565 30
1770130570 30
1770130575 30
1770130580 30
1770130585 30
1770130590 30
1770130595 30
1770130600 26
1770130605 26
1770130610 26
1770130615 26
1770130620 26
1770130625 26
```
</details>

---

