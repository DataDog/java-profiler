---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 00:59:16 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 8 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 23-32 cores)</summary>

```
1790225620 23
1790225626 23
1790225631 23
1790225636 23
1790225641 23
1790225646 32
1790225651 32
1790225656 32
1790225661 32
1790225666 32
1790225671 32
1790225676 32
1790225681 32
1790225686 32
1790225691 32
1790225696 32
1790225701 32
1790225706 32
1790225711 32
1790225716 32
```
</details>

---

