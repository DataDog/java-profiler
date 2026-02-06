---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-06 06:12:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 10 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 994 |
| Sample Rate | 16.57/sec |
| Health Score | 1036% |
| Threads | 13 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 45-68 cores)</summary>

```
1770375803 45
1770375808 45
1770375813 45
1770375818 45
1770375823 59
1770375828 59
1770375833 63
1770375838 63
1770375843 63
1770375848 63
1770375853 63
1770375858 63
1770375863 63
1770375868 63
1770375873 63
1770375878 63
1770375883 63
1770375888 63
1770375893 63
1770375898 63
```
</details>

---

