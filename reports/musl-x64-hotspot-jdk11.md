---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-03 05:48:25 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 977 |
| Sample Rate | 16.28/sec |
| Health Score | 1018% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 45-81 cores)</summary>

```
1791020626 81
1791020631 81
1791020636 81
1791020641 81
1791020646 81
1791020651 81
1791020656 81
1791020661 81
1791020666 81
1791020671 81
1791020676 81
1791020681 81
1791020686 81
1791020691 81
1791020696 81
1791020701 47
1791020706 47
1791020711 47
1791020716 47
1791020721 47
```
</details>

---

