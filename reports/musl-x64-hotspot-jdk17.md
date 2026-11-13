---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-11-13 10:19:18 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1794582892 92
1794582897 92
1794582902 92
1794582907 92
1794582912 92
1794582917 94
1794582922 94
1794582927 94
1794582932 92
1794582937 92
1794582942 92
1794582947 92
1794582952 92
1794582957 90
1794582962 90
1794582967 90
1794582972 90
1794582977 90
1794582982 90
1794582987 90
```
</details>

---

