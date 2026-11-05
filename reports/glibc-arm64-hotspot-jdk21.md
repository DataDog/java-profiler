---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 05:42:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 12 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793875099 40
1793875104 40
1793875109 40
1793875114 40
1793875119 40
1793875124 40
1793875129 40
1793875134 40
1793875139 40
1793875144 40
1793875149 40
1793875154 40
1793875159 40
1793875164 40
1793875169 40
1793875174 40
1793875179 40
1793875184 40
1793875189 40
1793875194 40
```
</details>

---

