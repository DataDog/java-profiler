---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 13:00:47 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793120099 48
1793120104 48
1793120109 48
1793120114 48
1793120119 48
1793120124 48
1793120129 48
1793120134 48
1793120139 48
1793120144 48
1793120149 48
1793120154 48
1793120159 48
1793120164 48
1793120169 48
1793120174 48
1793120179 48
1793120184 46
1793120189 46
1793120194 46
```
</details>

---

