---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:47:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 11 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 818 |
| Sample Rate | 13.63/sec |
| Health Score | 852% |
| Threads | 13 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 70-96 cores)</summary>

```
1770129676 70
1770129681 70
1770129686 70
1770129691 96
1770129696 96
1770129701 96
1770129706 96
1770129711 96
1770129716 96
1770129721 96
1770129726 96
1770129731 96
1770129736 96
1770129741 96
1770129746 96
1770129751 96
1770129756 96
1770129761 96
1770129766 96
1770129771 87
```
</details>

---

