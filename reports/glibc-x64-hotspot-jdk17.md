---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 18:30:12 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 12 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (3 unique values: 29-40 cores)</summary>

```
1793834741 29
1793834746 29
1793834751 29
1793834756 38
1793834761 38
1793834766 38
1793834771 38
1793834776 38
1793834781 38
1793834786 38
1793834791 38
1793834796 38
1793834801 38
1793834806 38
1793834811 38
1793834816 40
1793834821 40
1793834826 40
1793834831 40
1793834836 40
```
</details>

---

