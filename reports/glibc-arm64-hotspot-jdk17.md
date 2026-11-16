---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 09:37:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1794839646 51
1794839651 51
1794839656 51
1794839661 51
1794839666 51
1794839671 51
1794839676 51
1794839681 51
1794839686 51
1794839691 51
1794839696 51
1794839701 39
1794839706 39
1794839711 39
1794839716 39
1794839721 39
1794839726 39
1794839731 39
1794839736 39
1794839741 39
```
</details>

---

