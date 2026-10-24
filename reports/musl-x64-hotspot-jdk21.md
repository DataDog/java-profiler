---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-24 04:44:32 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 61-94 cores)</summary>

```
1792831107 61
1792831112 61
1792831117 61
1792831122 61
1792831127 63
1792831132 63
1792831137 63
1792831142 63
1792831147 63
1792831152 63
1792831157 61
1792831162 61
1792831167 61
1792831172 61
1792831177 61
1792831182 61
1792831187 94
1792831192 94
1792831197 94
1792831202 94
```
</details>

---

