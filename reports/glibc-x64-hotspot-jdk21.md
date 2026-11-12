---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 11:57:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 12 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (4 unique values: 76-96 cores)</summary>

```
1794502134 76
1794502139 76
1794502144 76
1794502149 76
1794502154 76
1794502159 76
1794502164 76
1794502169 76
1794502174 76
1794502179 77
1794502184 77
1794502189 77
1794502194 77
1794502199 77
1794502204 77
1794502209 77
1794502214 79
1794502219 79
1794502224 96
1794502229 96
```
</details>

---

