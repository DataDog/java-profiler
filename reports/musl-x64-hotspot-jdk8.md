---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-27 06:17:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 185 |
| Sample Rate | 3.08/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1795777977 22
1795777982 22
1795777987 22
1795777992 20
1795777997 20
1795778002 20
1795778007 20
1795778012 20
1795778017 20
1795778022 20
1795778027 20
1795778032 20
1795778037 20
1795778042 20
1795778047 20
1795778052 20
1795778057 20
1795778062 20
1795778067 20
1795778072 20
```
</details>

---

