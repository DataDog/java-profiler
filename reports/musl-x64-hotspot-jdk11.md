---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 10:31:06 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 946 |
| Sample Rate | 15.77/sec |
| Health Score | 986% |
| Threads | 12 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (5 unique values: 80-87 cores)</summary>

```
1778509494 85
1778509499 83
1778509504 83
1778509509 83
1778509514 83
1778509519 83
1778509524 83
1778509529 80
1778509534 80
1778509539 80
1778509544 80
1778509549 80
1778509554 80
1778509559 80
1778509564 82
1778509569 82
1778509574 83
1778509579 83
1778509584 83
1778509589 83
```
</details>

---

