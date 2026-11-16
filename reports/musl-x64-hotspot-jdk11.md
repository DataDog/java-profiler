---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 20:26:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794792139 32
1794792144 32
1794792149 32
1794792154 32
1794792159 32
1794792164 32
1794792169 32
1794792174 32
1794792179 32
1794792184 32
1794792189 32
1794792194 32
1794792199 32
1794792204 32
1794792209 32
1794792214 32
1794792219 32
1794792224 32
1794792229 32
1794792234 32
```
</details>

---

