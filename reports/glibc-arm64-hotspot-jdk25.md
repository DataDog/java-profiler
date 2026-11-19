---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:13:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 15-64 cores)</summary>

```
1795129706 15
1795129711 15
1795129716 15
1795129721 15
1795129726 15
1795129731 15
1795129736 15
1795129741 15
1795129746 15
1795129751 15
1795129756 15
1795129761 15
1795129766 64
1795129771 64
1795129776 64
1795129781 64
1795129786 64
1795129791 64
1795129796 64
1795129801 64
```
</details>

---

