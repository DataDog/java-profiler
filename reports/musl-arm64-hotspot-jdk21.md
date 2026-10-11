---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-11 01:02:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791694701 43
1791694706 43
1791694711 43
1791694716 43
1791694721 43
1791694726 43
1791694731 43
1791694736 43
1791694741 43
1791694746 48
1791694751 48
1791694756 48
1791694761 48
1791694766 48
1791694771 48
1791694776 48
1791694781 48
1791694786 48
1791694791 48
1791694796 48
```
</details>

---

