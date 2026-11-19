---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:13:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 225 |
| Sample Rate | 3.75/sec |
| Health Score | 234% |
| Threads | 14 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795129681 50
1795129686 50
1795129691 50
1795129696 50
1795129701 50
1795129706 50
1795129711 50
1795129716 50
1795129721 50
1795129726 50
1795129731 50
1795129737 50
1795129742 50
1795129747 50
1795129752 50
1795129757 50
1795129762 50
1795129767 50
1795129772 50
1795129777 50
```
</details>

---

