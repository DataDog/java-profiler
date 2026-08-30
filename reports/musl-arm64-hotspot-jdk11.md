---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-30 00:57:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 11 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1788065535 43
1788065540 43
1788065545 43
1788065550 46
1788065556 46
1788065561 46
1788065566 46
1788065571 46
1788065576 46
1788065581 46
1788065586 46
1788065591 46
1788065596 46
1788065601 48
1788065606 48
1788065611 48
1788065616 48
1788065621 48
1788065626 48
1788065631 43
```
</details>

---

