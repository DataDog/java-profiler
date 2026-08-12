---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-12 05:20:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1786526124 70
1786526129 70
1786526134 72
1786526139 72
1786526144 72
1786526149 72
1786526154 72
1786526159 72
1786526164 72
1786526169 72
1786526174 72
1786526179 72
1786526184 72
1786526189 72
1786526194 72
1786526199 72
1786526204 72
1786526209 72
1786526214 72
1786526219 72
```
</details>

---

