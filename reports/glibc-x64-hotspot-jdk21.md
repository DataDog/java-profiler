---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 05:45:40 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1794480149 84
1794480154 84
1794480159 84
1794480164 84
1794480169 84
1794480174 84
1794480179 84
1794480184 84
1794480189 84
1794480194 82
1794480199 82
1794480204 82
1794480209 82
1794480214 82
1794480219 82
1794480224 86
1794480229 86
1794480234 86
1794480239 86
1794480244 86
```
</details>

---

