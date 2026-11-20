---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-20 12:39:30 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795196077 29
1795196082 29
1795196087 29
1795196092 29
1795196097 34
1795196102 34
1795196107 32
1795196112 32
1795196117 32
1795196122 32
1795196127 32
1795196132 32
1795196137 32
1795196142 32
1795196147 32
1795196152 32
1795196157 32
1795196162 32
1795196167 32
1795196172 32
```
</details>

---

