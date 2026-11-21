---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-21 05:47:03 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 349 |
| Sample Rate | 5.82/sec |
| Health Score | 364% |
| Threads | 11 |
| Allocations | 195 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 13 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1795257771 19
1795257776 19
1795257781 19
1795257786 19
1795257791 24
1795257796 24
1795257801 24
1795257806 24
1795257811 24
1795257816 24
1795257821 24
1795257826 24
1795257831 24
1795257836 24
1795257841 24
1795257846 24
1795257851 24
1795257856 24
1795257861 24
1795257866 24
```
</details>

---

