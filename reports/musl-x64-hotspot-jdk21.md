---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:54:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 58-60 cores)</summary>

```
1793800112 60
1793800117 60
1793800122 60
1793800127 60
1793800132 60
1793800137 60
1793800142 60
1793800147 58
1793800152 58
1793800157 58
1793800162 58
1793800167 60
1793800172 60
1793800177 60
1793800182 60
1793800187 60
1793800192 60
1793800197 60
1793800202 60
1793800207 60
```
</details>

---

