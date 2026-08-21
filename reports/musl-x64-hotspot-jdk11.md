---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 05:42:05 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787305122 96
1787305127 96
1787305132 96
1787305137 96
1787305142 96
1787305147 96
1787305152 96
1787305157 96
1787305162 96
1787305168 96
1787305173 96
1787305178 96
1787305183 94
1787305188 94
1787305193 94
1787305198 94
1787305203 94
1787305208 94
1787305213 94
1787305218 94
```
</details>

---

