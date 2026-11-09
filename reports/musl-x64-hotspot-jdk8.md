---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-09 09:27:56 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1794234134 76
1794234139 76
1794234144 76
1794234149 76
1794234154 76
1794234159 76
1794234164 76
1794234169 74
1794234174 74
1794234179 74
1794234184 74
1794234189 74
1794234194 72
1794234199 72
1794234204 72
1794234209 72
1794234214 72
1794234219 72
1794234224 72
1794234229 72
```
</details>

---

