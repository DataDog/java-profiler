---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 18:20:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1794438875 63
1794438880 63
1794438885 63
1794438890 63
1794438895 63
1794438900 63
1794438905 63
1794438910 63
1794438915 63
1794438920 63
1794438925 61
1794438930 61
1794438935 61
1794438940 61
1794438945 61
1794438950 61
1794438955 61
1794438960 61
1794438965 61
1794438970 61
```
</details>

---

