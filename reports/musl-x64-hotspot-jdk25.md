---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 12:19:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 21.37/sec |
| Health Score | 1336% |
| Threads | 11 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 919 |
| Sample Rate | 30.63/sec |
| Health Score | 1914% |
| Threads | 13 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 26-37 cores)</summary>

```
1769706806 28
1769706811 28
1769706816 28
1769706821 36
1769706826 36
1769706831 36
1769706836 36
1769706841 26
1769706846 26
1769706851 26
1769706856 32
1769706861 32
1769706866 32
1769706871 32
1769706876 32
1769706881 32
1769706886 32
1769706891 32
1769706896 37
1769706901 37
```
</details>

---

