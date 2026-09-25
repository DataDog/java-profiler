---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-25 07:23:20 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (3 unique values: 61-71 cores)</summary>

```
1790335114 63
1790335119 63
1790335124 63
1790335129 63
1790335134 63
1790335139 63
1790335144 63
1790335149 63
1790335154 61
1790335159 61
1790335164 61
1790335169 61
1790335174 61
1790335179 61
1790335184 61
1790335189 61
1790335194 61
1790335199 61
1790335204 71
1790335209 71
```
</details>

---

