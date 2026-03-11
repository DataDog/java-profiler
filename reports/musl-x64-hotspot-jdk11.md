---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-11 05:27:48 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1104 |
| Sample Rate | 18.40/sec |
| Health Score | 1150% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1773221018 68
1773221023 68
1773221028 68
1773221033 68
1773221038 68
1773221043 68
1773221048 68
1773221053 68
1773221058 68
1773221063 68
1773221068 70
1773221073 70
1773221078 70
1773221083 70
1773221088 70
1773221093 70
1773221098 70
1773221103 70
1773221108 70
1773221113 70
```
</details>

---

