---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-20 17:39:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 844 |
| Sample Rate | 14.07/sec |
| Health Score | 879% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1792532072 91
1792532078 91
1792532083 91
1792532088 91
1792532093 91
1792532098 91
1792532103 91
1792532108 91
1792532113 91
1792532119 91
1792532124 89
1792532129 89
1792532134 89
1792532139 89
1792532144 89
1792532149 89
1792532154 89
1792532159 89
1792532164 89
1792532169 89
```
</details>

---

