---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-21 04:48:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 742 |
| Sample Rate | 12.37/sec |
| Health Score | 773% |
| Threads | 9 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1789980087 96
1789980092 96
1789980097 96
1789980102 88
1789980107 88
1789980112 88
1789980117 88
1789980122 78
1789980127 78
1789980132 78
1789980137 78
1789980142 78
1789980147 78
1789980152 78
1789980157 78
1789980162 78
1789980167 78
1789980172 78
1789980177 78
1789980182 78
```
</details>

---

