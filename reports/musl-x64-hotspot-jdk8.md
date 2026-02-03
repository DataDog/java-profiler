---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-02-03 08:18:05 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 263 |
| Sample Rate | 4.38/sec |
| Health Score | 274% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 5 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770119069 27
1770119074 27
1770119079 27
1770119084 27
1770119089 32
1770119094 32
1770119099 32
1770119104 32
1770119109 32
1770119114 32
1770119119 32
1770119124 32
1770119129 32
1770119134 32
1770119139 27
1770119144 27
1770119149 32
1770119154 32
1770119159 32
1770119164 32
```
</details>

---

