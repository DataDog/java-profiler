---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:20:31 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 13 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (3 unique values: 23-30 cores)</summary>

```
1786526134 23
1786526139 23
1786526144 25
1786526149 25
1786526154 25
1786526159 25
1786526164 25
1786526169 25
1786526174 25
1786526179 25
1786526184 25
1786526189 25
1786526194 25
1786526199 25
1786526204 25
1786526209 25
1786526214 25
1786526219 25
1786526224 25
1786526229 25
```
</details>

---

