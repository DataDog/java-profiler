---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 11:57:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 22-35 cores)</summary>

```
1794502129 22
1794502134 22
1794502139 35
1794502144 35
1794502149 35
1794502154 35
1794502159 35
1794502164 35
1794502169 35
1794502174 35
1794502179 35
1794502184 35
1794502189 35
1794502194 35
1794502199 35
1794502204 35
1794502209 35
1794502214 35
1794502219 35
1794502224 35
```
</details>

---

