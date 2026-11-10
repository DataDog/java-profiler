---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-10 14:54:04 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1794340132 32
1794340137 32
1794340142 32
1794340147 32
1794340152 32
1794340157 32
1794340162 32
1794340167 32
1794340172 32
1794340177 32
1794340182 32
1794340187 27
1794340192 27
1794340197 27
1794340202 27
1794340207 27
1794340212 27
1794340217 27
1794340222 27
1794340227 27
```
</details>

---

